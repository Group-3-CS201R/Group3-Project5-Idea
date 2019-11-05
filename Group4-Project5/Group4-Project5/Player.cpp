#include <iostream>
#include <string>
#include <vector>

#include "Player.h"

using namespace std;

Player::Player() {}

Player::Player(string name, int num) : playerName(name), playerNum(num), netWorth(1500), playerPosition(0) {}

// textual output of player info. to-be deleted if/when GUI is created
void Player::PrintPlayerInfo() {
	cout << playerName << endl;
	cout << playerNum << endl;
	cout << netWorth << endl;
}

void Player::MovePosition(int toMove) {
	playerPosition += toMove;
}

int Player::GetPosition() {
	return playerPosition;
}