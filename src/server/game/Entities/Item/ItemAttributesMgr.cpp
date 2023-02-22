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
    attributes.clear();

    QueryResult result = CharacterDatabase.Query("SELECT guid, quality, attr_type_1, attr_val_1, attr_type_2, attr_val_2, attr_type_3, attr_val_3, attr_type_4, attr_val_4, attr_type_5, attr_val_5, attr_type_6, attr_val_6, attr_type_7, attr_val_7, attr_type_8, attr_val_8, attr_type_9, attr_val_9 FROM item_attributes_instance");

    if (result)
    {
        uint32 count = 0;

        do
        {
            Field* fields = result->Fetch();

            uint64 guid = fields[0].Get<uint64>();
            uint32 quality = fields[1].Get<uint32>();

            // TODO: Anchy: Turn this into a loop...

            uint32 attrType1 = fields[2].Get<uint32>();
            float attrValue1 = fields[3].Get<float>();

            uint32 attrType2 = fields[4].Get<uint32>();
            float attrValue2 = fields[5].Get<float>();

            uint32 attrType3 = fields[6].Get<uint32>();
            float attrValue3 = fields[7].Get<float>();

            uint32 attrType4 = fields[8].Get<uint32>();
            float attrValue4 = fields[9].Get<float>();

            uint32 attrType5 = fields[10].Get<uint32>();
            float attrValue5 = fields[11].Get<float>();

            uint32 attrType6 = fields[12].Get<uint32>();
            float attrValue6 = fields[13].Get<float>();

            uint32 attrType7 = fields[14].Get<uint32>();
            float attrValue7 = fields[15].Get<float>();

            uint32 attrType8 = fields[16].Get<uint32>();
            float attrValue8 = fields[17].Get<float>();

            uint32 attrType9 = fields[18].Get<uint32>();
            float attrValue9 = fields[19].Get<float>();

            ObjectGuid fullGuid(guid);
            ItemInformation itemInfo;

            itemInfo.Quality = (AttributeQuality)quality;

            // TODO: Anchy: Include this into a loop...
            itemInfo.Attributes[0].Type = attrType1;
            itemInfo.Attributes[0].Value = attrValue1;

            itemInfo.Attributes[1].Type = attrType2;
            itemInfo.Attributes[1].Value = attrValue2;

            itemInfo.Attributes[2].Type = attrType3;
            itemInfo.Attributes[2].Value = attrValue3;

            itemInfo.Attributes[3].Type = attrType4;
            itemInfo.Attributes[3].Value = attrValue4;

            itemInfo.Attributes[4].Type = attrType5;
            itemInfo.Attributes[4].Value = attrValue5;

            itemInfo.Attributes[5].Type = attrType6;
            itemInfo.Attributes[5].Value = attrValue6;

            itemInfo.Attributes[6].Type = attrType7;
            itemInfo.Attributes[6].Value = attrValue7;

            itemInfo.Attributes[7].Type = attrType8;
            itemInfo.Attributes[7].Value = attrValue8;

            itemInfo.Attributes[8].Type = attrType9;
            itemInfo.Attributes[8].Value = attrValue9;

            attributes.emplace(fullGuid, itemInfo);

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
