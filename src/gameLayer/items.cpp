#include<items.h>

int getItemType(Item item)
{
	permaAssert(item < Items::ITEMS_COUNT);
	permaAssert(item >= 0);

	static int itemFlags[] =  // SET ITEM TYPE NOT QUALITY
	{
		(ItemType::ITEM_TYPE_NONUSABLE),
		(ItemType::ITEM_TYPE_USABLE),
		(ItemType::ITEM_TYPE_USABLE),
		(ItemType::ITEM_TYPE_USABLE),
		(ItemType::ITEM_TYPE_USABLE | ITEM_TYPE_CONSUMABLE | ITEM_TYPE_CRAFTABLE),
		(ItemType::ITEM_TYPE_USABLE | ITEM_TYPE_CONSUMABLE | ITEM_TYPE_CRAFTABLE),
		(ItemType::ITEM_TYPE_USABLE | ITEM_TYPE_BUILDING | ITEM_TYPE_CRAFTABLE),
		(ItemType::ITEM_TYPE_USABLE | ITEM_TYPE_BUILDING | ITEM_TYPE_CRAFTABLE),
		(ItemType::ITEM_TYPE_USABLE | ITEM_TYPE_BUILDING | ITEM_TYPE_CRAFTABLE),

	};
	static_assert(sizeof(itemFlags) / sizeof(itemFlags[0])
		== Items::ITEMS_COUNT);

	return itemFlags[item];
}

void item:: setAttributes(int flags)
{
	//check conflicting flags and then modify
}