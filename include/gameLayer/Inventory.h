#pragma once

#include <vector>
#include <items.h>
#include <glui/glui.h>



typedef enum {
    ACTION_USE,
    ACTION_CRAFT
} ActionType;

struct Inventory
{
	std::vector<item> itemsSlots;
	std::vector<item> armourSlots;
	std::vector<item> weaponSlots;
	std::vector<item> quickSlots;
	void create(int);
	void populateInv(); //creates items in an entity's inventory when interacted for the first time or during world gen
	void useItem(int idx);

	void addItem(item, int idx);
	item craftItem(const item** items);
	void performAction(const item item_name, ActionType action);
	
	static glui::RendererUi inventoryrenderer;

	
};