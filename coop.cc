#include "coop.h"
#include "player.h"
#include <string>
#include <iostream>
using namespace std;

coop::coop():block("COOP FEE", 38){}

void coop::action(){
	whosturn->setbalance( - 150);
	cout << "Pay the coop fee $150!" << endl;
	cout << "Press any key to continue" << endl;
	cout << ">";
	string continue1;
	cin >> continue1;
}

coop::~coop(){}
