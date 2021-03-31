#pragma once
#include <iostream>
#include <string>
#include <cctype>

class Key
{
public:
	unsigned int exponent, module;
	Key() :  exponent(0), module(0) {}
	Key(unsigned int exp, unsigned int mod) : exponent(exp), module(mod) {}
	Key(std::string);
	friend std::ostream& operator<< (std::ostream& output, const Key& keyToWrite);
	friend std::istream& operator>> (std::istream& input, Key& keyToRead);
};

