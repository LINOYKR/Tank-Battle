#include "LoadGame.h"


constexpr int ZERO = 0;
constexpr int ONE = 1;
constexpr int END = 3;
constexpr int BACK = 4;

// Display result mismatch error and wait for user input
void reportResultError(const std::string& message, size_t iteration) {
	system("cls");
	std::cout << "Screen " << message << '\n';
	std::cout << "Iteration: " << iteration << '\n';
	std::cout << "Press any key to continue to next screens (if any)" << std::endl;
	_getch();
	system("cls");
}
// Constructor - initialize base class and members
LoadGame::LoadGame()
    : Game(), steps(), results(), random_seed(ZERO) {}
// Load step and result files, set random seed
void LoadGame::initializeGame(const std::string& filename) {
	filename_prefix = filename.substr(ZERO, filename.find_last_of('.'));
	stepsFilename = filename_prefix + ".steps";
	resultsFilename = filename_prefix + ".result";
	steps = Steps::loadSteps(stepsFilename);
	random_seed = steps.getRandomSeed();
	results = Results::loadResults(resultsFilename);
	srand(random_seed);
}
// Create player
void LoadGame::createPlayers() {
	player1 = new Player();    
	player2 = new  ComputerPlayer();
}
// Always return first board (no input)
size_t LoadGame::chooseStartingLevel(const std::vector<std::string>& fileNames) {
	system("cls");
	size_t choice = ZERO;
	return choice;
}
// Load steps for current iteration from file and apply them to each player
void LoadGame::loadingDirectionFromFile() {
	while (steps.isNextStepOnIteration(iteration)) {
		auto [iter, action, player, stepVal] = steps.popStep();

		if (player == 1) {
			loadingPlayer(*player1, action, stepVal);
		}
		else {
			loadingPlayer(*player2, action, stepVal);
		}
	}
}
// Apply action from file to a specific player
void LoadGame::loadingPlayer(Player& play, ActionType action, int step) {
	switch (action) {
	case ActionType::SHOOT:
		play.getTank(play.getTankP()).setShot(true);
		
		if(!play.getTank(play.getTankP()).getBackwardOrForward())
			play.getTank(play.getTankP()).setStayTrack(true);
			
		break;

	case ActionType::STAY:
		play.getTank(play.getTankP()).setAddDir(step);
		play.getTank(play.getTankP()).setStayTrack(true);
		break;

	case ActionType::MOVE:
		play.getTank(play.getTankP()).setAddDir(step);
		if (step == ZERO || step == BACK) {
			play.getTank(play.getTankP()).setBackwardOrForward(true);
			play.getTank(play.getTankP()).setStayTrack(false);
		}
		else {
			play.getTank(play.getTankP()).setBackwardOrForward(false);
			play.getTank(play.getTankP()).setStayTrack(false);
		}
		break;

	case ActionType::SWITCH: {
		int attempts = ZERO;
		do {
			int num = (play.getTankP() + ONE) % play.getNumTank();
			play.setTankP(num);
			attempts++;
		} while (play.thisTankDead(play.getTankP()) && attempts < play.getNumTank());

		break;

	}
	}
}
// Check if tanks died as expected in result file
void LoadGame::allTanksDead() {
	while (results.isNextStepOnIteration(iteration)) {
		auto [iter, type, player, tank, x, y, scorePL1, scorePL2] = results.popResult();

		if (player == ONE) {
			rowIntegrityCheck(*player1, type, tank, x, y, scorePL1, scorePL2);
		}
		else {
			rowIntegrityCheck(*player2, type, tank, x, y, scorePL1, scorePL2);
		}
	}
	Game::allTanksDead();
}
// Validate death event of a tank in the results file
void LoadGame::rowIntegrityCheck(Player& play, EventType type, int tank, int x, int y, int scorePL1, int scorePL2) {
	if (!play.getTank(tank).getLostLife()) {
		reportResultError("Results file says the tank is dead, but it's alive", iteration);
		unmatching_result_found = true;
		return;
	}
	if (play.getTank(tank).getPos().getX() != x || play.getTank(tank).getPos().getY() != y) {
		reportResultError("Results file doesn't match lost life event!-Location", iteration);
		unmatching_result_found = true;
	}
	if (play.getTank(tank).getCauseOfDeath() != static_cast<int>(type)) {
		reportResultError("Results file doesn't match lost life event!-type", iteration);
		unmatching_result_found = true;
	}
	if (player1->getPoints() != scorePL1 || player2->getPoints() != scorePL2) {
		reportResultError("Results file doesn't match lost life event!-Points", iteration);
		unmatching_result_found = true;
	}
}
// Validate final END line at the end of results file
void LoadGame::endLevel() {
	if (!unmatching_result_found) {
		auto [iter, type, player, tank, x, y, scorePL1, scorePL2] = results.popResult();
		//rowIntegrityCheck(*player2, type, tank, x, y, scorePL1, scorePL2);
		if (END != static_cast<int>(type)) {
			reportResultError("Results file doesn't match lost life event!-type", iteration);
			unmatching_result_found = true;
		}
	}
}
