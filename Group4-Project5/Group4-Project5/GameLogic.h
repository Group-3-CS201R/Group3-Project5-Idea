#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <map>

#include "Dice.h"
#include "Property.h"
#include "Player.h"
#include "Railroad.h"
#include "Action.h"
#include "Tile.h"
#include "Utility.h"

using namespace std;

class GameLogic {
public:
	GameLogic(string name1, string name2, string name3, string name4, string name5, string name6);
	void PlayGame();
	void PropertySequence(int position, bool p1Turn);
	void AuctionSequence();
	void FillGameBoard();
	void PrintBoard();
	void SequenceDecision(int roll, bool p1Turn);
private:
	Dice dice1;
	Dice dice2;
	Player player1;
	Player player2;
	Player player3;
	Player player4;
	Player player5;
	Player player6;
	vector<Player> players;
	int currentTurn;
	map<int, Property> properties;
	map<int, Railroad> railroads;
	map<int, Utility> utilities;
	map<int, Action> actions;
};