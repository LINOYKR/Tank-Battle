#pragma once
#include "Board.h"
#include "Point.h"
#include "Tank.h"
#include "Utils.h"
#include "Player.h"
#include "ComputerPlayer.h"

#include <cstdlib>
#include <conio.h>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>


class Game
{
private:
	int modeGame = 0; //MODE
	//Board board;
	bool waitForInput = true;    // Wait for key press 
	bool isSilent = false;
	bool loadGame = false;
	// Displays message 
	void displayErrorMessage(const std::string& errorDetails);
	void displayVictoryMessage(const std::string& errorDetails);             
	void displayEndAllGameWin();
	
	void getAllBoardFileNames (std::vector<std::string>& vec_to_fill);	    // Upload available boards	                   

	void entityMeeting(Player& play1, Player& play2);	                    // Handles interactions between tanks-shells 
	void shellsMeeting(Player& play1, Player& play2);                       // Handles collisions between active shells 
	
	bool managePause(bool& isPaused, char& key);	                        // Manages game pause 
	bool tankClash(int tank);                                               // Checks if a tank collide
	void setWaitForInput() { waitForInput = false; }                        // Disables waitForInput variable
	
protected:
	//Number of interactions
	size_t iteration = 0;
	//Players
	Player* player1;
	Player* player2;
	//Virtual functions
	virtual void initializeGame(const std::string& filename); //Define game by mode
	virtual void tankCrossing(int player);                    //Swapping tanks by mod
	virtual void moveOrShoot(Player& play, int num);          //Move and shoot according to mode
	virtual void allTanksDead();                              //Dead tank inspection and treatment according to mod
	virtual void endLevel();                                  //End stage by mode
	
	virtual void createPlayers();                             //Creating an Players
	virtual size_t chooseStartingLevel(const std::vector<std::string>& fileNames);  //Selecting a starting board
	virtual void loadingDirectionFromFile();                  //Load command from file

public:
	~Game();
	virtual void run(); 	                      // Game loop
	void setloadGame() { loadGame = true; }      //Go to charging mode
	void setSilentMode() { isSilent = true; }   //Switch to silent mode
};

