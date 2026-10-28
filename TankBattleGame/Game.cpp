#include "Game.h"
#include "SaveGame.h"
#include "LoadGame.h"

constexpr int SLEEP = 100;
constexpr int ESC = 27;
constexpr int BOARD_NUM = 11;
constexpr int SHELLS_TANK = 5;
constexpr int ERRORS = -1;


Game::~Game() {
	delete player1;
	delete player2;
}

//displays Error Message
void Game::displayErrorMessage(const std::string& errorDetails) {
	system("cls"); //clear the console

	std::cout << "====================================================\n";
	std::cout << "              Error: The board file             \n";
	std::cout << "====================================================\n";
	std::cout << "====================================================\n";

	std::cout << "Details: " << errorDetails << "\n"; // Add the specific error

	std::cout << "====================================================\n";

	std::cout << "Press any key to return to the menu..." << std::endl;

	char input = _getch(); //wait for user input
	return;
}

// Displays victory message when game ends
void Game::displayVictoryMessage(const std::string& errorDetails) {
	system("cls"); //clear the console
	setTextColor(Colors::LIGHTRED);
	std::cout << "================================================================================\n";
	setTextColor(Colors::WHITE);
	std::cout << " _    _               _   _     _           _                   \n";
	std::cout << "| |  | |             | | | |   (_)         | |                  \n";
	std::cout << "| |  | | ___  _ __   | |_| |__  _ ___   ___| |_ __ _  __ _  ___ \n";
	std::cout << "| |/\\| |/ _ \\| '_ \\  | __| '_ \\| / __| / __| __/ _` |/ _` |/ _ \\\n";
	std::cout << "\\  /\\  / (_) | | | | | |_| | | | \\__ \\ \\__ \\ || (_| | (_| |  __/\n";
	std::cout << " \\/  \\/ \\___/|_| |_|  \\__|_| |_|_|___/ |___/\\__\\__,_|\\__, |\\___|\n";
	std::cout << "                                                      __/ |     \n";
	std::cout << "                                                     |___/      \n";
	setTextColor(Colors::LIGHTCYAN);
	std::cout << "Details: " << errorDetails << "\n"; // Add the specific error
	std::cout << "Summary of points up to this point" <<  "\n";
	std::cout << "  Player1: " << player1->getPoints()  << "\n";
	std::cout << "  Player2: " << player2->getPoints() << "\n";

	setTextColor(Colors::LIGHTRED);
	std::cout << "================================================================================\n";
	setTextColor(Colors::WHITE);
	std::cout << "Congratulations!" << std::endl;
	if (waitForInput) {
		std::cout << "Press any key to return to the menu..." << std::endl;
		_getch();
	}
	else {
		Sleep(SLEEP);
	}
	return;
}

//displays end all game and win
void Game::displayEndAllGameWin() {
	system("cls"); //clear the console
	setTextColor(Colors::LIGHTRED);
	std::cout << "================================================================================\n";
	setTextColor(Colors::WHITE);
	std::cout << "__        ___         _   _                                       \n";
	std::cout << "\\ \\      / (_)_ __   | |_| |__   ___    __ _  __ _ _ __ ___   ___ \n";
	std::cout << " \\ \\ /\\ / /| | '_ \\  | __| '_ \\ / _ \\  / _` |/ _` | '_ ` _ \\ / _ \\\n";
	std::cout << "  \\ V  V / | | | | | | |_| | | |  __/ | (_| | (_| | | | | | |  __/\n";
	std::cout << "   \\_/\\_/  |_|_| |_|  \\__|_| |_|\\___|  \\__, |\\__,_|_| |_| |_|\\___|\n";
	std::cout << "                                        |___/                      \n";
	
	if(player1->getPoints()>player2->getPoints())
		std::cout << "Player 1 won the entire game " << "\n\n";
	else if (player1->getPoints() < player2->getPoints())
		std::cout << "Player 2 won the entire game " << "\n\n";
	else
		std::cout << "A tie you both win " << "\n\n";
    setTextColor(Colors::LIGHTCYAN);
	std::cout << "Summary of points up to this point" << "\n";
	std::cout << "  Player1: " << player1->getPoints() << "\n";
	std::cout << "  Player2: " << player2->getPoints() << "\n";

	setTextColor(Colors::LIGHTRED);
	std::cout << "================================================================================\n";
	setTextColor(Colors::WHITE);
	std::cout << "Congratulations!" << std::endl;
	if (waitForInput) {
		std::cout << "Press any key to return to the menu..." << std::endl;
		_getch();
		return;
	}
}


