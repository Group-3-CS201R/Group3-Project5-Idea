#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <map>
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

// Use map to show who owns what propert(0 - no one, 1 - player1, 2 - player2, -1 - not ownable)

GameLogic::GameLogic(string name1, string name2, string name3, string name4, string name5, string name6) {
	players.push_back(Player(name1, 1));
	players.push_back(Player(name2, 2));
	players.push_back(Player(name3, 3));
	players.push_back(Player(name4, 4));
	players.push_back(Player(name5, 5));
	players.push_back(Player(name6, 6));
	dice1 = Dice();
	dice2 = Dice();
	currentTurn = 0;
	FillGameBoard();
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
			}
			else {
				if (players.at(currentTurn).GetPosition() + turnRoll >= 40) { turnRoll = turnRoll - 40; }
				players.at(currentTurn).MovePosition(turnRoll);
				//FIXME: Execute purchse/pay-rent/action property action
			}
			dice1.RollDice();
			dice2.RollDice();
			turnRoll = dice1.GetDiceValue() + dice2.GetDiceValue();
		}
		// this handles the case when the dice rolls do not have the same values
		if (players.at(currentTurn).GetPosition() + turnRoll >= 40) { turnRoll = turnRoll - 40; }
		players.at(currentTurn).MovePosition(turnRoll);
		if (currentTurn < 5) {
			currentTurn++;
		}
		else {
			currentTurn = 0;
		}
	}
}

//FIXME: Should handle accessing the correct conatiner for the sequence. Possibly pass this to the property function
void GameLogic::SequenceDecision(int roll, bool p1Turn) {
	if (properties.find(roll) != properties.end()) {
		//PropertySequence(roll, turn);
	}
	else if (railroads.find(roll) != railroads.end()) {
		//RailroadSequence(roll, turn);
	}
	else if (utilities.find(roll) != utilities.end()) {
		//utilitiesSequence(roll, turn)
	}
	else {
		//actionSequence(roll, turn);
	}
}

/*
void GameLogic::PropertySequence(int position, bool p1Turn) {
	int cost = (boardSquares.at(position))->GetCost();
	string userResponse;
	if ((boardSquares.at(position))->PropIsOwned()) {
		if (p1Turn) {
			player1.PayRent(cost);
			player2.CollectRent(cost);
		}
		else {
			player2.PayRent(cost);
			player1.CollectRent(cost);
		}
	}
	else {
		cout << "Would you like to purchase this property? Cost: $" << cost << endl;
		//FIXME: Needs to error check for proper input
		cin >> userResponse;
		if (userResponse == "yes") {
			// FIXME: Check if player has the networth to purchase this property
			((Property*)(boardSquares.at(position)))->PurchaseProp();
			if (p1Turn) {
				player1.PurchaseProperty(cost);
				// add color to player1 list of owned properties
			}
			else {
				player2.PurchaseProperty(cost);
				// add color to player2 list of owned properties
			}
		}
	}
}
*/

void GameLogic::AuctionSequence() {
	//Program this late if time allows
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
	int index = 0;
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
			Property newProp = Property(name, color, cost, rentBase, rent1House, rent2House, rent3House, rent4House, rentHotel, mortgage, houseCost, hotelCost);
			properties.insert({ index, newProp });
		}
		else if (propType == "Action") {
			gameProps >> name;
			Action newAction = Action(name);
			actions.insert({ index, newAction });
		}
		else if (propType == "Railroad") {
			gameProps >> name;
			gameProps >> cost;
			gameProps >> rent1House;
			gameProps >> rent2House;
			gameProps >> rent3House;
			gameProps >> rent4House;
			gameProps >> mortgage;
			Railroad newRR = Railroad(name, cost, rent1House, rent2House, rent3House, rent4House, mortgage);
			railroads.insert({ index, newRR });
		}
		else {
			gameProps >> name;
			gameProps >> cost;
			gameProps >> mortgage;
			Utility newUtil = Utility(name, cost, mortgage);
			utilities.insert({ index, newUtil });
		}
		++index;
	}
}

void GameLogic::PrintBoard() {
	for (int i = 0; i < 18; ++i) {
		if (properties.find(i) != properties.end()) {
			//PropertySequence(roll, turn);
			properties[i].PrintDescription();
		}
		else if (railroads.find(i) != railroads.end()) {
			//RailroadSequence(roll, turn);
			railroads[i].PrintDescription();
		}
		else if (utilities.find(i) != utilities.end()) {
			//utilitiesSequence(roll, turn)
			utilities[i].PrintDescription();
		}
		else {
			//actionSequence(roll, turn);
			actions[i].PrintDescription();
		}
	}
}