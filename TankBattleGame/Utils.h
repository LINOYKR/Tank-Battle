#pragma once

#include <conio.h>
#include <iostream>
#include <string>
#include <windows.h>

#include "Point.h"
//using namespace std;

//Colors
enum class Colors
{
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHTGREY = 7,
	DARKGREY = 8,
	LIGHTBLUE = 9,
	LIGHTGREEN = 10,
	LIGHTCYAN = 11,
	LIGHTRED = 12,
	LIGHTMAGENTA = 13,
	YELLOW = 14,
	WHITE = 15
};
//Variables
enum class Variables : int {
	VICTORY_POINT = 100,
	HIT_POINT = 50,
	MAX_X = 80,      // Maximum board width
	MAX_Y = 25,
	ZERO = 0,
	BEEP10=10,
	BEEP100=100,
	BEEP1000=1000
};
//Directions
enum class Directions : int {
	UP=0,
	UR=1,
	RIGHT=2,
	DR=3,
	DOWN=4,
	DL=5,
	LEFT=6,
	UL=7,
	STAY=8
};
//Signs
enum class Characters : char {
	MINE = '@',
	WALL = '#',
	TANK = 'O',
	SPACE = ' ',
	WEAK_WALL = '=',
	ONE = '1',
	TWO = '2',
	LEGEND = 'L',
	BIG_EXIT = 'X',
	SMALL_EXIT='x',
	TANK_SHELL= '*'
};

extern bool g_isColorOn;      // With or without color

extern bool g_isSilent;
void clearScreen();           // Clears the console screen
void gotoxy(int x, int y);    // Moves the cursor to position 
void hideCursor();            // Hides the blinking console cursor
void setTextColor(Colors);    // Sets the console text color

// Convert to character
inline char toChar(Characters ch) {
	return static_cast<char>(ch);
}
// Convert Variables to a number
inline int toInt(Variables v) {
	return static_cast<int>(v);
}
// Convert Directions to a number
inline int toIntDir(Directions v) {
	return static_cast<int>(v);
}


