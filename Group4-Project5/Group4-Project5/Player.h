#pragma once
#include <iostream>
#include <string>
#include <vector>

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
private:
	string playerName;
	string playerColor;
	int playerNum;
	int netWorth;
	int playerPosition;
};