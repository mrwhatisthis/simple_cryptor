#include "Dimmention.h"

dimmention getConsoleSize()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	dimmention consoleScreenInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	consoleScreenInfo.columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	consoleScreenInfo.rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	return consoleScreenInfo;
}