#pragma once
#include "Item.h"
#include "Dimmention.h"
#include <string>
#include <conio.h>

class Input : protected Item
{
	std::string printedContent;
	void(*strOut)(std::string str);
	int mode;
	void renderLarge();
	void renderSmall();
public:
	Input(std::string itemName, std::string text, int mode, void(*func)(std::string str), void(*afterFunc)() = nullptr);
	void getLargeInput();
	void getSmallInput();
	void operator()();
};
