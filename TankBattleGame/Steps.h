#pragma once

#include <list>
enum class ActionType { MOVE, SHOOT, SWITCH,STAY };

class Steps {

	long randomSeed = 0;
	std::list<std::tuple<size_t, ActionType, int,int>> steps;

public:
	//Loads game steps from a .steps file and returns a Steps object filled with recorded actions.
	static Steps loadSteps(const std::string& filename);
	// Saves the steps to a .steps file so that the game can be replayed exactly.
	void saveSteps(const std::string& filename) const;

	// Returns the random seed
	long getRandomSeed() const {
		return randomSeed;
	}
	// Sets the random seed
	void setRandomSeed(long seed) {
		randomSeed = seed;
	}
	// Adds a new recorded action (step) to the list
	void addStep(size_t iteration, ActionType type,int player,int step) {
		steps.push_back({ iteration, type,player,step });
	}
	// Checks if the next recorded step is meant for the current game
	bool isNextStepOnIteration(size_t iteration) const {
		return !steps.empty() && std::get<0>(steps.front()) == iteration;
	}
	// Removes and returns the first step in the queue
	std::tuple<size_t, ActionType, int, int> popStep() {
		auto step = steps.front();
		steps.pop_front();
		return step;
	}
	// Clears all recorded steps
	void clear() {
		steps.clear();
	}

};
