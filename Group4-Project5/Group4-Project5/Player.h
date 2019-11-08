#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Player {
public:
	Player();
	Player(string name, int playerNum);
	void PrintPlayerInfo();
	int GetNetWorth();
	string GetName();
	string GetColor();
	void MovePosition(int toMove);
	int GetPosition();
	bool IsInJail();
	void AddToColorMap(string colorToAdd);
	bool CanPurchaseHouse(string colorToPurchase);
	void PayRent(int toPay);
	void CollectRent(int toCollect);
	void PurchaseProperty(int propCost);
private:
	string playerName;
	string playerColor;
	int numRailRoads;
	int playerNum;
	int netWorth;
	int playerPosition;
	int rollsInJail;
	bool inJail;
	map<string, int> numOfColor;
};