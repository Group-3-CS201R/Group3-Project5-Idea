#pragma once
#include <iostream>
#include <string>

#include "Tile.h"

using namespace std;

class Utility : public Tile {
public:
	Utility() {};
	Utility(string name, int cost, int mortgage);
	int RentCalculator(int diceRoll);
	void PrintDescription();
private:
	int propCost;
	int mortgageValue;
	int numOwned;
};