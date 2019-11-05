#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>

#include "Dice.h"
#include "Property.h"
#include "Player.h"
#include "Railroad.h"
#include "Action.h"
#include "Tile.h"
#include "Utility.h"
#include "GameLogic.h"

using namespace std;


GameLogic::GameLogic(string name1, string name2) {
	player1 = Player(name1, 1);
	player2 = Player(name2, 2);
	dice1 = Dice();
	dice2 = Dice();
	player1Turn = true;
}

void GameLogic::PlayGame() {
	int numDoubles = 0;
	int turnRoll = 0;
int dummy = 0;
	while (true) {
		dice1.RollDice();
		dice2.RollDice();
		turnRoll = dice1.GetDiceValue() + dice2.GetDiceValue();
		// this handles the case of 1 or more dice rolls that have the same value
		while (dice1.GetDiceValue() == dice2.GetDiceValue()) {
			numDoubles++;
			if (numDoubles == 3) {
				//FIXME: Execute go to jail action for current player
				break;
			} else if (player1Turn) {
				if (player1.GetPosition() + turnRoll >= 40) { turnRoll = turnRoll - 40; }
				player1.MovePosition(turnRoll);
				//FIXME: Execute purchse/pay-rent/action property action
			}
			else {
				if(player2.GetPosition() + turnRoll >= 40) { turnRoll = turnRoll - 40; }
				player2.MovePosition(turnRoll);
				//FIXME: Execute purchse/pay-rent/action property action
			}
			dice1.RollDice();
			dice2.RollDice();
			turnRoll = dice1.GetDiceValue() + dice2.GetDiceValue();
		}
		// this handles the case when the dice rolls do not have the same values
		if (player1Turn) {
			if (player1.GetPosition() + turnRoll >= 40) { turnRoll = turnRoll - 40; }
			player1.MovePosition(turnRoll);
			//FIXME: Execute purchse/pay-rent/action property action
		}
		else {
			if (player2.GetPosition() + turnRoll >= 40) { turnRoll = turnRoll - 40; }
			player2.MovePosition(turnRoll);
			//FIXME: Execute purchse/pay-rent/action property action
		}
		player1Turn = !player1Turn;
	}
}

void GameLogic::FillGameBoard() {
	ifstream gameProps("game_props.txt");
	string propType;
	string name;
	string color;
	int cost;
	int rentBase;
	int rent1House;
	int rent2House;
	int rent3House;
	int rent4House;
	int rentHotel;
	int mortgage;
	int houseCost;
	int hotelCost;
	while (!gameProps.eof()) {
		gameProps >> propType;
		if (propType == "Property") {
			gameProps >> name;
			gameProps >> color;
			gameProps >> cost;
			gameProps >> rentBase;
			gameProps >> rent1House;
			gameProps >> rent2House;
			gameProps >> rent3House;
			gameProps >> rent4House;
			gameProps >> rentHotel;
			gameProps >> mortgage;
			gameProps >> houseCost;
			gameProps >> hotelCost;
			boardSquares.push_back(new Property(name, color, cost, rentBase, rent1House, rent2House, rent3House, rent4House, rentHotel, mortgage, houseCost, hotelCost));
		}
		else if (propType == "Action") {
			gameProps >> name;
			boardSquares.push_back(new Action(name));
		}
		else if (propType == "Railroad") {
			gameProps >> name;
			gameProps >> cost;
			gameProps >> rent1House;
			gameProps >> rent2House;
			gameProps >> rent3House;
			gameProps >> rent4House;
			gameProps >> mortgage;
			boardSquares.push_back(new Railroad(name, cost, rent1House, rent2House, rent3House, rent4House, mortgage));
		}
		else {
			gameProps >> name;
			gameProps >> cost;
			gameProps >> mortgage;
			boardSquares.push_back(new Utility(name, cost, mortgage));
		}
	}
}

void GameLogic::PrintBoard() {
	for (int i = 0; i < boardSquares.size(); ++i) {
		boardSquares.at(i)->PrintDescription();
		cout << endl;
	}
}