#include "Item.h"

void Item::operator()()
{
	this->itemFunc();
}

std::ostream& operator<<(std::ostream& out, Item& obj)
{
	out << obj.name;
	return out;
}