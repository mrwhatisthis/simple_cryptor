#include "Input.h"

Input::Input(std::string itemName, std::string text, int mode, void(*func)(std::string str), void(*afterFunc)()) 
	: mode(mode), strOut(func)
{
	name = itemName;
	description = text;
	itemFunc = afterFunc;
}

void Input::renderLarge()
{
	system("cls");
	dimmention dimm = getConsoleSize();
	std::cout << name;
	if (dimm.columns - name.length() < 32)
	{
		std::cout << std::endl << "Press CTRL+X to stop input text";
	}
	else
	{
		for (int i = name.length(); i < dimm.columns - 31; ++i)
		{ std::cout << ' '; }
		std::cout << "Press CTRL+X to stop input text";
	}
	std::cout << std::endl;
	for (int i = 0; i < dimm.columns; ++i)
	{
		std::cout << '_';
	}
	std::cout << std::endl << std::endl;
	std::cout << printedContent;
}

void Input::renderSmall()
{
	system("cls");
	dimmention dimm = getConsoleSize();
	std::cout << name << std::endl;
	for (int i = 0; i < dimm.columns; ++i)
	{ std::cout << '_'; }
	std::cout << std::endl << std::endl;
	std::string outDescription = description;
	int writedRows = 4;
	for (int i = 0; i < description.length(); ++i)
	{
		if (description[i] == '\n' || (i / dimm.columns) > 0)
		{ ++writedRows; }
	}
	outDescription.resize(((dimm.rows - writedRows) * dimm.columns), ' ');
	std::cout << outDescription << std::endl;
	std::cout << printedContent;
}

void Input::getLargeInput()
{
	renderLarge();
	char c;
	dimmention dimm = getConsoleSize();
	while (true)
	{
		c = _getch();
		if (c == -32)
		{
			_getch();
			continue;
		}
		if (c == 13)
		{
			std::cout << std::endl;
			printedContent += '\n';
		}
		else if (c == 8)
		{
			if (printedContent.length() != 0)
			{
				printedContent.resize(printedContent.length() - 1);
			}
			renderLarge();
		}
		else if (c == 24)
		{
			system("cls");
			std::cout << printedContent << std::endl;
			for (int i = 0; i < dimm.columns; ++i)
			{ std::cout << '_'; }
			std::cout << std::endl;
			strOut(printedContent);
			if (itemFunc != nullptr)
			{ itemFunc(); }
			break;
		}
		else if(c == 27)
		{ break; }
		else if (c >= 32 && c <= 126)
		{
			std::cout << c;
			printedContent += c;
		}
	}
}

void Input::getSmallInput()
{
	renderSmall();
	char c;
	while (true)
	{
		c = _getch();
		if (c == -32)
		{
			_getch();
			continue;
		}
		if (c == 13)
		{
			std::cout << std::endl;
			strOut(printedContent);
			if (itemFunc != nullptr)
			{ itemFunc(); }
			break;
		}
		else if (c == 8)
		{
			if (printedContent.length() != 0)
			{
				printedContent.resize(printedContent.length() - 1);
			}
			renderSmall();
		}
		else if (c == 27)
		{ break; }
		else if (c >= 32 && c <= 126)
		{
			std::cout << c;
			printedContent += c;
		}
	}
}

void Input::operator()()
{
	if (mode == 0)
	{
		getSmallInput();
	}
	else if (mode == 1)
	{
		getLargeInput();
	}
}