#include "Utils.h"

extern bool g_isColorOn = true;
constexpr int NO_CO = 15;
extern bool g_isSilent=false;

// Moves the cursor to position (x, y) on the console
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	std::cout << std::flush;
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

// Hides the console cursor (so it doesn't blink on screen)
void hideCursor()
{
	HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CURSOR;
	CURSOR.dwSize = 1;
	CURSOR.bVisible = FALSE;
	SetConsoleCursorInfo(myconsole, &CURSOR);//second argument need pointer
}

// Clears the console screen (Windows-specific implementation)
void clearScreen() {
    system("CLS");  // Works for Windows; for other platforms, use appropriate code
}
// Sets the console text color
void setTextColor(Colors colorToSet) {
	if (g_isColorOn) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)colorToSet);
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), NO_CO);
	}
}