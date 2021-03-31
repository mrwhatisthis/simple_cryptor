#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include "Item.h"
#include "Dimmention.h"


class Menu : protected Item
{
	std::vector<Item> menuItems;
	std::vector<Menu> itemsInstanceOfMenu;
	int position;
	unsigned int size;
	bool breakAfter;
	void render();
public:
	Menu(std::string itemName, std::vector<Item> items, bool isBreak = true);
	Menu(std::string itemName, std::vector<Menu> items, bool isBreak = true);
	void operator()();
	friend std::ostream& operator<<(std::ostream& out, Menu& obj);
};

