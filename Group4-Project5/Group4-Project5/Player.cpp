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

//FIXME: Change to 39 after testing
void Player::MovePosition(int toMove) {
	playerPosition += toMove;
	if (playerPosition > 39) {
		cout << "You passed GO. You Receive $200 from the bank." << endl;
		netWorth += 200;
		playerPosition -= 39;
	}
}

int Player::GetPosition() {
	return playerPosition;
}

void Player::GoToJail() {
	cout << "You have been put in jail. You will need to either roll a double, pay $50 to get out, or wait 3 turns then pay $50" << endl;
	inJail = true;
}

bool Player::IsInJail() {
	if (rollsInJail == 3) { 
		inJail = false; 
		rollsInJail = 0;
	}
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

// adds item to owned properties to handle the case of bankruptcy 
void Player::PurchaseProperty(int propCost, int position) {
	netWorth -= propCost;
	propsOwned.push_back(position);
}

// Checks if player is out of money, meaning that the player is bankrupt
bool Player::IsBankrupt() {
	if (netWorth <= 0) { return true; }
	return false;
}