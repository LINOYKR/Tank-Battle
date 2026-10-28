#include "Tank.h"
constexpr int SHELLS_NUM = 5;
constexpr int GAME_ROUNDS = 5;
constexpr int SLEEP = 100;

// add a new shell 
void Tank::addTankShell() {
	for (int i = 0; i < SHELLS_NUM; ++i) {
		if (!Shells[i].isActive()) {
			Shells[i].setPos(canon);
			Shells[i].setPrev(canon);
			Shells[i].setActive(true);
			Shells[i].setDir(direction);
			numShells++;
			break; 
		}
	}
}
// Moves the tank's cannon according to the current direction
void Tank::moveCanon() {
	Point prev = canon;
	if (canMove && canonExist) {
		if (!stayTrack) {
			canon = pos;
			canon.move(direction);
			if (prev != pos) {
			   char fromBoard = board->getChar(prev.getX(), prev.getY());
				if (fromBoard == toChar(Characters::TANK)) {
					prev.draw(toChar(Characters::SPACE));
				}
				else if (fromBoard == toChar(Characters::MINE)) {
					setTextColor(Colors::LIGHTRED);
					prev.draw(fromBoard);
				}
				else {
					setTextColor(Colors::WHITE);
					prev.draw(fromBoard);
				}
			  setTextColor(color);
			}
		}
	}
	if (numShells != 0) {
		numShells++;
		if (numShells == GAME_ROUNDS)
			numShells = 0;
	}
	if (canMove && canonExist) {
		if (Shot == true) {
			addTankShell();
			Shot = false;
		}
		canon.draw(directionSymbols[direction][0]);
	}
	hideCursor();
}

//Place a dot of a Canon.
void Tank::setPYcanon(Point start) { 
	canon = start; 
}
// Sets whether the tank is in "stay" mode
void Tank::setStay(bool stay) {
	stayTrack = stay;
}

// Checks if the tank can move forward in its current direction.
bool Tank::canMoveTo() {
	Point temp = pos;
	Point temp1 = canon;
	if (!stayTrack) {
		if(BackwardOrForward){
			temp.move(direction);
			char c1 = board->getChar(temp.getX(), temp.getY());
			if (c1 == toChar(Characters::MINE)) {
				dead = true;
				causeOfDeath = 2;
				gotoxy(pos.getX(), pos.getY());
				std::cout << toChar(Characters::SPACE);
				explode(temp.getX(), temp.getY());
				return false;
			}
			else if (c1 != toChar(Characters::WALL) && c1 != toChar(Characters::WEAK_WALL)) {
				temp.move(direction);
				if (!canonExist) { return true; }
				char c2 = board->getChar(temp.getX(), temp.getY());
				if (c2 != toChar(Characters::WALL) && c2 != toChar(Characters::WEAK_WALL)) {
					return true;
				}
			}
		}
		else {
			temp.move(direction);
			temp.move(direction);
			if (!canonExist) { 
				return true; 
			}
			char c2 = board->getChar(temp1.getX(), temp1.getY());
			if (c2 != toChar(Characters::WALL) && c2 != toChar(Characters::WEAK_WALL)) {
				return true;
			}
		}
	}
	return false;
}
// Random number
int Tank::randomDirection() {
	return toIntDir(Directions::UP) + (rand() % 8);
}


