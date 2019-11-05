#include <iostream>
#include <string>

#include "Utility.h"
#include "Tile.h"

using namespace std;

Utility::Utility(string name, int cost, int mortgage) : Tile(name, "Utility"), propCost(cost),
	mortgageValue(mortgage), numOwned(0) {}

void Utility::PrintDescription() {
	cout << this->GetName() << endl;
	cout << propCost << endl;
	cout << "Mortgage value: $" << mortgageValue << endl;
}

int Utility::RentCalculator(int diceRoll) {
	if (numOwned == 1) {
		return (4 * diceRoll);
	}
	else if (numOwned == 2){
		return 10 * diceRoll;
	}
}