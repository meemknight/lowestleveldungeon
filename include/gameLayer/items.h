#pragma once

#include <vector>
#include<blocks.h>

namespace Items
{
	enum
	{
		none=0,
		pickaxe,//= Blocks::BLOCKS_COUNT-1,
		axe,
		sword,
		meat,
		water,
		wood,
		stone,
		soil,
		ITEMS_COUNT //= (soil+2) - pickaxe
	};
}
using Item = int;

typedef enum {
    ITEM_TYPE_USABLE = 1 << 0,
    ITEM_TYPE_NONUSABLE = 1 << 1,
    ITEM_TYPE_CRAFTABLE = 1 << 2,
    ITEM_TYPE_BUILDING = 1 << 3,
    ITEM_TYPE_WEARABLE = 1 << 4,
    ITEM_TYPE_CONSUMABLE = 1 << 5,

    // for setting item quality

    ITEM_QUALITY_HIGH  = 1 << 6,
    ITEM_QUALITY_NORMAL = 1 << 7,
    ITEM_QUALITY_LOW = 1 << 8
} ItemType;


int getItemType(Item);

typedef struct{

	Item item;
	int attributes;

	void setAttributes(int);
}item;