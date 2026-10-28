#include <fstream>

#include "Steps.h"


// Loads the recorded steps from a file and returns a Steps object
Steps Steps::loadSteps(const std::string& filename) {
	Steps steps;
	std::ifstream steps_file(filename);
	steps_file >> steps.randomSeed;

	size_t size;
	steps_file >> size;

	while (!steps_file.eof() && size-- != 0) {
		size_t iteration;
		std::string actionStr;
		int player, step;
		ActionType action;

		steps_file >> iteration >> actionStr >> player >> step;

		if (actionStr == "MOVE") action = ActionType::MOVE;
		else if (actionStr == "SHOOT") action = ActionType::SHOOT;
		else if (actionStr == "SWITCH") action = ActionType::SWITCH;
		else if (actionStr == "STAY") action = ActionType::STAY;
		else action = ActionType::MOVE; // fallback

		steps.addStep(iteration, action, player, step);
	}
	return steps;
}

// Saves all recorded steps to a file in a readable format
void Steps::saveSteps(const std::string& filename) const {
	std::ofstream steps_file(filename);
	steps_file << randomSeed << '\n' << steps.size();

	for (const auto& step : steps) {
		size_t iteration = std::get<0>(step);
		ActionType action = std::get<1>(step);
		int player = std::get<2>(step);
		int stepVal = std::get<3>(step);

		std::string actionStr;
		switch (action) {
		case ActionType::MOVE: actionStr = "MOVE"; break;
		case ActionType::SHOOT: actionStr = "SHOOT"; break;
		case ActionType::SWITCH: actionStr = "SWITCH"; break;
		case ActionType::STAY: actionStr = "STAY"; break;
		}

		steps_file << '\n' << iteration << ' ' << actionStr << ' ' << player << ' ' << stepVal;
	}
}

