#include "Key.h"
#include "keyGen.h"
#include "RSA.h"
#include "Vigenere.h"
#include "Gronsfeld.h"
#include <conio.h>

using namespace std;

void setWorkingDataFromString(string str)
{
	ofstream data("workingData.txt", ios::out);
	if (!data.is_open())
	{
		system("cls");
		cout << "Can't create file" << endl;
		_getch();
		return;
	}
	data << str;
	data.close();
}

void setWorkingDataFromFile(string filename)
{
	ifstream inputFile(filename, ios::in | ios::binary);
	if (!inputFile.is_open())
	{
		system("cls");
		cout << "Can't open " << filename;
		_getch();
		return;
	}

	ofstream outputFile("workingData.txt", ios::out | ios::binary);
	if (!outputFile.is_open())
	{
		system("cls");
		cout << "Can't create file" << endl;
		_getch();
		return;
	}

	char* buffer = new char;
	while (inputFile.read(buffer, sizeof(char)))
	{
		outputFile.write(buffer, sizeof(char));
	}
	inputFile.close();
	outputFile.close();
	delete buffer;
}


void setWorkingKeyFromString(string str)
{
	ofstream pubKey("workingKey.pub.key", ios::out);
	ofstream privKey("workingKey.priv.key", ios::out);

	if (str.length() == 0)
	{ return; }

	if (!pubKey.is_open() || !privKey.is_open())
	{
		system("cls");
		cout << "Can't create file" << endl;
		_getch();
		return;
	}
	pubKey << str;
	privKey << str;

	pubKey.close();
	privKey.close();
}

void setWorkingKeyFromFile(string keyName)
{
	ifstream pubKeyIn((keyName + ".pub.key"), ios::in);
	ifstream privKeyIn((keyName + ".priv.key"), ios::in);

	if (!privKeyIn.is_open() || !privKeyIn.is_open())
	{
		system("cls");
		cout << "Can't open key file" << endl;
		_getch();
		return;
	}

	ofstream pubKeyOut("workingKey.pub.key", ios::out);
	ofstream privKeyOut("workingKey.priv.key", ios::out);

	if (!pubKeyOut.is_open() || !privKeyOut.is_open())
	{
		system("cls");
		cout << "Can't create file" << endl;
		_getch();
		return;
	}

	char* buffer = new char;
	while (pubKeyIn.read(buffer, sizeof(char)))
	{
		pubKeyOut.write(buffer, sizeof(char));
	}

	while (privKeyIn.read(buffer, sizeof(char)))
	{
		privKeyOut.write(buffer, sizeof(char));
	}
	pubKeyIn.close();
	pubKeyOut.close();
	privKeyIn.close();
	privKeyOut.close();
	delete buffer;
}
