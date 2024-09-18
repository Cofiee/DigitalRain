#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <windows.h>

#include "RainMatrix.h"

typedef unsigned char uint8_t;

int main() {
	// SETUP
	srand(20);
	// Change stdout to Unicode UTF-16
	_setmode(_fileno(stdout), _O_U16TEXT);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);
	GetConsoleScreenBufferInfo(hConsole, &csbi);

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsole, &cursorInfo);

	//int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	//int rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	int columns = 186;
	int rows = 44;

	RainMatrix rainMatrix(columns, rows);
	wchar_t* out = new wchar_t[rainMatrix.getStringOutputSize()];
	out[rainMatrix.getMatrixSize()];

	COORD c;
	c.X = 0;
	c.Y = 0;
	while (1) {
		//system("CLS");
		SetConsoleCursorPosition(hConsole, c);
		rainMatrix.fillMatrix(out, rainMatrix.getStringOutputSize());
		//std::wcout << out << std::endl;
		std::wprintf(L"%s", out);
		rainMatrix.nextFrame();
		//Sleep(15);
	}

	delete[] out;
	return 0;
}