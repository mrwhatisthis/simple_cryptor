#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <conio.h>

std::string getVigenereKeyFromFile(std::string keyName);

void encryptVigenere(std::string fileToEncrypt, std::string key);

void decryptVigenere(std::string fileToDecrypt, std::string key);