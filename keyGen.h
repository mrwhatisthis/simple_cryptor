#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <string>
#include "Key.h"

int gratestCommonFactor(unsigned int a, unsigned int b);

void primeFileGen(unsigned int lowLimit, unsigned int highLimit);

std::vector<unsigned int>* fillVectorFromPrimeFile();

unsigned int calculateInverseNumber(unsigned int number, unsigned int module);

void keyGen(std::vector<unsigned int>* primesVector, std::string keyName);

void generate(std::string fileName, unsigned int lowLimit = 1000, unsigned int highLimit = 10000);
