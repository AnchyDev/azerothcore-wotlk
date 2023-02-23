/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ItemAttributesPlayerScript.h"
#include "ItemAttributesCommon.h"
#include "ItemAttributesMgr.h"
#include "Chat.h"
#include "Warden.h"

void ItemAttributesPlayerScript::OnLootItem(Player* player, Item* item, uint32 /*count*/, ObjectGuid /*lootguid*/)
{
    if (!sWorld->getBoolConfig(CONFIG_ITEM_CUSTOM_ATTRIBUTES))
    {
        return;
    }

    if (!player)
    {
        return;
    }

    if (!item)
    {
        return;
    }

    ItemInformation itemInfo;

    itemInfo.Quality = ITEM_ATTR_QUALITY_HIGH;

    // + 50 Stamina Test
    itemInfo.Attributes[0].Type = 7;
    itemInfo.Attributes[0].Value = 50;

    sItemAttrMgr->AddItemInfo(item, itemInfo);

    ChatHandler(player->GetSession()).SendSysMessage("Test");
}

void ItemAttributesPlayerScript::OnBeforeSendChatMessage(Player* player, uint32& type, uint32& lang, std::string& msg)
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

    if (data.size() < 3)
    {
        LOG_WARN("module", "Didn't receive guid. String: {}", msg);
        return;
    }
    auto sguid = data[2];

    if (prefix != "wltx")
    {
        return;
    }

    if (event != "reqitem")
    {
        return;
    }

    std::istringstream reader(sguid);
    uint32 guid = 0;
    reader >> guid;

    std::string payloadPrefix = "wlrx";
    std::string payload = Acore::StringFormatFmt("itemCache['{}'] = {{ ['suffix'] = 'Hello World', ['quality'] = 'Fantastic' }};", guid);
    auto packets = sItemAttrHelper->CreateAddonPackets(payloadPrefix, payload, CHAT_MSG_WHISPER, player);
    LOG_INFO("module", "Got req for item info for guid '{}'.", guid);
    for (const auto& packet : packets)
    {
        player->SendDirectMessage(&packet);
    }
}
