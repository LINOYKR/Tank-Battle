#pragma once
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>

#include "Point.h"

class Board
{
	// Board size
	static constexpr int MAX_X = 80;      // Maximum board width
	static constexpr int MAX_Y = 25;      // Maximum board height
	
	char originalBoard[MAX_Y][MAX_X + 1]; // original static board 
	char currentBoard[MAX_Y][MAX_X + 1];  // Current dynamic board
	
	// Starting positions for the two players
	Point player1{ 0, 0 };
	Point player2{ 0, 0 };
	std::vector<Point> player1Tanks;
	std::vector<Point> player2Tanks;

	// Counter players
	int players=0;                   
	int counterPlayer1 = 0;
	int counterPlayer2 = 0;
	Point legendPos{ 0,0 };

	// Incorrect board
	bool invalidboard = false; // Correct board
	std::string errorMessage = "Error: No level files found."; // Notes invalid board
	
	
	bool isValidChar(char c);                  //Correct character on the board

public:

	void load(const std::string& filename);    // Loads a board layout from a text file
	void print() const; 	                   // Displays current state of the board on screen
	void reset(); 	                           // Resets current board to original state
	void setChar(int x, int y, char ch); 	   // Sets character on board 

	char getChar (int x, int y) const { 	       // Retrieves the character  specified (x, y) position
		return currentBoard[y][x];
	}

	Point getLegendPos () const { return legendPos; } //Location legend

	//Returning player tank locations
	const std::vector<Point>& getPY10() const { return player1Tanks; }
    const std::vector<Point>& getPY20() const { return player2Tanks; }

	const bool getInvalidbord() const { return invalidboard; }          //If that invalid board
	const std::string getErrorMessage() const { return errorMessage; }  //Invalid board message
};

