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

GameLogic::GameLogic() {
	FillPlayersVect();
	dice1 = Dice();
	dice2 = Dice();
	currentTurn = 0;
	jailLocation = 10;
	//FIXME: Use these two variables to track if a player has one game (numPlayers = (numBankrupt - 1))
	numPlayers = 0;
	numBankrupt = 0;
	FillGameBoard();
}

void GameLogic::PlayGame() {
	int numDoubles = 0;
	int turnRoll = 0;
	int dummy = 0;
	string stallyBoi;
	while (true) {
		if (players.at(currentTurn).GetInJail()) { // checks to see if the player is in jail
			JailSequence();
			continue;
		}
		cout << endl << "Player: " << (currentTurn + 1) <<  ".\nPress any key to roll -> ";
		cin >> stallyBoi;
		cin.ignore();
		dice1.RollDice();
		dice2.RollDice();
		turnRoll = dice1.GetDiceValue() + dice2.GetDiceValue();
		cout << endl << "Player: " << (currentTurn + 1) << " Roll: " << turnRoll << endl;
		// this handles the case of 1 or more dice rolls that have the same value
		if (dice1.GetDiceValue() == dice2.GetDiceValue()) {

			// the player's number of doubles count increases
			players.at(currentTurn).IncrementDoubles();
			if (players.at(currentTurn).DoublesRolled() == 3) { // change this to 1 if you want to test jail
				players.at(currentTurn).MovePosition(jailLocation); // moves player to jail
				players.at(currentTurn).GoToJail(); // changes bool in class
				currentTurn++; // changes player turn and ends the jailed's turn
				if (currentTurn == players.size()) {
					currentTurn = 0;
				}
				continue;
			}
			cout << endl << "You have rolled " << players.at(currentTurn).DoublesRolled() << " double(s). Three doubles in a row will land you in Jail. Shake those dice carefully!" << endl << endl;
		}
		else { 
			players.at(currentTurn).ResetDoubles();  // clears the consecutive roll count
		}
		// this handles the case when the dice rolls do not have the same values
		//FIXME: Move this error checking into Player class
		cout << "\nYou currently have : $" << players.at(currentTurn).GetNetWorth() << "\n\n";
		players.at(currentTurn).MovePosition(turnRoll);
		SequenceDecision(players.at(currentTurn).GetPosition(), turnRoll);
		// FIXME: A queue should be implemented to get rid of this portion
		if (players.at(currentTurn).IsBankrupt()) {
			//FIXME: Execute bankruptcy property cleanup
		}
		currentTurn++;
		if (currentTurn == players.size()) {
			currentTurn = 0;
		}
	}
}


void GameLogic::SequenceDecision(int position, int roll) {
	if (properties.find(position) != properties.end()) {
		PropertySequence(position);
	}
	else if (railroads.find(position) != railroads.end()) {
		RailroadSequence(position);
	}
	else if (utilities.find(position) != utilities.end()) {
		UtilitySequence(position, roll);
	}
	else {
		ActionSequence(position);
	}
}

void GameLogic::RailroadSequence(int position) {
	int cost = railroads[position].GetCost();
	string userResponse;
	if (railroads[position].PropIsOwned()) {
		players.at(currentTurn).PayRent(cost);
		players.at(railroads[position].GetOwnedBy()).CollectRent(cost);
	}
	else {
		railroads[position].PrintDescription();
		cout << endl << "Would you like to purchase this property? -> ";
		//FIXME: Needs to error check for proper input
		cin >> userResponse;
		if (userResponse == "yes") {
			// FIXME: Check if player has the networth to purchase this property
			players.at(currentTurn).PurchaseProperty(railroads[position].GetCost(), position);
			railroads[position].SetOwnedBy(currentTurn);
		}
	}
}

