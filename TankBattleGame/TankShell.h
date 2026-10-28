#pragma once
#include "Board.h"
#include "Point.h"

#include <cstring>

class TankShell
{
	Point pos,prev;      // Current and previous position of the shell
	int direction = 0;   // Direction in which the shell is moving (0–7 based on move rules)

	bool hit = false;    // True if the shell hit something
	bool active = false; // Indicates if shell is currently active

public:
	void movePos();                                       // Move the shell in its direction
	void setActive(bool ac) { active = ac; }              // Set whether the shell is active
	void setDir(int dir) { direction = dir; }             // Set the direction of the shell
	void setPos(Point Location) { pos = Location; }       // Set current position shell
	void setPrev(Point Location) { prev = Location; }     // Set the previous position
	void reset() { direction = 0; active = false; }       // Reset variables
	bool isActive() const { return active; }              // Check if the shell is active

	int getDirection()const { return direction; }
	Point  getPos() const{ return pos; }                        // Get the current position of the shell
	Point  getPrev() const{ return prev; }                      // Get the previous position of the shell

};