// Finds all .screen files starting with "board" in current directory
void Game::getAllBoardFileNames (std::vector<std::string>& vec_to_fill) {
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator(fs::current_path())) {
		auto filename = entry.path().filename();
		auto filenameStr = filename.string();
		if (filenameStr.substr(0, BOARD_NUM) == "tanks-game_" && filename.extension() == ".screen") {
			//std::cout << " ^ added!!\n";
			vec_to_fill.push_back(filenameStr);
		}
	}
}

// Checks if any tank or cannon was hit by a shell
void Game::entityMeeting(Player& play1, Player& play2) {
	for (int i = 0; i < play1.getNumTank(); i++) {
		if (!play1.getTank(i).getLostLife()) {
			Point temp = play1.getTank(i).getPos();
			//A tank hit the shell of my tank.
			for (int j = 0; j < play1.getNumTank(); j++) {
				if (play1.getTank(j).shellHitsTank(temp)) {
					play1.getTank(i).setLostLife(true);
					play1.getTank(i).setCauseOfDeath(0);
					play2.addPoints(toInt(Variables::HIT_POINT));
					play1.getTank(i).getCanon().draw(toChar(Characters::SPACE));
				}
				if (play1.getTank(i).getCanonExist()) {
					Point canonCk = play1.getTank(i).getCanon();
					if (play1.getTank(j).shellHitsTank(canonCk)) {
						play1.getTank(i).setCanonExist(false);
						play1.getTank(i).setCauseOfDeath(1);
					}
						

				}
			}
			//A tank hit the shell of the other player's tank.
			for (int k = 0; k < play2.getNumTank(); k++) {
				if (play2.getTank(k).shellHitsTank(temp)) {
					play1.getTank(i).setLostLife(true);
					play1.getTank(i).setCauseOfDeath(0);
					play2.addPoints(toInt(Variables::HIT_POINT));
					play1.getTank(i).getCanon().draw(toChar(Characters::SPACE));
				}

				if (play1.getTank(i).getCanonExist()) {
					Point canonCk = play1.getTank(i).getCanon();
					if (play2.getTank(k).shellHitsTank(canonCk)) {
						play1.getTank(i).setCanonExist(false);
						play1.getTank(i).setCauseOfDeath(1);
					}

				}
			}
		}	
	}
}

// Handles collisions between shells
void Game::shellsMeeting(Player& play1, Player& play2) {
	
	for (int i = 0; i < play1.getNumTank(); i++) {
		for (int j = 0; j < SHELLS_TANK; j++) {
			if (play1.getTank(i).getShell(j).isActive() )
			{
				Point pos1 = (play1.getTank(i).getShell(j).getPos());
				// Check for shell collision between players
				for (int k = 0; k < play2.getNumTank(); k++) {
					for (int s = 0; s < SHELLS_TANK; s++) {
							if (play2.getTank(k).getShell(s).isActive()) {
								Point pos2 = (play2.getTank(k).getShell(s).getPos());
								if (pos1 == pos2) {
									play1.getTank(i).shellExplosion(j);
									play2.getTank(k).shellExplosion(s);
								}
								else if (pos1 == play2.getTank(k).getShell(s).getPrev()) {
									if (pos2 == play1.getTank(i).getShell(j).getPrev()) {
										play1.getTank(i).shellExplosion(j);
										play2.getTank(k).shellExplosion(s);
									}
								}
							}
					}

				}
				// Check for shell collision within the same tank
				int loop = j + 1;
				for (int k = i; k < play1.getNumTank(); k++) {
					for ( loop; loop < SHELLS_TANK; loop++) {
						if (play1.getTank(k).getShell(loop).isActive()) {
							Point pos2 = (play1.getTank(k).getShell(loop).getPos());
							if (pos1 == pos2) {
								play1.getTank(i).shellExplosion(j);
								play1.getTank(k).shellExplosion(loop);
							}
							else if (pos1 == play1.getTank(k).getShell(loop).getPrev()) {
								if (pos2 == play1.getTank(i).getShell(j).getPrev()) {
									play1.getTank(i).shellExplosion(j);
									play1.getTank(k).shellExplosion(loop);
								}
							}
						}

					}
					loop = 0;
				}
			}
		}
	}
}

