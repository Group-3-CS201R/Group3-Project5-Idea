#include <iostream>
#include <string>
#include <vector>

#include "Player.h"

using namespace std;

Player::Player() {}

Player::Player(string name, int num) : playerName(name), playerNum(num), netWorth(1500), playerPosition(0),
inJail(false), rollsInJail(0), numRailRoads(0)
{
	numOfColor.insert({ "PINK", 0 });
	numOfColor.insert({ "ORANGE", 0 });
	numOfColor.insert({ "RED", 0 });
	numOfColor.insert({ "YELLOW", 0 });
	numOfColor.insert({ "GREEN", 0 });
	numOfColor.insert({ "NAVY", 0 });
	numOfColor.insert({ "PURPLE", 0 });
	numOfColor.insert({ "BLUE", 0 });
}

// textual output of player info. to-be deleted if/when GUI is created
void Player::PrintPlayerInfo() {
	cout << playerName << endl;
	cout << playerNum << endl;
	cout << netWorth << endl;
}

void Player::MovePosition(int toMove) {
	playerPosition += toMove;
	if (playerPosition > 39) {
		playerPosition -= 39;
	}
}

int Player::GetPosition() {
	return playerPosition;
}

bool Player::IsInJail() {
	if (rollsInJail == 3) { inJail = false; }
	rollsInJail++;
	if (inJail) {
		return true;
	}
	else {
		return false;
	}
}

int Player::GetNetWorth() {
	return netWorth;
}
string Player::GetName() {
	return playerName;
}
string Player::GetColor() {
	return playerColor;
}

void Player::AddToColorMap(string colorToAdd) {
	numOfColor[colorToAdd]++;
}

bool Player::CanPurchaseHouse(string colorToPurchase) {
	if (colorToPurchase == "PINK" && numOfColor[colorToPurchase] == 3) {
		return true;
	} else if (colorToPurchase == "ORANGE" && numOfColor[colorToPurchase] == 3) {
		return true;
	} else if (colorToPurchase == "RED" && numOfColor[colorToPurchase] == 3) {
		return true;
	} else if (colorToPurchase == "YELLOW" && numOfColor[colorToPurchase] == 3) {
		return true;
	} else if (colorToPurchase == "GREEN" && numOfColor[colorToPurchase] == 3) {
		return true;
	} else if (colorToPurchase == "PINK" && numOfColor[colorToPurchase] == 3) {
		return true;
	} else if (colorToPurchase == "NAVY" && numOfColor[colorToPurchase] == 2) {
		return true;
	} else if (colorToPurchase == "PURPLE" && numOfColor[colorToPurchase] == 2) {
		return true;
	} else if (colorToPurchase == "BLUE" && numOfColor[colorToPurchase] == 3) {
		return true;
	}
	else {
		return false;
	}
}

void Player::PayRent(int toPay) {
	if (netWorth >= toPay) {
		netWorth -= toPay;
	}
	else {
		netWorth = 0;	
	}
}

void Player::CollectRent(int toCollect) {
	netWorth += toCollect;
}

//FIXME: Needs error checking for if property can be purchased
void Player::PurchaseProperty(int propCost) {
	netWorth -= propCost;
}