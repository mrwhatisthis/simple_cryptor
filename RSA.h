#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include "keyGen.h"
#include "Key.h"
#include "Bint.h"

Bint modexp(Bint x, unsigned int y, unsigned int N);

void encryptRSA(std::string fileToCrypt, std::string keyName);

void decryptRSA(std::string fileToDecrypt, std::string keyName);

