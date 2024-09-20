#include<Inventory.h>

void Inventory::create(int size)
{
	*this = {};
	itemsSlots.resize(size);
	armourSlots.resize(5);
	weaponSlots.resize(2);
	quickSlots.resize(7);

	itemsSlots[0].item = Items::pickaxe;
	itemsSlots[0].attributes = getItemType(Items::pickaxe);
	itemsSlots[0].setAttributes(itemsSlots[0].attributes);

	//inventoryrenderer.SetAlignModeFixedSizeWidgets({0,150});
}

void Inventory::addItem(item itm, int idx)
{
	itemsSlots[idx]= itm;
}