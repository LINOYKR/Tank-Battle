#include "Menu.h"
  

constexpr int SLEEP_DURATION = 500;

// Displaying the menu
void Menu::displayMenu() {
    system("cls"); // Clears the screen
    setTextColor(Colors::LIGHTRED);
    std::cout << "================================================================================\n";
    setTextColor(Colors::WHITE);
    std::cout << "  _____  _    _   _ _  __  ____    _  _____ _____ _     _____   \n";
    std::cout << " |_   _|/ \\  | \\ | | |/ / | __ )  / \\|_   _|_   _| |   | ____|  \n";
    std::cout << "   | | / _ \\ |  \\| | ' /  |  _ \\ / _ \\ | |   | | | |   |  _|    \n";
    std::cout << "   | |/ ___ \\| |\\  | . \\  | |_) / ___ \\| |   | | | |___| |___   \n";
    std::cout << "   |_/_/   \\_\\_| \\_|_|\\_\\ |____/_/   \\_\\_|   |_| |_____|_____|  \n";
    setTextColor(Colors::LIGHTRED);
    std::cout << "================================================================================\n";
    setTextColor(Colors::LIGHTBLUE);

    std::cout << "                (  )       \n";
    std::cout << "                ||||         \n";
    std::cout << "            [][][][][][][][]]]============@  \n";
    std::cout << "            [][][][][][][][][]              \n";
    std::cout << "          [][][][][][][][][][][][]]        \n";
    std::cout << "          [][][][][][][][][][][][]]        \n";
    std::cout << "       [][][][][][][][][][][][][][][][][][]     \n";
    std::cout << "        OXOXOXOXOXOXOXOXOXOXOXOXOXOXOXOX        \n";

    setTextColor(Colors::LIGHTRED);
    std::cout << "================================================================================\n";
    std::cout << "       ======================================\n";
    setTextColor(Colors::WHITE);
    std::cout << "                     Main Menu\n";
    setTextColor(Colors::LIGHTRED);
    std::cout << "       ======================================\n\n";
    setTextColor(Colors::WHITE);
    for (int i = 0; i < numOptions; ++i) {
        if (i == currentOption) {
            setTextColor(Colors::LIGHTCYAN); // color for the current option
            std::cout << "        > " << options[i] << "\n";
        }
        else {
            setTextColor(Colors::WHITE); // color for other options
            std::cout << "          " << options[i] << "\n";
        }
    }
    setTextColor(Colors::LIGHTRED);
    std::cout << "\n       ======================================\n";
    setTextColor(Colors::WHITE);
}

// Displaying instructions 3 Pages
void Menu::displayInstructions() {
    system("cls");
    setTextColor(Colors::LIGHTRED);
    std::cout << "================================================================================\n";
    setTextColor(Colors::WHITE);
    std::cout << "                      Tank Battle Game - Instructions\n";
    setTextColor(Colors::LIGHTRED);
    std::cout << "================================================================================\n\n";
    setTextColor(Colors::LIGHTCYAN);
    std::cout << "Welcome to Tank Battle!\n";
    setTextColor(Colors::WHITE);
    std::cout << "Two players compete in a maze using tanks that can rotate, move, and shoot.\n";
    std::cout << "Be the last tank standing!\n\n";
    
    setTextColor(Colors::LIGHTCYAN);
    std::cout << " Goal:\n";
    setTextColor(Colors::WHITE);
    std::cout << "Destroy the enemy tank using your cannon or by luring them into a mine. \n";
    std::cout << "If both tanks are destroyed in the same game cycle, it's a tie.\n\n";

    setTextColor(Colors::LIGHTCYAN);
    std::cout << "Controls:\n";
    setTextColor(Colors::WHITE);
    std::cout << "Each player controls their tank using separate keys.\n";
    std::cout << "Case-insensitive: both lowercase and uppercase work.\n\n";
    
    setTextColor(Colors::LIGHTCYAN);
    std::cout << "Game Elements:\n";
    setTextColor(Colors::WHITE);
    std::cout << " - 'O': Tank\n";
    std::cout << " - '|', '/', '\\', '-': Cannon directions\n";
    std::cout << " - '@': Mine\n";
    std::cout << " - '#': Wall\n";
    std::cout << " - '*': Shell (bullet)\n";

    waitForContinue();
    setTextColor(Colors::LIGHTRED);
    std::cout << "================================================================================\n";
    setTextColor(Colors::WHITE);
    std::cout << "                      Tank Battle Game - Instructions\n";
    setTextColor(Colors::LIGHTRED);
    std::cout << "================================================================================\n\n";
    setTextColor(Colors::LIGHTCYAN);
    std::cout << " Keys:\n\n";
    setTextColor(Colors::WHITE);
    std::cout << "Player 1:\n";
    std::cout << " - Left track forward:    Q\n";
    std::cout << " - Left track backward:   A\n";
    std::cout << " - Right track forward:   E\n";
    std::cout << " - Right track backward:  D\n";
    std::cout << " - Stay:                  S\n";
    std::cout << " - Shoot:                 W\n\n";

    std::cout << "Player 2:\n";
    std::cout << " - Left track forward:    U\n";
    std::cout << " - Left track backward:   J\n";
    std::cout << " - Right track forward:   O\n";
    std::cout << " - Right track backward:  L\n";
    std::cout << " - Stay:                  K\n";
    std::cout << " - Shoot:                 I\n\n";
   
    waitForContinue();
    setTextColor(Colors::LIGHTRED);
    std::cout << "================================================================================\n";
    setTextColor(Colors::WHITE);
    std::cout << "                      Tank Battle Game - Instructions\n";
    setTextColor(Colors::LIGHTRED);
    std::cout << "================================================================================\n\n";

    setTextColor(Colors::LIGHTCYAN);
    std::cout << "Game Rules:\n";
    setTextColor(Colors::WHITE);
    std::cout << "1. Each tank can rotate or move based on its track control.\n";
    std::cout << "2. Tanks cannot rotate into walls.\n";
    std::cout << "3. Shells destroy tanks or cannons on impact.\n";
    std::cout << "4. Walls take two hits to break.\n";
    std::cout << "5. Stepping on a mine destroys a tank.\n";
    std::cout << "6. Shells destroy each other if they meet.\n";
    std::cout << "7. Objects that leave the screen edges appear on the opposite\n";
    std::cout << "side (tunnel effect).\n\n";
    std::cout << "Pause the game with ESC. Press again to resume or X to exit to menu.\n";

;
setTextColor(Colors::LIGHTRED);
std::cout << "================================================================================\n";
    setTextColor(Colors::WHITE);
    std::cout << "Press any key to return to the main menu.";

    (void)_getch(); // Waits for press and skips the return value
}

