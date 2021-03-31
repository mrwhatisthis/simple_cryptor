#pragma once
#include <string>
#include <iostream>

class Item
{

protected:
	std::string name;
	std::string description;
	void (*itemFunc)();
public:
	Item() : name(""), description(""), itemFunc(nullptr) {}
	Item(std::string itemName, void (*func)()) : name(itemName), description(""), itemFunc(func) {}
	virtual void operator()();
	friend std::ostream& operator<<(std::ostream& out, Item& obj);
};

