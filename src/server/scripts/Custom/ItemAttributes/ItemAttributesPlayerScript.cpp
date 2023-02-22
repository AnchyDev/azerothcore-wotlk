#include "ItemAttributesPlayerScript.h"
#include "ItemAttributesMgr.h"

void ItemAttributesPlayerScript::OnLootItem(Player* player, Item* item, uint32 /*count*/, ObjectGuid /*lootguid*/)
{
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
}
