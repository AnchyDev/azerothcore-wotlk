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

#ifndef _ITEM_ATTRIBUTES_COMMON_H
#define _ITEM_ATTRIBUTES_COMMON_H

class ItemAttributesHelper
{
private:
    ItemAttributesHelper() { }
public:
    static ItemAttributesHelper* GetInstance();
public:
    std::vector<std::string> Split(const std::string& /*s*/, char /*delimiter*/);
    std::vector<std::string> GetChunks(std::string /*s*/, uint8_t /*chunkSize*/);
    WorldPacket CreateAddonPacket(std::string const& prefix, std::string const& msg, ChatMsg msgType, Player* player);
    std::vector<WorldPacket> CreateAddonPackets(std::string const& prefix, std::string const& msg, ChatMsg msgType, Player* player);
};

#define sItemAttrHelper ItemAttributesHelper::GetInstance()

#endif
