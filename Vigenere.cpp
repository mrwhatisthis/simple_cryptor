#include "Vigenere.h"

std::string getVigenereKeyFromFile(std::string keyName)
{
	std::ifstream keyFile(keyName + ".pub.key");
	std::string line;
	getline(keyFile, line);
	if (line.length() == 0)
	{
		keyFile.close();
		return "0";
	}
	for (const char& ch : line)
	{
		if (!isalpha(ch))
		{
			keyFile.close();
			return "0";
		}
	}
	keyFile.close();
	return line;
}

void encryptVigenere(std::string fileToEncrypt, std::string keyFileName)
{
	std::string key = getVigenereKeyFromFile(keyFileName);

	if (!isalpha(key[0]))
	{
		system("cls");
		std::cout << "Invalid key for vigenere cipher" << std::endl;
		_getch();
		return;
	}

	std::string encryptedFileName = "output.txt";
	std::ifstream encryptingFile(fileToEncrypt, std::ios::in);
	if (!encryptingFile.is_open())
	{
		std::cerr << "Can't open file" << std::endl;
		_getch();
		return;
	}

	std::ofstream encryptedFile(encryptedFileName, std::ios::out);
	if (!encryptedFile.is_open())
	{
		std::cerr << "Can't create file" << std::endl;
		_getch();
		return;
	}

	int keyCounter = 0;
	char* buffer = new char;
	system("cls");
	while (encryptingFile.read(buffer, sizeof(char)))
	{
		if (*buffer >= 65 && *buffer <= 90)
		{
			*buffer = ((*buffer - 65) + (key[keyCounter] - 97)) % 26;
			*buffer += 65;
			keyCounter = (keyCounter + 1) % key.length();
		}
		else if (*buffer >= 97 && *buffer <= 122)
		{
			*buffer = ((*buffer - 97) + (key[keyCounter] - 97)) % 26;
			*buffer += 97;
			keyCounter = (keyCounter + 1) % key.length();
		}
		std::cout << *buffer;
		encryptedFile.write(buffer, sizeof(char));
	}
	_getch();
	encryptingFile.close();
	encryptedFile.close();
	delete buffer;
}


void decryptVigenere(std::string fileToDecrypt, std::string key)
{

	for (char& ch : key)
	{
		if (!isalpha(ch))
		{
			std::cerr << "Invalid key." << std::endl;
			exit(2);
		}
	}

	std::string decryptedFileName = "output.txt";
	std::ifstream decryptingFile(fileToDecrypt, std::ios::in);
	if (!decryptingFile.is_open())
	{
		std::cerr << "Can't open file" << std::endl;
		_getch();
		return;
	}

	std::ofstream decryptedFile(decryptedFileName, std::ios::out);
	if (!decryptedFile.is_open())
	{
		std::cerr << "Can't create file" << std::endl;
		_getch();
		return;
	}

	int keyCounter = 0;
	char* buffer = new char;
	system("cls");
	while (decryptingFile.read(buffer, sizeof(char)))
	{
		if (*buffer >= 65 && *buffer <= 90)
		{
			*buffer = ((*buffer - 65) - (key[keyCounter] - 97) + 26) % 26;
			*buffer += 65;
			keyCounter = (keyCounter + 1) % key.length();
		}
		else if (*buffer >= 97 && *buffer <= 122)
		{
			*buffer = ((*buffer + 26 - 97) - (key[keyCounter] - 97) + 26) % 26;
			*buffer += 97;
			keyCounter = (keyCounter + 1) % key.length();
		}
		std::cout << buffer;
		decryptedFile.write(buffer, sizeof(char));
	}
	_getch();
	decryptingFile.close();
	decryptedFile.close();
	delete buffer;
}

//int main()
//{
//	encryptVigener("cryptMe.txt", "qwer");
//	return 0;
//}