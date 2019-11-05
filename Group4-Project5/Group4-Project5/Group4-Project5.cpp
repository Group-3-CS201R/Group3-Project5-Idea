// Names: Bao Ngo, Gabe Nell, Nolan Rice
// Instructor: Michael Essmyer
// Project #5

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "Dice.h"
#include "Property.h"
#include "Player.h"
#include "Railroad.h"
#include "Action.h"
#include "Tile.h"
#include "Utility.h"
#include "GameLogic.h"

using namespace std;

int main() {
	/*Dice dice1;
	Dice dice2;

	vector<Tile*> boardTiles;

	Property* statesAve = new Property("States Avenue", "Green", 140, 70, 10, 50, 150,
		450, 625, 750, 100, 100);

	Player player1("Jacob", 1);

	Railroad* railroad1 = new Railroad("Pensylvania Railroad", 150, 100, 25, 50, 100, 200);

	Action* action1 = new Action("GO");

	Utility* utility1 = new Utility("Electric Company", 300, 75);

	boardTiles.push_back(statesAve);
	boardTiles.push_back(railroad1);
	boardTiles.push_back(action1);
	boardTiles.push_back(utility1);

	dice1.RollDice();
	dice2.RollDice();

	cout << "Dice1: " << dice1.GetDiceValue() << " Dice2: " << dice2.GetDiceValue() << endl;
	cout << endl;
	player1.PrintPlayerInfo();
	cout << endl;

	for (int i = 0; i < boardTiles.size(); ++i) {
		boardTiles.at(i)->PrintDescription();
		cout << endl;
	}*/

	GameLogic gameObject("John", "Jane");

	gameObject.FillGameBoard();
	gameObject.PrintBoard();

	return 0;
}
