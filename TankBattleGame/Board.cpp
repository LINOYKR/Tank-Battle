#include "Board.h"

// Function to check if the character is valid
bool Board::isValidChar(char c) {
	return c == toChar(Characters::MINE) || c == toChar(Characters::ONE) || c == toChar(Characters::TWO) || c == toChar(Characters::LEGEND) || c == toChar(Characters::WALL) ||
		c == toChar(Characters::SPACE) || c == toChar(Characters::WEAK_WALL);
}

// Loads the board layout from a given file
void Board::load(const std::string& filename) {
	std::ifstream screen_file(filename);
	// std::cout << screen_file.is_open() << std::endl;
	// TODO: handle errors (all sort of...) - do not submit it like that :)
	
	if (!screen_file.is_open()) {
		errorMessage = "Can't open the file.";
		invalidboard = true;
		return;
	}
	int curr_row = 0;
	int curr_col = 0;
	char c;
	bool legendFound = false;
	// Read characters one by one until EOF or max rows reached
	while (!screen_file.get(c).eof() && curr_row < MAX_Y) {
		if (c == '\n') {
			if (curr_col < MAX_X) {
				// add spaces for missing cols
#pragma warning(suppress : 4996) // to allow strcpy
				strcpy(originalBoard[curr_row] + curr_col, std::string(MAX_X - curr_col - 1, ' ').c_str());
			}
			++curr_row;
			curr_col = 0;
			continue;
		}
		if (curr_col < MAX_X) {
			// handle special chars
			if (c == toChar(Characters::ONE)) {
				player1 = { curr_col, curr_row };
				player1Tanks.push_back(Point(curr_col, curr_row));

				counterPlayer1++;
				originalBoard[curr_row][curr_col++] = toChar(Characters::SPACE);
			}
			else if (c == toChar(Characters::TWO)) {
				player2 = { curr_col, curr_row };
				player2Tanks.push_back(Point(curr_col, curr_row));

				counterPlayer2++;
				originalBoard[curr_row][curr_col++] = toChar(Characters::SPACE);
			}
			else if (c == toChar(Characters::LEGEND)) {

				if (legendFound) {
					errorMessage = "Too many legend characters (L).";
					invalidboard = true;
					return;
				}
				legendPos = Point(curr_col, curr_row);

				originalBoard[curr_row][curr_col++] = toChar(Characters::SPACE);
				legendFound = true;
			}
			else {

				if (!isValidChar(c)) {
					if (curr_col < MAX_X) {
						errorMessage = "Invalid character found: " + std::string(1, c);
						invalidboard = true;
					}
					return;
				}
				originalBoard[curr_row][curr_col++] = c;
			}			


		}
	}
	if (counterPlayer1==0|| counterPlayer2==0) {
		errorMessage = "Missing players " ;
		invalidboard = true;
		return;
	}
	

	// Draw top and bottom frames and ensure each line ends properly
	int last_row = (curr_row < MAX_Y ? curr_row : MAX_Y - 1);
	// add a closing frame
	// first line
#pragma warning(suppress : 4996) // to allow strcpy
	strcpy(originalBoard[0], std::string(MAX_X, toChar(Characters::SPACE)).c_str());
	originalBoard[0][MAX_X] = '\n';
	// last line
#pragma warning(suppress : 4996) // to allow strcpy
	strcpy(originalBoard[last_row], std::string(MAX_X, toChar(Characters::SPACE)).c_str());
	originalBoard[last_row][MAX_X] = '\0';
	
	// first col + last col
	for (int row = 1; row < last_row; ++row) {
		originalBoard[row][0] = toChar(Characters::SPACE);
		originalBoard[row][MAX_X - 1] = toChar(Characters::SPACE);
		originalBoard[row][MAX_X] = '\n';
	}
	
}

// Prints the current board to the console
void Board::print() const {
	system("cls");
	const char* boardStr = currentBoard[0];
	while (*boardStr != '\0') {
		if (*boardStr == toChar(Characters::TANK)) // Hide tanks represented by 'O' on print
			std::cout << toChar(Characters::SPACE);
		else if (*boardStr == toChar(Characters::MINE)) {
			setTextColor(Colors::LIGHTRED);
			std::cout << *boardStr;
			setTextColor(Colors::WHITE);
		}
		else
			std::cout << *boardStr;
		++boardStr;
	}
}

// Resets the current board to the original layout
void Board::reset() {
	// copy the original board to the current board, as an entire 2d array
	memcpy(currentBoard, originalBoard, MAX_Y * (MAX_X + 1));
	//player1 = startPos;
	//player1.setBoard(*this);
}

// Updates a single character on the board at given x,y position
void Board::setChar(int x, int y, char ch) {
	if (x >= 0 && x < MAX_X && y >= 0 && y < MAX_Y) {
		currentBoard[y][x] = ch;
	}
}

