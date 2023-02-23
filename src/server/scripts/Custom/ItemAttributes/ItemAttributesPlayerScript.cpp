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
#include "ItemAttributesMgr.h"
#include "Chat.h"

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
