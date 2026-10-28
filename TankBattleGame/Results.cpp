#include <limits>
#include <fstream>
#include <sstream>
#include <iostream>  

#include "Results.h"
constexpr int EMPTY_ = -1;
constexpr int ZERO = 0;
constexpr int ONE = 1;


//Converts an EventType enum to a string (used for saving to file).
std::string eventTypeToString(EventType type) {
	switch (type) {
	case EventType::HIT_TANK: return "HIT_TANK";
	case EventType::HIT_CANNON: return "HIT_CANNON";
	case EventType::MINE: return "MINE";
	case EventType::END_LEVEL: return "END_LEVEL";
	default: return "UNKNOWN";
	}
}

//Converts a string back to an EventType enum (used when loading from)
EventType stringToEventType(const std::string& str) {
	if (str == "HIT_TANK") return EventType::HIT_TANK;
	if (str == "HIT_CANNON") return EventType::HIT_CANNON;
	if (str == "MINE") return EventType::MINE;
	if (str == "END_LEVEL") return EventType::END_LEVEL;
	return EventType::END_LEVEL; // default fallback
}

//Writes all game results to a file in human-readable format
void Results::saveResults(const std::string& filename) const {
	std::ofstream results_file(filename);
	results_file << results.size() << '\n';

	for (const auto& [iteration, type, player, tank, x, y, scorePL1, scorePL2] : results) {
		results_file << "TIME " << iteration << ' '
			<< eventTypeToString(type) << ' '
			<< "P" << player << ' '
			<< "T" << tank << ' '
			<< "AT " << x << ' ' << y << ' '
			<< "SCORE P0 " << scorePL1 << ' '
			<< "SCORE P1 " << scorePL2 << '\n';
	}
	results_file.close();
}

//Reads a .result file and reconstructs the list of results
Results Results::loadResults(const std::string& filename) {
	Results results;
	std::ifstream in(filename);
	if (!in) return results;

	std::string line;
	while (std::getline(in, line)) {
		std::istringstream iss(line);
		std::string temp, typeStr;
		std::string playerToken, tankToken, dummy, score0Token, score1Token;
		size_t iteration;
		int player = EMPTY_, tank = EMPTY_, x = ZERO, y = ZERO, scorePL1 = ZERO, scorePL2 = ZERO;

		iss >> temp >> iteration;        // TIME <iteration>
		iss >> typeStr;
		EventType type = stringToEventType(typeStr);

		iss >> playerToken;
		if (playerToken.size() > ONE && playerToken[0] == 'P') {
			player = std::stoi(playerToken.substr(ONE));
		}
		else {
			//std::cerr << "Invalid player token: " << playerToken << std::endl;
			continue;
		}

		iss >> tankToken;
		if (tankToken.size() > 1 && tankToken[0] == 'T') {
			tank = std::stoi(tankToken.substr(ONE));
		}
		else {
			//std::cerr << "Invalid tank token: " << tankToken << std::endl;
			continue;
		}

		iss >> temp >> x >> y;  // temp == "AT"

		iss >> dummy >> score0Token >> scorePL1;  // SCORE P0 <score>
		iss >> dummy >> score1Token >> scorePL2;  // SCORE P1 <score>
		/*
		//Print test
		std::cout << "Loaded result: iteration=" << iteration
			<< ", type=" << eventTypeToString(type)
			<< ", player=" << player
			<< ", tank=" << tank
			<< ", pos=" << x << "," << y
			<< ", scores=" << scorePL1 << "/" << scorePL2
			<< std::endl;*/
		results.addResult(iteration, type, player, tank, x, y, scorePL1, scorePL2);
	}

	return results;
}