//Tank update beginning of phase
void Tank::reset() {
	direction = 0;
	addDir = 0;
	numShells = 0;
	color = Colors::WHITE;

	rightTrack = false;
	leftTrack = false;
	stayTrack = true;
	canonExist = true;
	canMove = true;
	dead = false;
	Shot = false;
	BackwardOrForward = false;

	// Resets the cannon
	//moveCanon();
	// 
    // Reset shells	
	for (int i = 0; i < 5; ++i) {
		Shells[i].reset();  
	}
}
// Resets the tank's movement and action flags at the start of a turn.
void Tank::booleanReset() {
	rightTrack = false;
	leftTrack = false;
	Movement[0] = 0;
	Movement[1] = 0;
	Shot = false;
}
//Explosion animation
void Tank::explode(int x, int y) const {

	gotoxy(x, y);
	if (!g_isSilent) {
		std::cout << toChar(Characters::TANK_SHELL);
		Beep(toInt(Variables::BEEP100), 8 * toInt(Variables::BEEP10));
		Sleep(SLEEP);

		gotoxy(x - 1, y); std::cout << toChar(Characters::TANK_SHELL);
		gotoxy(x + 1, y); std::cout << toChar(Characters::TANK_SHELL);
		gotoxy(x, y - 1); std::cout << toChar(Characters::TANK_SHELL);
		gotoxy(x, y + 1); std::cout << toChar(Characters::TANK_SHELL);
		Beep(9 * toInt(Variables::BEEP100), 8 * toInt(Variables::BEEP10));
		Sleep(SLEEP);

		gotoxy(x, y);     std::cout << toChar(Characters::SPACE);
		gotoxy(x - 1, y); std::cout << toChar(Characters::SPACE);
		gotoxy(x + 1, y); std::cout << toChar(Characters::SPACE);
		gotoxy(x, y - 1); std::cout << toChar(Characters::SPACE);
		gotoxy(x, y + 1); std::cout << toChar(Characters::SPACE);

		board->setChar(x, y, toChar(Characters::SPACE));
	}
	

}
// Handles full tank movement for the current turn.
void Tank::move()
{
	Point prev = pos;
	Point next = pos;

	if (!stayTrack) {
		if (BackwardOrForward) {
			next.move(direction);
		}
		canMove = canMoveTo();
		if (canMove) {
			pos = next;
		}
		else {
			stayTrack = true;
			BackwardOrForward = false;
		}

	}

	//char fromBoard = board->getChar(prev.getX(), prev.getY());
	if (canMove) {
		prev.draw(toChar(Characters::SPACE));
		pos.draw(toChar(Characters::TANK));
	}
	hideCursor();
	moveCanon();
	movingActiveShells();

	if (canMove && canonExist) {
		canon.draw(directionSymbols[direction][0]);
	}

}
// Iterates through all active shells and moves them forward.
void Tank::movingActiveShells() {
	for (int i = 0; i < SHELLS_NUM; ++i) {
		if (Shells[i].isActive()) {
			Point prev = Shells[i].getPos();
			Shells[i].setPrev(prev);
			char fromBoard = board->getChar(prev.getX(), prev.getY());
			char special;
			if (fromBoard == toChar(Characters::WALL)) {
				board->setChar(prev.getX(), prev.getY(), toChar(Characters::WEAK_WALL));
				special = toChar(Characters::WEAK_WALL);
				Shells[i].setActive(false);
			}
			else if (fromBoard == toChar(Characters::WEAK_WALL)) {
				board->setChar(prev.getX(), prev.getY(), toChar(Characters::SPACE));
				special = toChar(Characters::SPACE);
				Shells[i].setActive(false);
			}
			else if (fromBoard == toChar(Characters::MINE)){
				special = toChar(Characters::MINE);
			}
			else
				special = toChar(Characters::SPACE);
			if (Shells[i].isActive()) {
				Shells[i].movePos();
				setTextColor(color);
				Shells[i].getPos().draw(toChar(Characters::TANK_SHELL));
			}
			if (special == toChar(Characters::MINE))
				setTextColor(Colors::LIGHTRED);
			else
				setTextColor(Colors::WHITE);
			prev.draw(special);
			
				setTextColor(color);
		}
	}
}
// Deactivates a shell and erases its symbol from the board.
void Tank::shellExplosion(int num) {
	Point prev = Shells[num].getPos();
	Shells[num].setActive(false);
	prev.draw(toChar(Characters::SPACE));
}
// Sets the initial position of the tank and its cannon.
void Tank::startPositions(Point player, Board& b){
	setPY(player);
	Point temp;
	int Attempts = 0;
	direction = randomDirection();
	temp.move(direction);
	char c1 = b.getChar(temp.getX(), temp.getY());
	while (!c1 == toChar(Characters::SPACE)) {
		if (Attempts <= toIntDir(Directions::UL)) {
			direction = direction + 1;
			Attempts++;
			temp.move(direction);
			char c1 = b.getChar(temp.getX(), temp.getY());
		}
		else {
			c1 = toChar(Characters::SPACE);
			b.setChar(temp.getX(), temp.getY(), c1);
		}
	}
	player.move(direction);
	setPYcanon(player);
}


