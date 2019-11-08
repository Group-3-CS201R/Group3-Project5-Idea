#include <iostream>
#include <string>

#include "Utility.h"
#include "Tile.h"

using namespace std;

Utility::Utility(string name, int cost, int mortgage) : Tile(name, "Utility"), propCost(cost),
	mortgageValue(mortgage), numOwned(0), propOwned(false), ownedByNum(0) {}

int Utility::GetOwnedBy() {
	return ownedByNum;
}

void Utility::SetOwnedBy(int num) {
	ownedByNum = num;
	propOwned = true;
}

int Utility::GetCost() {
	return propCost;
}

bool Utility::PropIsOwned() {
	return propOwned;
}

void Utility::PrintDescription() {
	cout << this->GetName() << endl;
	cout << "Cost" << propCost << endl;
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