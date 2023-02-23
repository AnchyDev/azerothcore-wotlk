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

#ifndef _ITEM_ATTRIBUTES_MGR_H
#define _ITEM_ATTRIBUTES_MGR_H

static constexpr uint32 MAX_ITEM_ATTRIBUTES = 9;

enum AttributeRarity
{
    SUFFIX_RARITY_POOR = 0,
    SUFFIX_RARITY_COMMON = 1,
    SUFFIX_RARITY_UNCOMMON = 2,
    SUFFIX_RARITY_RARE = 3,
    SUFFIX_RARITY_EPIC = 4,
    SUFFIX_RARITY_LEGENDARY = 5
};

struct ItemAttribute
{
    uint32 Type;
};

struct ItemAttributeInfo
{
    uint32 Id;
    uint32 Rarity;
    std::string Name;
    std::string Icon;
    ItemAttribute Attributes[MAX_ITEM_ATTRIBUTES];
};

//TODO: REMOVE
struct ItemInformation
{
    std::string Name;
    AttributeRarity Quality;
    ItemAttribute Attributes[MAX_ITEM_ATTRIBUTES];
};

class ItemAttributesMgr
{
private:
    ItemAttributesMgr() { }

public:
    void LoadAttributesTable();
    ItemInformation* GetItemInfo(Item* /*item*/);
    bool AddItemInfo(Item* item, ItemInformation /*itemInfo*/);

    void LoadAttributeTemplates();
    std::map<uint32, ItemAttributeInfo>* GetAttributeTemplates();

public:
    static ItemAttributesMgr* GetInstance();

private:
    std::map<ObjectGuid, ItemInformation> itemInformation;
    std::map<uint32, ItemAttributeInfo> customAttributesTemplate;
};

#define sItemAttrMgr ItemAttributesMgr::GetInstance()
#define sItemAttrAttributeStore ItemAttributesMgr::GetInstance()->GetAttributeTemplates()

#endif
