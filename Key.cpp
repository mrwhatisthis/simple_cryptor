#include "Key.h"


std::ostream& operator<< (std::ostream& output, const Key& keyToWrite)
{
	output << keyToWrite.exponent << ":" << keyToWrite.module;
	return output;
}

std::istream& operator>> (std::istream& input, Key& keyToRead)
{
	std::string line;
	std::string exponent, module;
	std::string* elementToFill = &exponent;
	std::getline(input, line);
	if (line.length() == 0)
	{
		keyToRead.module = 0;
		return input;
	}
	for (const char& ch : line)
	{
		if (!(isdigit(ch)) && !(ch == ':'))
		{
			keyToRead.module = 0;
			return input;
		}
		if (ch == ':')
		{
			elementToFill = &module;
		}
		else
		{
			*elementToFill += ch;
		}
	}
	keyToRead.exponent = std::stoul(exponent);
	keyToRead.module = std::stoul(module);
	return input;
}