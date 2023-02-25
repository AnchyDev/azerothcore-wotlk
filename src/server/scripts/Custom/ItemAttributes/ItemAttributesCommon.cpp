#include "ItemAttributesCommon.h"
#include "ItemAttributesMgr.h"

/*



WorldPacket ItemAttributesHelper::CreateAddonPacket(std::string const& prefix, std::string const& msg, ChatMsg msgType, Player* player)
{
    WorldPacket data;

    std::string fullMsg = prefix + "\t" + msg;
    size_t len = fullMsg.length();

    data.Initialize(SMSG_MESSAGECHAT, 1 + 4 + 8 + 4 + 8 + 4 + 1 + len + 1);
    data << uint8(msgType); //Type
    data << uint32(LANG_ADDON); //Lang
    data << uint64(player->GetGUID().GetRawValue()); //SenderGUID
    data << uint32(0); //Flags
    data << uint64(player->GetGUID().GetRawValue()); //ReceiverGUID
    data << uint32(len + 1); //MsgLen
    data << fullMsg; //Msg
    data << uint8(0);

    return data;
}

std::vector<WorldPacket> ItemAttributesHelper::CreateAddonPackets(std::string const& prefix, std::string const& msg, ChatMsg msgType, Player* player)
{
    auto chunks = GetChunks(msg, 128);

    std::vector<WorldPacket> packets;

    for (auto chunk : chunks)
    {
        packets.push_back(CreateAddonPacket(prefix, chunk, msgType, player));
    }

    return packets;
}






std::string ItemAttributesHelper::CreateItemInfoPayload(uint32 guid, uint32 suffix, uint32 rarity, std::vector<uint32> mods)
{
    std::string payload = "";

    std::string sSuffix = GetSuffixName(suffix);
    std::string sRarity = GetRarityName(rarity);

    return payload;
}*/

ItemAttributesHelper* ItemAttributesHelper::GetInstance()
{
    static ItemAttributesHelper instance;
    return &instance;
}

std::vector<std::string> ItemAttributesHelper::Split(const std::string& s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<std::string> ItemAttributesHelper::GetChunks(std::string s, uint8_t chunkSize)
{
    std::vector<std::string> chunks;

    for (uint32_t i = 0; i < s.size(); i += chunkSize)
    {
        chunks.push_back(s.substr(i, chunkSize));
    }

    return chunks;
}

std::string ItemAttributesHelper::GetSuffixName(uint32 suffix)
{
    std::string suffixName = "";
    auto it = sItemAttrAttributeStore->find(suffix);

    if (it == sItemAttrAttributeStore->end())
    {
        suffixName = "UNDEFINED";
        return suffixName;
    }

    suffixName = it->second.Name;

    return suffixName;
}

std::string ItemAttributesHelper::GetRarityName(uint32 rarity)
{
    std::string rarityName = "";

    switch (rarity)
    {
    case AttributeRarity::SUFFIX_RARITY_POOR:
        rarityName = "Poor";
        break;

    case AttributeRarity::SUFFIX_RARITY_COMMON:
        rarityName = "Common";
        break;

    case AttributeRarity::SUFFIX_RARITY_UNCOMMON:
        rarityName = "Uncommon";
        break;

    case AttributeRarity::SUFFIX_RARITY_RARE:
        rarityName = "Rare";
        break;

    case AttributeRarity::SUFFIX_RARITY_EPIC:
        rarityName = "Epic";
        break;

    case AttributeRarity::SUFFIX_RARITY_LEGENDARY:
        rarityName = "Legendary";
        break;

    default:
        rarityName = "UNDEFINED";
    }

    return rarityName;
}

ItemAttributeInfo* ItemAttributesHelper::GetRandomSuffix()
{
    std::vector<uint32> keyStore;

    for (const auto& key : *sItemAttrAttributeStore)
    {
        keyStore.push_back(key.first);
    }

    std::shuffle(keyStore.begin(), keyStore.end(), RandomEngine::Instance());

    return &sItemAttrAttributeStore->find(keyStore[0])->second;
}