void GameLogic::PropertySequence(int position) {
	int cost = properties[position].GetCost();
	string userResponse;
	if (properties[position].PropIsOwned()) {
		cout << "This property is owned by player number: " << properties[position].GetOwnedBy() << " you owe $" << properties[position].GetRent() << " in rent.";
		players.at(currentTurn).PayRent(cost);
		players.at(properties[position].GetOwnedBy()).CollectRent(cost);
	}
	else {
		properties[position].PrintDescription();
		cout << endl << "Would you like to purchase this property? (y/n) -> ";
		cin >> userResponse;
		while (userResponse != "y" && userResponse != "Y" && userResponse != "n" && userResponse != "N") {
			cout << "Please give a valid response (y/n)." << endl;
			cout << endl << "Would you like to purchase this property? (y/n) -> ";
			cin >> userResponse;
		}
		if (userResponse == "y" || userResponse == "Y") {
			// checks that player has enough money to purchase the proerty in question
			if (players.at(currentTurn).GetNetWorth() >= properties[position].GetCost()) {
				players.at(currentTurn).PurchaseProperty(properties[position].GetCost(), position);
				properties[position].SetOwnedBy(currentTurn);
			}
			else { cout << "Sorry, you don't have enough money to purchase this property." << endl; }
		}
	}
}

void GameLogic::UtilitySequence(int position, int roll) {
	int cost = utilities[position].GetCost();
	string userResponse;
	if (utilities[position].PropIsOwned()) {
		//FIXME: Print rent cost message
		players.at(currentTurn).PayRent(cost);
		players.at(utilities[position].GetOwnedBy()).CollectRent(cost);
	}
	else {
		utilities[position].PrintDescription();
		cout << endl << "Would you like to purchase this property? -> ";
		//FIXME: Needs to error check for proper input
		cin >> userResponse;
		if (userResponse == "yes") {
			// FIXME: Check if player has the networth to purchase this property
			players.at(currentTurn).PurchaseProperty(utilities[position].GetCost(), position);
			utilities[position].SetOwnedBy(currentTurn);
		}
	}
}

void GameLogic::ActionSequence(int position) {
	actions[position].PrintDescription();
}

void GameLogic::JailSequence() {
	cout << endl << "Player: " << (currentTurn + 1); // let's you know which player is in jail
	cout << "\nYou are in jail. You can either try to roll doubles or pay $50. If you fail to roll doubles after three turns you must pay $50.\n"; // asks them if they want to roll or pay
	cout << "r) Roll\np) Pay\n";
	string userResponse;
	cin >> userResponse;
	while (userResponse != "r" && userResponse != "R" && userResponse != "p" && userResponse != "P") {
		cout << "Please give a valid response (r/p)." << endl;
		cout << endl << "Would you like to roll or pay? (r/p) -> ";
		cin >> userResponse;
	}
	if ((userResponse == "r") || (userResponse == "R")) {  // if they choose roll the dice are rolled and if they equal they are free, else it increments by one until three
		dice1.RollDice();
		dice2.RollDice();
		cout << "You rolled " << dice1.GetDiceValue() << " and " << dice2.GetDiceValue() << endl;
		if (dice1.GetDiceValue() == dice2.GetDiceValue()) {
			cout << "You are free from jail.\n";
			players.at(currentTurn).FreeFromJail();
		}
		else {
			players.at(currentTurn).IsInJail();
		}
	}
	else if ((userResponse == "p") || (userResponse == "P")) { // if they 
		while (players.at(currentTurn).IsInJail()) {
			players.at(currentTurn).IsInJail();
		}
	}
	
	currentTurn++; // after the jail turn the player is switched
	if (currentTurn == players.size()) {
		currentTurn = 0;
	}
	
	// Player can pay $50 to get out now
	// Player can try to roll a double
	// Player can wait three turns then pay $50
}

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
	gameProps.close();
}

void GameLogic::FillPlayersVect() {
	string userName;
	string keepAdding;
	cout << "Welcome to Monopoly!" << endl;
	cout << "Enter at least two, and up to six, players' names to start playing the game." << endl << endl;
	for (int i = 0; i < 6; ++i) {
		cout << "Enter name of player #" << (i + 1) << " -> ";
		getline(cin, userName);
		players.push_back(Player(userName, (i + 1)));
		numPlayers++;
		if (i > 0) {
			cout << endl << "Would you like to add another player?\nPress y to add another player, any other key to start playing. -> ";
			getline(cin, keepAdding);
			if (keepAdding != "y" && keepAdding != "Y") {
				break;
			}
		}
		cout << endl;
	}
	cout << endl << "Let's get started!\n" << endl;
  }