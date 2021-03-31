#pragma once
#include <Windows.h>


class dimmention
{
public:
	int columns;
	int rows;
};

dimmention getConsoleSize();