//Waiting for the next screen
void Menu::waitForContinue() {
    std::cout << "\nPress any key to continue...\n";
    _getch(); 
    system("cls"); 
}


// Constructor
Menu::Menu(std::string optionsArray[], int size) {
    numOptions = size;
    options = new std::string[size]; // Allocate memory to an array
    for (int i = 0; i < size; ++i) {
        options[i] = optionsArray[i]; // Copy the values
    }
    currentOption = 0; // Starting from the first option
}

// Destructor
Menu::~Menu() {
    delete[] options; // Release the allocated memory
}

//Copy Constructor
Menu::Menu(const Menu& other) {
    numOptions = other.numOptions;
    options = new std::string[numOptions];
    for (int i = 0; i < numOptions; ++i) {
        options[i] = other.options[i];
    }
    currentOption = other.currentOption;
    //useColors = other.useColors;
    //useSound = other.useSound;
}

// Assignment operator
Menu& Menu::operator=(const Menu& other) {
    if (this != &other) {
        delete[] options;
        numOptions = other.numOptions;
        options = new std::string[numOptions];
        for (int i = 0; i < numOptions; ++i) {
            options[i] = other.options[i];
        }
        currentOption = other.currentOption;
        //useColors = other.useColors;
        //useSound = other.useSound;
    }
    return *this;
}

// Activating the menu
void Menu::run(int argc, char** argv) {
    Sleep(SLEEP_DURATION);
    char input;
    bool running = true;
    bool isSave = argc > 1 && std::string(argv[1]) == "-save";
    bool isLoad = argc > 1 && std::string(argv[1]) == "-load";
    bool isSilent = isLoad && argc > 2 && std::string(argv[2]) == "-silent";
    if (isLoad) {
        LoadGame loadGame;
        loadGame.setloadGame();
        if (isSilent) {
            loadGame.setSilentMode();
            g_isSilent = true;
        }
        loadGame.run();
    }
    else {

        do {
            displayMenu();

            input = _getch(); // Read a character without having to press Enter
            Game game;
            SaveGame saveGame;
            // Handling user input
            switch (input) {
            case '1': // Start game
                clearScreen();
                if (isSave) {
                    saveGame.run();
                }
                else {
                    game.run();
                }
                break;
            case '8': // Show instructions
                displayInstructions();
                break;
            case '9': // Exit
                std::cout << "Goodbye!\n";
                Sleep(1000);
                running = false;
                break;
            case '2': // Without or with color
                g_isColorOn = !g_isColorOn;
                break;
            case 72: // Up 
                currentOption = (currentOption - 1 + numOptions) % numOptions;
                break;
            case 80: // Down 
                currentOption = (currentOption + 1) % numOptions;
                break;
            case 13: // Enter
                if (currentOption == 0) {
                    clearScreen();
                    if (isSave) {
                        saveGame.run();
                    }
                    else {
                        game.run();
                    }
                    break;
                }
                else if (currentOption == 1) {
                    displayInstructions();
                    break;
                }
                else if (currentOption == 2) {
                    std::cout << "Goodbye!\n";
                    Sleep(1000);
                    running = false;
                    break;
                }
                else if (currentOption == 3) {
                    g_isColorOn = !g_isColorOn;
                    break;
                }
                break;
            default:
                break;
            }

        } while (running); // Always ongoing until one returns

    }


}

