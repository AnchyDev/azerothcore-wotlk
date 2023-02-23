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

#include "ItemAttributesMgr.h"

ItemAttributesMgr* ItemAttributesMgr::GetInstance()
{
    static ItemAttributesMgr iAttrMgr;

    return &iAttrMgr;
}

void ItemAttributesMgr::LoadAttributesTable()
{
    uint32 oldMSTime = getMSTime();

    // Clear in case of reload.
    itemInformation.clear();

    QueryResult result = CharacterDatabase.Query("SELECT guid, quality, attr_type_1, attr_val_1, attr_type_2, attr_val_2, attr_type_3, attr_val_3, attr_type_4, attr_val_4, attr_type_5, attr_val_5, attr_type_6, attr_val_6, attr_type_7, attr_val_7, attr_type_8, attr_val_8, attr_type_9, attr_val_9 FROM customattributes_item_instance");

    if (result)
    {
        uint32 count = 0;

        do
        {
            Field* fields = result->Fetch();

            uint64 guid = fields[0].Get<uint64>();
            uint32 quality = fields[1].Get<uint32>();

            ObjectGuid fullGuid(guid);
            ItemInformation itemInfo;

            itemInfo.Quality = (AttributeQuality)quality;

            for (auto i = 0; i < MAX_ITEM_ATTRIBUTES; ++i)
            {
                auto attrIndex = 2 + (i * 2);

                uint32 attrType = fields[attrIndex].Get<uint32>();
                uint32 attrValue = fields[attrIndex + 1].Get<uint32>();

                itemInfo.Attributes[i].Type = attrType;
                itemInfo.Attributes[i].Value = attrValue;
            }

            itemInformation.emplace(fullGuid, itemInfo);

            ++count;
        } while (result->NextRow());

        LOG_INFO("server.loading", ">> Loaded {} Item Attribute(s) in {} ms", count, GetMSTimeDiffToNow(oldMSTime));
        LOG_INFO("server.loading", " ");
    }
    else
    {
        LOG_WARN("server.loading", ">> Loaded 0 Item Attribute(s). DB table `item_attribute_instance` is empty.");
        LOG_INFO("server.loading", " ");
    }
}

ItemInformation* ItemAttributesMgr::GetItemInfo(Item* item)
{
    if (!item)
    {
        return nullptr;
    }

    auto it = itemInformation.find(item->GetGUID());
    if (it == itemInformation.end())
    {
        return nullptr;
    }

    return &it->second;;
}

bool ItemAttributesMgr::AddItemInfo(Item* item, ItemInformation itemInfo)
{
    if (!item)
    {
        return false;
    }

    itemInformation.emplace(item->GetGUID(), itemInfo);

    return true;
}
