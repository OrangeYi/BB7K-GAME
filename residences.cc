#include "residences.h"
#include "player.h"
#include <iostream>
#include <string>
#include "board.h"
#include "display.h"
using namespace std;
residences::residences(string name, int cost, int pos, board* b):building(name, pos,b){
	this->cost = cost;
	mortgaged = false;
	owner = NULL;
}
player* residences::getowner(){
    return owner;
}

int residences::getcost(){
    return cost;
}

residences::~residences(){}

void residences::tomortgaged(){
	this->mortgaged = true;
}

void residences::unmortgaged(){
	this->mortgaged = false;
}

bool residences::getmortgaged(){
	return this->mortgaged;
}

int residences::getpay(){
	int num = owner->resnum;
	if(num == 1) {return 25;}
	else if(num == 2) {return 50;}
	else if(num == 3) {return 100;}
	else {return 200;}
}


void residences::setowner(player* players){
	owner = players;
}

void residences::changepay(){}

void residences::action() {
    if (owner == NULL && (whosturn->getbalance() > cost)) {
        cout << "You can buy "<< this->getname() << ", using $" << cost << " yes(y) or no(n)" << endl;
        string temp;
        cin >> temp;
        if (temp == "y") {
            whosturn->setbalance(-cost);
            owner = whosturn;
            whosturn->addbuilding(this);

            whosturn->getdisplay()->notifyo(this->position, whosturn->getpiece());

        } else if (temp == "n") {
            b->auction(this);
        } else {
            cout << "Wrong command, please enter yes(y) or no(n)" << endl;
        }
    } else if (this->getmortgaged()){
            cout << "This propertie is in mortgaged, do not need to pay anything!!" << endl;
            string continue1;
            cout << "Press any key to continue" << endl;
            cout << ">";
            cin >> continue1;
            return;
        }
    else if (owner != NULL && owner != whosturn) {
        cout << "you paid $" << getpay() << " to " << owner->getname() << endl;
        whosturn->setbalance(- getpay());
        owner->setbalance(getpay());
        string continue1;
        cout << "Press any key to continue" << endl;
        cout << ">";
        cin >> continue1;
    }
}

