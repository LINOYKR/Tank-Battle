#pragma once
#include "Board.h"
#include "Point.h"
#include "TankShell.h"

#include <random>

#include <cstring>
#include <vector>
#include <windows.h>

constexpr int TWO = 2;

enum Movement {QE=0, AD=4, E=-1, EA=2, Q=1, QD=-2, D=1, A=-1, S=8 };

class Tank {
private:
	Point pos , canon;  //Tank's position and cannon's position
	int direction = 0;  // Direction code: 0-8 for directions: U, UR, R, DR, D, DL, L, UL,S
	int addDir = 0;
	int numShells=0;    // Number of active shells
	int causeOfDeath;//0-HIT_TANK,1-HIT_CANNON,2-MINE,3-END_LEVEL
	
	Colors color= Colors::WHITE;
	
	bool testResults = false;       //Whether a test was performed, the results were printed or not
	bool rightTrack = false;        // Indicates if the right track is moving
	bool leftTrack = false;         // Indicates if the left track is moving
	bool stayTrack = true;          // True if tank is staying in place
	bool canonExist = true;         // Whether the cannon is active
	bool canMove = true;            // If the tank is allowed to move
	bool dead = false;              // Whether the tank has been destroyed
	bool Shot = false;              // Indicates if the tank shot a shell this turn
	bool BackwardOrForward = false; // Traveling backwards or forwards


	char rightArrowKeys[TWO];    // Keys to control right track
	char leftArrowKeys[TWO];     // Keys to control left track
	char stayShootArrowKeys[TWO];// Keys to stay or shoot
	char Movement[TWO];          // Stores current movement input
	char symbol;                 // Tank's symbol on screen

	Board* board = nullptr; // Pointer to the game board
	TankShell Shells[5];    // Array of active shells (max 5)
	
	// Visual symbols for each direction
	const char* directionSymbols[8] = { "|", "/", "-", "\\", "|", "/", "-", "\\" };


	void addTankShell();                             //Adds a new active shell if available.
	void moveCanon();                                //Moves the cannon if possible.
	
	void setPY(Point start) { pos = start; }         //Sets the tank's position.
	void setPYcanon(Point start);                    //Sets the cannon's position. is staying.
	void setStay(bool stay);                         //Sets tank is stay.
	
	bool canMoveTo();                                //Checks if the tank can move
	
	int randomDirection();                           // Finding a random number

public:

	void reset();
	void booleanReset();                              // Resets all tank movement flags.
	void explode(int x, int y)const;                  // Explosion animation
	void move();                                      // Moves the tank and cannon, handles shooting and drawing.
    void movingActiveShells();                        // Moves active shells and updates board.
    void shellExplosion(int num);                     // Handles shell explosion
    void startPositions(Point player, Board& b);      // Initializes tank's and cannon's starting position
	
	//Setters
	void setArrowKeys(const char* keys);              // Sets the control keys for the tank.
	void setBoard(Board& b) { board = &b; }           // Sets the pointer to the game board.
    void setCanonExist(bool is) { canonExist = is; }  // Set enables or disables the cannon
	void setDirection(int dir);                       // Sets the tank's direction
    void setLostLife(bool is) { dead = is; }          // Marks the tank as destroyed/alive.
	void setCauseOfDeath(int is) { causeOfDeath = is; }
	void setColor(Colors it) { color = it; }          // Determining the color of the tank
	void setStayTrack(bool is) { stayTrack=is; }      // Switch to stay mode
	void setShot(bool is) { Shot = is; }              // Determines whether to fire
	void setTestResults(){testResults=true; }         // Determines whether results were executed
	void setBackwardOrForward(bool is) { BackwardOrForward = is; } // Determines whether to move forward or backward
	
    //Getters
	bool getCanonExist () const { return canonExist; }       // return True if the cannon is active.
	bool getLostLife () const { return dead; }               // return True if the tank is destroyed.
	bool getStay () const { return stayTrack; }              // return True if the tank is staying in place.
    bool shellHitsTank(Point pos);                           // Checks if a shell has hit a specific point
	bool getShot() const { return Shot; }                    // Shot
	bool getTestResults() const { return testResults; }      // Did you print results?
	bool getBackwardOrForward() const { return BackwardOrForward; }   // Move forward or backward
	
	int getDir() const { return direction; }            // return The current direction code.
	int getDirection();                                 // Determines the direction based on movement input.
	int getMovement(char key);                          // Updates movement state based on key input
	int getCauseOfDeath() { return causeOfDeath; }      // Cause of death

	Colors getColor() const { return color; }              // Bring back the tank color
	Point getCanon() const { return canon; }               // return Cannon position.
	Point getPos() const { return pos; }              // return Tank position.
	
	TankShell getShell(int num) const { return  Shells[num]; } // Returns the shell at a given index.
	
	//Auxiliary functions Start direction of movement-Random
	void setAddDir(int add) { addDir = add; }                // Add to traffic direction
	int getAddDir() const { return addDir; }                 // Return some to add
	int getNumShells() const { return numShells; }           // Return number of tanks for the player
	
	//Movement operations
	int forward();
	int Backward();
	int Right45degrees();
	int Left45degrees();
	int Right90degrees();
	int Left90degrees();
	int StayTank();
};
