#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <conio.h>

std::string getGronsfeldKeyFromFile(std::string keyName);

void encryptGronsfeld(std::string fileToEncrypt, std::string key);

void decryptGronfeld(std::string fileToDecrypt, std::string key);