// Assigns the control keys for this tank 
void Tank::setArrowKeys(const char* keys)
{
	int j = 0;
	for (int i=0 ; i < TWO; ++i,j++)
		rightArrowKeys[i] = keys[j];
	for (int i=0; i < TWO; ++i, j++)
		leftArrowKeys[i] = keys[j];
	for (int i = 0; i < TWO; ++i, j++)
		stayShootArrowKeys[i] = keys[j];

}
// Sets the current direction of the tank.
void Tank::setDirection(int dir) {
		direction = dir;
		while (direction > toIntDir(Directions::UL)) {
			direction = direction - toIntDir(Directions::STAY);
		}
		while (direction < toIntDir(Directions::UP)) {
			direction = direction + toIntDir(Directions::STAY);
		}
	
}


// Checks if any active shell has hit the given position.
bool Tank::shellHitsTank(Point pos) {
	for (int i = 0; i < SHELLS_NUM; ++i) {
		if (Shells[i].isActive()) {
			if (Shells[i].getPos() == pos)
			{ 
				shellExplosion(i);
				return true;
			}	
		}
	}
	return false;
}

//Movement operations
int Tank::forward() {
	BackwardOrForward = true;
	return QE;
}
int Tank::Backward() {
	BackwardOrForward = true;

	return  AD;
}
int Tank::Right45degrees() {
	BackwardOrForward = false;
	return  Q;
}
int Tank::Left45degrees() {
	BackwardOrForward = false;
	return  E;
}
int Tank::Right90degrees() {
	BackwardOrForward = false;
	return  EA;
}
int Tank::Left90degrees() {
	BackwardOrForward = false;
	return  QD;
}
int Tank::StayTank() {
	return S;
	stayTrack = true;
}

// Determines the current direction based on key inputs.
// Returns the encoded direction constant (0-7).
int Tank::getDirection()
{
	//BackwardOrForward = false;
	if (rightTrack == true && leftTrack == true) {
		if (Movement[0] == rightArrowKeys[0])//E
			if (Movement[1] == leftArrowKeys[0]) {    //EQ
				return forward();
			}
			else { //EA
				BackwardOrForward = false;
				return  EA;
			} 
				
		else //D
			if (Movement[1] == leftArrowKeys[0]) {//DQ
				BackwardOrForward = false;
				return  QD;
			}
			else {//AD
				return Backward();
			}
				
	}
	else if(rightTrack == true){
		BackwardOrForward = false;
		if (Movement[0] == rightArrowKeys[0])//E
			return  E;
		else //D
			return  D;
	}
	else if (leftTrack == true) {
		BackwardOrForward = false;
		if(Movement[1] == leftArrowKeys[0])//Q
			return  Q;
	else //A
		return A;
	}
	else {
		if (Movement[0] == stayShootArrowKeys[0])
			return StayTank();
		else if (Movement[0] == stayShootArrowKeys[1])
		{
			
			return QE;
		}
	}
}
// Updates the tank’s movement state based on the input key
// Returns 0 if input was recognized, -1 otherwise.
int Tank::getMovement(char key) {
	if (key == stayShootArrowKeys[0]){
		stayTrack = true;
		Movement[0] = key;
		return 0;
	}
	else if (key == stayShootArrowKeys[1]) {
		if ( numShells == 0)
			Shot = true;
		Movement[0] = key;
		return 0;
	}
	else {
	for (int i = 0; i < TWO; ++i)
	{
		if (key == rightArrowKeys[i]) {
			rightTrack = true;
			stayTrack = false;
			Movement[0] = key;
			return 0;
		}
		else if (key == leftArrowKeys[i]) {
			leftTrack = true;
			stayTrack = false;
			Movement[1] = key;
			return 0;
		}
	}

}
	return -1;
}





