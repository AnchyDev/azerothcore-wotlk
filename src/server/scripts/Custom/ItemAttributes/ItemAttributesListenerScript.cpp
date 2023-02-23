#include "ItemAttributesListenerScript.h"
#include "ItemAttributesCommon.h"


void ItemAttributesListenerScript::SendChunkedPayload(Warden* warden, WardenPayloadMgr* payloadMgr, std::string payload, uint32 chunkSize)
{
    auto chunks = sItemAttrHelper->GetChunks(payload, chunkSize);

    if (!payloadMgr->GetPayloadById(_prePayloadId))
    {
        payloadMgr->RegisterPayload(_prePayload, _prePayloadId);
    }

    payloadMgr->QueuePayload(_prePayloadId);
    warden->ForceChecks();

    for (auto const& chunk : chunks)
    {
        auto smallPayload = "wlbuf = wlbuf .. [[" + chunk + "]];";

        payloadMgr->RegisterPayload(smallPayload, _tmpPayloadId, true);
        payloadMgr->QueuePayload(_tmpPayloadId);
        warden->ForceChecks();
    }

    if (!payloadMgr->GetPayloadById(_postPayloadId))
    {
        payloadMgr->RegisterPayload(_postPayload, _postPayloadId);
    }

    payloadMgr->QueuePayload(_postPayloadId);
    warden->ForceChecks();
}

void ItemAttributesListenerScript::OnLogin(Player* player)
{
    if (!sWorld->getBoolConfig(CONFIG_ITEM_CUSTOM_ATTRIBUTES))
    {
        return;
    }

    if (!player)
    {
        return;
    }

    auto warden = player->GetSession()->GetWarden();
    if (!warden)
    {
        return;
    }

    auto payloadMgr = warden->GetPayloadMgr();
    if (!payloadMgr)
    {
        return;
    }

    if (payloadMgr->GetPayloadsInQueue())
        payloadMgr->ClearQueuedPayloads();

    SendChunkedPayload(warden, payloadMgr, _listenerPayload, 128);
}

void ItemAttributesListenerScript::OnLogout(Player* player)
{
    if (!sWorld->getBoolConfig(CONFIG_ITEM_CUSTOM_ATTRIBUTES))
    {
        return;
    }

    if (!player)
    {
        return;
    }

    auto warden = player->GetSession()->GetWarden();
    if (!warden)
    {
        return;
    }

    auto payloadMgr = warden->GetPayloadMgr();
    if (!payloadMgr)
    {
        return;
    }

    if (payloadMgr->GetPayloadsInQueue())
        payloadMgr->ClearQueuedPayloads();
}

void ItemAttributesListenerScript::OnBeforeSendChatMessage(Player* player, uint32& type, uint32& lang, std::string& msg)
{
    if (!sWorld->getBoolConfig(CONFIG_ITEM_CUSTOM_ATTRIBUTES))
    {
        return;
    }

    if (!player)
    {
        return;
    }

    auto warden = player->GetSession()->GetWarden();
    if (!warden)
    {
        return;
    }

    auto payloadMgr = warden->GetPayloadMgr();
    if (!payloadMgr)
    {
        return;
    }

    if (type != CHAT_MSG_WHISPER)
    {
        return;
    }

    if (lang != LANG_ADDON)
    {
        return;
    }

    auto data = sItemAttrHelper->Split(msg, '\t');

    auto prefix = data[0];
    auto event = data[1];

    if (prefix != "wltx")
    {
        return;
    }

    if (event != "reload")
    {
        return;
    }

    SendChunkedPayload(warden, payloadMgr, _listenerPayload, 128);
}
