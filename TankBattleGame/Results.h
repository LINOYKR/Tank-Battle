#pragma once
#include <windows.h>
#include <iostream>
#include <list>

constexpr int EMPTY = -1;

// The types of events that can appear in the file
enum class EventType { HIT_TANK, HIT_CANNON, MINE, END_LEVEL };

class Results {
private:
	// Stores a list of results from the game
	std::list<std::tuple<size_t, EventType, int, int, int, int, int, int>> results;

public: 

	static Results loadResults(const std::string& filename); // Loads results from a file
	void saveResults(const std::string& filename) const;     // Saves the results to a file
	
	// Adds a new result to the list
	void addResult(size_t iteration, EventType type, int player, int tank, int x, int y, int scorePL1, int scorePL2) {
		results.push_back(std::make_tuple(iteration, type, player, tank, x, y, scorePL1, scorePL2));
	}
	// Returns the first result in the list and removes it
	std::tuple<size_t, EventType, int, int, int, int, int, int> popResult() {
		if (results.empty()) {
			return std::make_tuple(0, EventType::END_LEVEL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY);
		}
		auto result = results.front();
		results.pop_front();
		return result;
	}
	// Checks if the game has ended up to a given iteration (or if there are no results).
	bool isFinishedBy(size_t iteration) const {
		return results.empty() || std::get<0>(results.back()) <= iteration;
	}
	// Checks if there is a result that matches the current iteration.
	bool isNextStepOnIteration(size_t iteration) const {
		return !results.empty() && std::get<0>(results.front()) == iteration;
	}
	// Clears the entire results list
	void clear() {
		results.clear();
	}
};