// Manages the pause menu when ESC is pressed
bool Game::managePause(bool& isPaused, char& key) {
	
		if (key == ESC) { // ESC
			isPaused = !isPaused;

			if (isPaused) {
				system("cls");
				std::cout << "Game paused, press ESC again to continue or X to go back to the main menu";

				while (true) {
					if (_kbhit()) {
						key = tolower(_getch());
						if (key == ESC) { 
							isPaused = false;
							system("cls");
							return false;
						}
						else if (key == toChar(Characters::SMALL_EXIT) || key == toChar(Characters::BIG_EXIT)) {
							return true;
						}
					}
					Sleep(SLEEP);	
				}
			}
		}
}

// Displays a menu for the player to choose the starting level and returns the chosen level's index.
size_t Game::chooseStartingLevel(const std::vector<std::string>& fileNames) {
	system("cls");
	std::cout << "Select the starting level:\n";
	for (size_t i = 0; i < fileNames.size(); ++i) {
		std::cout << i + 1 << ". " << fileNames[i] << "\n";
	}

	size_t choice = 0;
	while (true) {
		std::cout << "Enter a number (1-" << fileNames.size() << "): ";
		std::cin >> choice;
		if (choice >= 1 && choice <= fileNames.size()) {
			system("cls");
			break;
		}
		std::cout << "Invalid choice. Please try again.\n";
	}
	return choice - 1;
}


// Runs the main game loop
void Game::run()
{
	createPlayers();
	hideCursor();
	std::vector<std::string> fileNames;
	getAllBoardFileNames(fileNames);
	if (fileNames.empty()) {
		std::string errorMessage = "Error: No level files found.";
		displayErrorMessage(errorMessage);
		return;
	}
	size_t startLevel = chooseStartingLevel(fileNames);
	bool isPaused = false;
	char key = 0;
	int dir1 = 0, dir2 = 0;

	//Switching between boards
	for (size_t i = startLevel; i < fileNames.size(); ++i) {
		Board board;
		board.load(fileNames[i]);
		if (board.getInvalidbord()) {
			displayErrorMessage(board.getErrorMessage());
			return;
		}
		board.reset();
		if (!g_isSilent) {
			board.print();
		}
		initializeGame(fileNames[i]);
		// Set start positions
		std::vector<Point> play1Positions = board.getPY10();
		int numTanks1 = play1Positions.size();
		player1->initTanksFromPositions(play1Positions, "edqasw", Colors::LIGHTCYAN, board);
		player1->setNumTank(numTanks1);
		std::vector<Point> play2Positions = board.getPY20();
		int numTanks2 = play1Positions.size();
		player2->initTanksFromPositions(play2Positions, "olujki", Colors::LIGHTMAGENTA, board);
		player2->setNumTank(numTanks2);
		player1->setTankBoard(board);
		player2->setTankBoard(board);

		bool round = 0;
		int tankP1 = 0, tankP2 = 0;
		iteration = 0;


		//Game loop
		while (!player1->getLost() && !player2->getLost()) {


			if (loadGame)
				loadingDirectionFromFile();
			else
			{
				player1->setTankP(tankP1);
				player2->setTankP(tankP2);
				bool p1 = false, p2 = false;
				bool p1Move = false, p2Move = false;
				//----------------------------------------------------
				while (_kbhit()) {

					key = tolower(_getch());
					if (key == ESC) {
						if (managePause(isPaused, key)) {
							return; // Go back to menu
						}
						//isPaused = !isPaused;
						managePause(isPaused, key);
						board.print();  // Reprint board after pause
					}
					if ((key == 'z' || key == 'Z' || player1->thisTankDead(tankP1)) && (modeGame == 0 || modeGame == 1)) {
						int attempts = 0;
						do {
							tankP1 = (tankP1 + 1) % numTanks1; // Moving to the next tank
							attempts++;
						} while (player1->thisTankDead(tankP1) && attempts < numTanks1);
						p1 = true;

					}
					else if ((key == 'm' || key == 'M' || player2->thisTankDead(tankP2)) && (modeGame == 0)) {
						int attempts = 0;
						do {
							tankP2 = (tankP2 + 1) % numTanks2;
							attempts++;
						} while (player2->thisTankDead(tankP2) && attempts < numTanks2);
						p2 = true;
						tankCrossing(2);
					}
					// Update direction for tank 1 
					else if ((player1->getTank(tankP1).getMovement(key) != ERRORS) && (modeGame == 0 || modeGame == 1)) {
						dir1 = player1->getTank(tankP1).getDirection();
						player1->getTank(tankP1).setAddDir(dir1);
						p1Move = true;
					}
					// Update direction for tank 2
					else if ((player2->getTank(tankP2).getMovement(key) != ERRORS) && (modeGame == 0)) {
						dir2 = player2->getTank(tankP2).getDirection();
						player2->getTank(tankP2).setAddDir(dir2);
						p2Move = true;

					}
				}
				if (modeGame == 0) {
					if (p1) {
						tankCrossing(1);
					}
					else if (p1Move) {
						moveOrShoot(*player1, 1);
					}
					if (p2) {
						tankCrossing(2);
					}
					else if (p2Move) {
						moveOrShoot(*player2, 2);
					}
				}
				else if (modeGame == 1) {
					if (p1) {
						tankCrossing(1);
					}
					else if (p1Move) {
						moveOrShoot(*player1, 1);
					}
					if (player2->autoGenerateDirection(player1))
						tankCrossing(2);
					else
						moveOrShoot(*player2, 2);

				}
				else if (modeGame == 2) {
					if (player1->autoGenerateDirection(player2))
						tankCrossing(1);
					else
						moveOrShoot(*player1, 1);

					if (player2->autoGenerateDirection(player1))
						tankCrossing(2);
					else
						moveOrShoot(*player2, 2);

				}
				//----------------------------------------------------------

			}
			// Move tank 1 if allowed
			player1->setAllTank();
			player1->moveAllTank(*player2);
			if (!g_isSilent) {
				Sleep(SLEEP * 2);
			}

			// Move tank 2 if allowed
			player2->setAllTank();
			player2->moveAllTank(*player1);
			if (!g_isSilent) {
				Sleep(SLEEP * 2);
			}
			

			// Reset temporary flags
			player1->tankBooleanReset();
			player2->tankBooleanReset();

			// Handle collisions
			entityMeeting(*player1, *player2);
			entityMeeting(*player2, *player1);
			shellsMeeting(*player1, *player2);
			shellsMeeting(*player2, *player1);

			//Player points
			allTanksDead();
			iteration++;
			if (!g_isSilent){
			setTextColor(Colors::LIGHTCYAN);
			gotoxy(board.getLegendPos().getX(), board.getLegendPos().getY());
			std::cout << " Player1: " << player1->getPoints() << "  Player2: " << player2->getPoints() << std::flush;
			setTextColor(Colors::WHITE);
			}
		}
		endLevel();
		
		// Determine game result
		std::string errorMessage;
		if (player1->allTanksDead() && player2->allTanksDead()) {
			player1->addPoints(toInt(Variables::VICTORY_POINT));
			player2->addPoints(toInt(Variables::VICTORY_POINT));
			errorMessage = "You both win this stage";

		}
		else if (player1->allTanksDead()) {
			player2->addPoints(toInt(Variables::VICTORY_POINT));
			errorMessage = "Player number 2 won this stage";
		}
		else {
			player1->addPoints(toInt(Variables::VICTORY_POINT));
			errorMessage = "Player number 1 won this stage";
		}
		if (!g_isSilent){
		displayVictoryMessage(errorMessage);
		}

	}
	if (!g_isSilent) {
		displayEndAllGameWin();
	}

	system("cls");

}

