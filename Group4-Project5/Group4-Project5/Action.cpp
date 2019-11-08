#include <iostream>
#include <string>

#include "Action.h"

using namespace std;

Action::Action(string name) : Tile(name, "Action") {}

string Action::GetActionType() {
	return this->GetName();
}

//uses action type to print out the proper description
void Action::PrintDescription() {
	if (this->GetName() == "GO") {
		cout << "You passed go. You receive $200 from the bank" << endl;
	}
	else {
		cout << this->GetName() << endl;
	}
}