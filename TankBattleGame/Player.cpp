#include "Player.h"



// Function that initializes the tanks by locations
void Player::initTanksFromPositions(const std::vector<Point>& positions, const char* keys, Colors color, Board& b) {
	lost = false;
	numTanks = positions.size();
	for (int i = 0; i < numTanks; ++i) {
		s[i].reset();
		s[i].startPositions(positions[i],b);
		s[i].setColor(color);
		s[i].setArrowKeys(keys);
	}
}
//Reset all tank variables
void Player::tankBooleanReset() {
	for (int i = 0; i < numTanks; i++) {
		s[i].booleanReset();
	}
}
//Setting direction for all tanks
void Player::setAllTank() {
	for (int i = 0; i < numTanks; i++) {
		if (!s[i].getStay()) {
			s[i].setDirection(s[i].getAddDir() + s[i].getDir());
			if (s[i].getAddDir() == toIntDir(Directions::DOWN))
				s[i].setAddDir(toIntDir(Directions::UP));
		}
	}
}

//Movement of all tanks
void Player::moveAllTank(Player& name) {
	int point = 0;
	for (int i = 0; i < numTanks; i++) {
		if (!s[i].getLostLife()) {
			if (!tankClash(name, i)) {
				setTextColor(s[i].getColor());
				s[i].move();
				setTextColor(Colors::WHITE);
				if (s[i].getLostLife()) {
					name.addPoints(toInt(Variables::HIT_POINT));
				}
			}
		}
		else {
			s[i].movingActiveShells();
		}
	}

}
//Tank collision
bool Player::tankClash(Player& name,int tank) {
	Point temp = s[tank].getPos();
	temp.move(s[tank].getDir());
	Point tempCannon = temp;
	tempCannon.move(s[tank].getDir());
	//Tanks from the same player
	for (int i = 0; i < numTanks; i++) {
		if (i != tank && !s[i].getLostLife()) {
			if (temp == s[i].getPos())
				return true;
			else if (temp == s[i].getCanon() && s[i].getCanonExist())
				return true;
			else if (s[tank].getCanonExist()) {
				if (tempCannon == s[i].getPos())
					return true;
				else if (s[i].getCanonExist() && tempCannon == s[i].getCanon())
					return true;
			}
		}
	}
	//tanks player opposite
	for (int i = 0; i < name.getNumTank(); i++) {
		if ( !name.getTank(i).getLostLife()) {
			if (temp == name.getTank (i).getPos())
				return true;
			else if (temp == name.getTank(i).getCanon() && name.getTank(i).getCanonExist())
				return true;
			else if (s[tank].getCanonExist()) {
				if (tempCannon == name.getTank(i).getPos())
					return true;
				else if (name.getTank(i).getCanonExist() && tempCannon == name.getTank(i).getCanon())
					return true;
			}
		}
	}
	return false;
}
//Checking if all tanks are dead
bool Player::allTanksDead() {
	for (int i = 0; i < numTanks; ++i) {
		if(!s[i].getLostLife()){
			return false;
		}
	}
	lost = true;
	return true;
}
//Checking if a specific tank is dead
bool Player::thisTankDead(int num) {
	if (s[num].getLostLife()) {
		return true;
	}
	return false;
}

//Placing a board for the tank
void Player::setTankBoard(Board& b) {
	for (int i = 0; i < numTanks; ++i) {
		s[i].setBoard(b);
	}
}
//Adding points to a player
void Player::addPoints(int add){
	Points = Points + add;
}