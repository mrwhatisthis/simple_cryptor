#include "RSA.h"

Bint modexp(Bint x,unsigned int y,unsigned int N)
{
	if (y == 0) return 1;
	Bint z = modexp(x, y / 2, N);
	if (y % 2 == 0)
		return (z * z) % N;
	else
		return (z * z * x) % N;
}

void encryptRSA(std::string fileToCrypt, std::string keyName)
{
	std::string cryptedFileName = "output.txt";
	std::string keyFileName = keyName + ".pub.key";

	std::ifstream cryptingFile(fileToCrypt, std::ios::binary | std::ios::in);
	std::ifstream keyFile(keyFileName, std::ios::in);

	if (!cryptingFile.is_open() || !keyFile.is_open())
	{
		std::cerr << "Can't open file" << std::endl;
		_getch();
		return;
	}

	std::ofstream cryptedFile(cryptedFileName, std::ios::binary | std::ios::out);

	if (!cryptedFile.is_open())
	{
		std::cerr << "Can't create file." << std::endl;
		_getch();
		return;
	}

	Key crptKey;
	keyFile >> crptKey;
	if (crptKey.module == 0)
	{
		system("cls");
		std::cout << "Wrong key format" << std::endl;
		_getch();
		return;
	}
	system("cls");
	char* buffer = new char;
	while (cryptingFile.read(buffer, sizeof(char)))
	{
		//cryptingFile.read(buffer, sizeof(char));
		Bint crSeq = (int)(*buffer);
		crSeq = modexp(crSeq, crptKey.exponent, crptKey.module);
		long long writable = crSeq.toLong();
		std::cout << reinterpret_cast<const char*>(&writable);
		cryptedFile.write(reinterpret_cast<const char *>(&writable), sizeof(writable));
	}
	_getch();
	cryptedFile.close();
	cryptingFile.close();
	keyFile.close();
	delete buffer;
}

void decryptRSA(std::string fileToDecrypt, std::string keyName)
{
	std::string decryptedFileName = "output.txt";
	std::string keyFileName = keyName + ".priv.key";

	std::ifstream decryptingFile(fileToDecrypt, std::ios::binary | std::ios::in);
	std::ifstream keyFile(keyFileName, std::ios::in);

	if (!decryptingFile.is_open() || !keyFile.is_open())
	{
		std::cerr << "Can't open file" << std::endl;
		_getch();
		return;
	}

	std::ofstream decryptedFile(decryptedFileName, std::ios::binary | std::ios::out);

	if (!decryptedFile.is_open())
	{
		std::cerr << "Can't create file" << std::endl;
		_getch();
		return;
	}

	Key crptKey;
	keyFile >> crptKey;

	char* buffer = new char[sizeof(long long)];
	system("cls");
	while (decryptingFile.read(buffer, sizeof(long long)))
	{
		//decryptingFile.read(buffer, sizeof(long long));
		Bint dcrSeq = *((long long*)buffer);
		dcrSeq = modexp(dcrSeq, crptKey.exponent, crptKey.module);
		char writable = (char)(dcrSeq.toLong());
		std::cout << writable;
		decryptedFile.write((char*)&writable, sizeof(writable));
	}
	_getch();
	decryptedFile.close();
	decryptingFile.close();
	keyFile.close();
	delete[] buffer;
}
