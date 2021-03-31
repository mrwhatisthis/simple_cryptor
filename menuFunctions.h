#pragma once

#include "Key.h"
#include "keyGen.h"
#include "RSA.h"
#include "Vigenere.h"
#include "Gronsfeld.h"

void setWorkingDataFromString(std::string str);

void setWorkingDataFromFile(std::string filename);

void setWorkingKeyFromString(std::string str);

void setWorkingKeyFromFile(std::string keyName);