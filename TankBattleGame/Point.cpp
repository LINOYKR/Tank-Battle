#include "Point.h"

// Draws the point on screen at (x, y) location us give character
void Point::draw(char ch) {
	gotoxy(x, y);
	if (!g_isSilent) {
		std::cout << ch;
	}

	
}
// Moves the point in one of 8 directions (0-7) or stays in place
// 0-7: U, UR, R, DR, D, DL, L, UL,S
void Point::move(int dir) {
	switch (dir) {
	case 0: // UP
		--y;
		break;
	case 1: // UP-RIGHT
		--y;
		++x;
		break;
	case 2: // RIGHT
		++x;
		break;
	case 3: // DOWN-RIGHT
		++x;
		++y;
		break;
	case 4: // DOWN
		++y;
		break;
	case 5: // DOWN-LEFT
		++y;
		--x;
		break;
	case 6: // LEFT
		--x;
		break;
	case 7: // UP-LEFT
		--x;
		--y;
		break;

	}

	// Wrap around the screen boundaries 
	if (x < toInt(Variables::ZERO)) x = toInt(Variables::MAX_X)-1;
	if (x > toInt(Variables::MAX_X) - 1) x = toInt(Variables::ZERO);
	if (y < toInt(Variables::ZERO)) y = toInt(Variables::MAX_Y) - 1;
	if (y > toInt(Variables::MAX_Y) - 1) y = toInt(Variables::ZERO);

}