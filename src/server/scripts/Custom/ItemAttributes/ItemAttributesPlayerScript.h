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

#ifndef _ITEM_ATTRIBUTES_PLAYER_SCRIPT_H
#define _ITEM_ATTRIBUTES_PLAYER_SCRIPT_H

#include "ScriptMgr.h"
#include "ItemAttributesMgr.h"

class ItemAttributesPlayerScript : public PlayerScript
{
public:
    ItemAttributesPlayerScript() : PlayerScript("ItemAttributesPlayerScript") { }

private:
    ItemAttributeInfo* GetAttributeInfoFromGuid(uint32 guid);
    void OnLootItem(Player* /*player*/, Item* /*item*/, uint32 /*count*/, ObjectGuid /*lootguid*/) override;
    void OnBeforeSendChatMessage(Player* /*player*/, uint32& /*type*/, uint32& /*lang*/, std::string& /*msg*/) override;
};

#endif
