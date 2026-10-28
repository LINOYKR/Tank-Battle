#pragma once
#ifndef POINT_H
#define POINT_H

#include "Utils.h"


class Point {
	int x , y ; // Default position is (1,1)
	
public:
	Point(int _x = 0, int _y = 0) : x(_x), y(_y) {} // Constructor with default values (0, 0)

	void draw (char ch) ; // Draw point on screen
	void move(int direction);// Moves the point - direction (0-7)
	
	// Comparison operators
	bool operator!=(const Point& other) const {
		return !(*this == other);
	}
	bool operator==(const Point& other) const {
		return x == other.x && y == other.y;
	}

	// Getters
	int getX() const { return x; }
	int getY() const { return y; }
	 
	// Setters
	void setX(int newX) { x = newX; }
	void setY(int newY) { y = newY; }

	

};

#endif  // POINT_H

