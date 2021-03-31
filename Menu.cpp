#include "Menu.h"

Menu::Menu(std::string itemName, std::vector<Item> items, bool isBreak) 
	: menuItems(items), size(menuItems.size()), position(0), breakAfter(isBreak)
{
	name = itemName;
	description = "";
}

Menu::Menu(std::string itemName, std::vector<Menu> items, bool isBreak)
	: itemsInstanceOfMenu(items), size(itemsInstanceOfMenu.size()), position(0), breakAfter(isBreak)
{
	name = itemName;
	description = "";
}

void Menu::render()
{
	dimmention dimm;
	dimm = getConsoleSize();

	system("cls");
	for (int i = 0; i < (dimm.columns - name.length()) / 2; ++i)
	{ std::cout << ' '; }
	std::cout << name << std::endl;
	for (int i = 0; i < dimm.columns; ++i)
	{ std::cout << '-'; }
	std::cout << std::endl;
	if (menuItems.size() > 0)
	{
		for (int i = 0; i < size; ++i)
		{
			std::cout << ((i == position) ? '>' : ' ') << menuItems[i] << std::endl;
		}
	}
	else if (itemsInstanceOfMenu.size() > 0)
	{
		for (int i = 0; i < size; ++i)
		{
			std::cout << ((i == position) ? '>' : ' ') << itemsInstanceOfMenu[i] << std::endl;
		}
	}
	std::cout << std::endl;
	if (description.length() != 0);
	for (int i = 0; i < dimm.columns; ++i)
	{ std::cout << '_'; }
	std::cout << std::endl;

	//std::cout << description;

	std::cout << std::endl;
}

void Menu::operator()()
{
	char c;
	while (true)
	{
		render();
		c = _getch();
		if (c == -32)
		{
			c = _getch();
			if (c == 72)
			{
				position = (position - 1) % size;
			}
			else if (c == 80)
			{
				position = (position + 1) % size;
			}
		}
		else if (c == 13)
		{
			if (menuItems.size() > 0)
			{ 
				menuItems[position](); 
			}
			else if (itemsInstanceOfMenu.size() > 0)
			{ itemsInstanceOfMenu[position](); }
			if (breakAfter)
			{ break; }
		}
		else if (c == 27)
		{
			return;
		}
	}
}


std::ostream& operator<<(std::ostream& out, Menu& obj)
{
	out << obj.name;
	return out;
}
