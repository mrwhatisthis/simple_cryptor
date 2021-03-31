#include "Main.h"

using namespace std;


void encryptDecrypt()
{
	vector<Item> chooseCipherToEncryptMenuItems = { {"RSA", []() { encryptRSA("workingData.txt", "workingKey"); }},
													{"Vigenere", []() { encryptVigenere("workingData.txt", "workingKey"); }},
													{"Gronsfeld", []() {encryptGronsfeld("workingData.txt", "workingKey"); }} };

	vector<Item> chooseCipherToDecryptMenuItems = { {"RSA", []() { decryptRSA("workingData.txt", "workingKey"); }},
													{"Vigenere", []() { decryptVigenere("workingData.txt", "workingKey"); }},
													{"Gronsfeld", []() { decryptGronfeld("workingData.txt", "workingKey"); }} };
	vector<Menu> encryptDecryptMenuItems = { {"Encrypt", chooseCipherToEncryptMenuItems}, {"Decrypt", chooseCipherToDecryptMenuItems} };
	Menu encryptDecryptMenu("Choose action", encryptDecryptMenuItems);
	encryptDecryptMenu();
}

void setWorkingKey()
{
	vector<Item> setWorkingKeyMenuItems =
	{
		{ "Write key manually", []()
			{
				Input inp("Write key manually", "Key formats: \nRSA: exponent:module (only numbers)\nVigenere: key (only letters)\nGronsfeld: key (only numbers)", 0, setWorkingKeyFromString, encryptDecrypt);
				inp();
			}
		},
		{ "Get key from .key file", []()
			{
				Input inp("Write name of the key", "Write key name without extentions.", 0,setWorkingKeyFromFile, encryptDecrypt);
				inp();
			}
		}
	};

	Menu setWorkingKeyMenu("Get key", setWorkingKeyMenuItems);
	setWorkingKeyMenu();
}

void generateKey()
{
	Input inp("Input key name", "Files keyName.pub.key, keyName.priv.key will be created.", 0, [](string keyName) 
		{ 
			system("cls");
			cout << "Generating" << endl;
			generate(keyName); 
			cout << keyName << " is generated." << endl;
			_getch();
		});
	inp();
}

void info()
{
	ifstream infoFile("Info.txt", ios::in);
	if (!infoFile.is_open())
	{
		system("cls");
		cout << "Can't find info file." << endl;
		_getch();
		return;
	}

	string line;
	system("cls");
	while (getline(infoFile, line))
	{
		cout << line << endl;
	}
	infoFile.close();
	_getch();
}

void setWorkingData()
{
	vector<Item> setWorkingDataMenuItems =
	{
		{"Write data manually", []()
			{
				Input inp("Input data", "", 1, setWorkingDataFromString, setWorkingKey);
				inp();
			}
		},
		{"Get data from file", []()
			{
				Input inp("Input file name", "Input full file name with extention.", 0, setWorkingDataFromFile, setWorkingKey);
				inp();
			}			
		}
	};
	Menu setWorkingDataMenu("Set data", setWorkingDataMenuItems, false);
	setWorkingDataMenu();
}

void mainProg()
{
	vector<Item> mainProgramMenuItems =
	{
		{"Start", setWorkingData},
		{"KeyGen", generateKey},
		{"About", info},
		{"Exit", []() { exit(0); } }
	};
	Menu mainProgMenu("Main menu", mainProgramMenuItems, false);
	mainProgMenu();
}

int main()
{
	mainProg();
	return 0;
}