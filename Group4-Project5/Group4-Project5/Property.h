#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Tile.h"

using namespace std;

class Property : public Tile {
public:
	Property(string propName, string color, int propertyCost, int mortgageValue, int rentBase, int rentOneHouse, int rentTwoHouse,
		int rentThreeHouse,int rentFourHouse, int rentHotel, int houseBuyCost, int hotelBuyCost);
	void PrintDescription();
	bool PropIsOwned();
	bool HotelIsOwned;
	int GetCost();
	int GetRent();
	int GetMortgage();
private:
	string propColor;
	bool propOwned;
	int propCost;
	int housesOnProp;
	vector<int> rents;
	int mortgageValue;
	int houseCost;
	int hotelCost;
	bool hotelOwned;
};