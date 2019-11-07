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
	GameLogic(string name1, string name2);
	void PlayGame();
	void FillGameBoard();
	void PrintBoard();
private:
	Dice dice1;
	Dice dice2;
	Player player1;
	Player player2;
	vector<Tile*> boardSquares;
	map<int, int> ownershipMap;
	bool player1Turn;
};