#include "goose.h"
#include <string>
#include <iostream>

using namespace std;

goose::goose():block("goose", 19){}

goose::~goose(){}

void goose::action(){
	cout << "Attacked by a flock of nesting geese! CAREFUL!!!" << endl;
	string continue1;
	cout << "Press any key to continue" << endl;
	cout << ">";
	cin >> continue1;
}
