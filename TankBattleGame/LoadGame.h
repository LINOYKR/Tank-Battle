#include "Game.h"
#include "Results.h"
#include "Steps.h"

#include <iostream>


class LoadGame : public Game
{
private:

    Steps steps;          // Stores the actions taken by the players
    Results results;      // Stores game events 
    long random_seed;     //Ensures deterministic behavior during saving and allows identical replay during loading.
    bool unmatching_result_found = false;

    std::string filename_prefix;
    std::string stepsFilename;
    std::string resultsFilename;
protected:

    void initializeGame(const std::string& filename);
    void createPlayers();
    size_t chooseStartingLevel(const std::vector<std::string>& fileNames);  //Selecting a starting board
    void loadingDirectionFromFile();
    //void loadingPlayer(Player& play, Step& step);
    void allTanksDead();
    void rowIntegrityCheck(Player& play, EventType type, int tank, int x, int y, int scorePL1, int scorePL2);
    //void rowIntegrityCheck(Player& play, ResultEvent& resu);
    void endLevel();
    void loadingPlayer(Player& play, ActionType action, int step);

public:
    LoadGame();

};

