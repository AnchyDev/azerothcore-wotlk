#include "ItemAttributesCommon.h"

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

ItemAttributesHelper* ItemAttributesHelper::GetInstance()
{
    static ItemAttributesHelper instance;
    return &instance;
}

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
