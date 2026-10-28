#include "SaveGame.h"

constexpr int ZERO = 0;


// Initializes file names, random seed, and sets the starting state of the game.
void SaveGame::initializeGame(const std::string& filename) {
	filename_prefix = filename.substr(ZERO, filename.find_last_of('.'));
	stepsFilename = filename_prefix + ".steps";
	resultsFilename = filename_prefix + ".result";
	iteration = ZERO;
	random_seed = static_cast<long>(std::chrono::system_clock::now().time_since_epoch().count());
	steps.setRandomSeed(random_seed);
	srand(random_seed);

}
//Saves a "SWITCH TANK" action to the .steps file
void SaveGame::tankCrossing(int num) {
	steps.addStep(iteration, ActionType::SWITCH, num, ZERO);
}
//Logs the action (MOVE, STAY, or SHOOT) of a player's tank
void SaveGame::moveOrShoot(Player& play, int num) {
	ActionType action;

	if (play.getTank(play.getTankP()).getShot()) {
		action = ActionType::SHOOT;
	}
	else if (play.getTank(play.getTankP()).getStay() || play.getTank(play.getTankP()).getAddDir() == 8) {
		action = ActionType::STAY;
	}
	else {
		action = ActionType::MOVE;
	}

	int stepVal = play.getTank(play.getTankP()).getAddDir();
	steps.addStep(iteration, action, num, stepVal);
}
//Logs dead tanks as events in the .result file
void SaveGame::allTanksDead() {
	Game::allTanksDead();

	for (int i = 0; i < player1->getNumTank(); ++i) {
		if (player1->getTank(i).getLostLife() && !player1->getTank(i).getTestResults()) {
			EventType type;
			switch (player1->getTank(i).getCauseOfDeath()) {
			case 0: type = EventType::HIT_TANK; break;
			case 1: type = EventType::HIT_CANNON; break;
			default: type = EventType::MINE;
			}
			results.addResult(iteration, type, 1, i,
				player1->getTank(i).getPos().getX(),
				player1->getTank(i).getPos().getY(),
				player1->getPoints(),
				player2->getPoints());

			player1->getTank(i).setTestResults();
		}
	}

	for (int i = 0; i < player2->getNumTank(); ++i) {
		if (player2->getTank(i).getLostLife() && !player2->getTank(i).getTestResults()) {
			EventType type;
			switch (player2->getTank(i).getCauseOfDeath()) {
			case 0: type = EventType::HIT_TANK; break;
			case 1: type = EventType::HIT_CANNON; break;
			default: type = EventType::MINE;
			}
			results.addResult(iteration, type, 2, i,
				player2->getTank(i).getPos().getX(),
				player2->getTank(i).getPos().getY(),
				player1->getPoints(),
				player2->getPoints());

			player2->getTank(i).setTestResults();
		}
	}
}
// Marks the end of the level in the .result file
void SaveGame::endLevel() {
	results.addResult(iteration, EventType::END_LEVEL, 2, ZERO, ZERO, ZERO,player1->getPoints(), player2->getPoints());

	steps.saveSteps(stepsFilename);
	results.saveResults(resultsFilename);
	steps.clear();
	results.clear();
}


SaveGame::SaveGame()
	: Game(), steps(), results() {
}