//Creating an Players
void Game::createPlayers() {
	system("cls");
	int mode;
	std::cout << "Choose mode:\n1. Human vs Human\n2. Human vs Computer\n3. Computer vs Computer\n";
		std::cin >> mode;
		if (mode > 0 && mode < 4) {
			switch (mode) {
			case 1:
				player1 = new Player(); // Human
				player2 = new Player(); // Human
				break;
			case 2:
				player1 = new Player();            // Human
				player2 = new ComputerPlayer();    //computer
				modeGame = 1;
				break;
			case 3:
				player1 = new ComputerPlayer();    // computer
				player2 = new ComputerPlayer();    //computer
				modeGame = 2;
				break;
			default:
				std::cout << "Invalid choice, defaulting to Human vs Human\n";
				player1 = new Player();
				player2 = new Player();
				break;
			}
		}
}
//Define game by mode
void Game::initializeGame(const std::string& filename) {

}
//Swapping tanks by mod
void Game::tankCrossing(int player) {}
//Move and shoot according to mode
void Game::moveOrShoot(Player& play, int num){}
//Dead tank inspection and treatment according to mod
void Game::allTanksDead(){
	player1->allTanksDead();
	player2->allTanksDead();
}
//End stage by mode
void Game::endLevel() {}
//Load command from file
void Game::loadingDirectionFromFile(){}