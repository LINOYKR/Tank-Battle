#include "Game.h"
#include "Steps.h"
#include "Results.h"
class SaveGame : public Game
{
private:
    Steps steps;        // Stores the actions taken by the players
    Results results;    // Stores game events 
    long random_seed;   // Ensures deterministic behavior during saving and allows identical replay during loading.

    std::string filename_prefix;
    std::string stepsFilename;
    std::string resultsFilename;
   

protected:
    
    void initializeGame(const std::string& filename); // Extracts filenames, sets up random seed, and prepares to record data.
    void tankCrossing(int player);                    // Logs a tank switch (ActionType::SWITCH) to the .steps file
    void moveOrShoot(Player& play, int num);          // Logs a player’s action (MOVE, STAY, SHOOT) to .steps
    void allTanksDead();                              // Records dead tanks (with cause and position) to .result
    void endLevel() ;                                 // Records a final END_LEVEL event to .result
    void loadingDirectionFromFile() {}                // Overridden to do nothing in Save mode
public:
    SaveGame();

};
