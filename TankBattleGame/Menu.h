#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <windows.h>

#include "SaveGame.h"
#include "LoadGame.h"
#include "Game.h"
#include "Utils.h"


class Menu
{
private:
    std::string* options;   // The options array
    int numOptions;    //number of options in the menu
    int currentOption; //current option selected


    void displayMenu();                       //displays the menu
    void displayInstructions();               //displays game instructions
    void waitForContinue();                   //Waiting for the next screen


public:
    Menu(std::string optionsArray[], int size);  //constructor
    ~Menu();                                //destructor
    Menu(const Menu& other);                // Copy constructor
    Menu& operator=(const Menu& other);     // Assignment operator
    void run(int argc, char** argv);        //Running a game menu

};

