#include "gym.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "player.h"
#include "board.h"
#include "display.h"
using namespace std;
gym::gym(string name, int cost, int pos, board* b):building(name,pos,b){
	this->cost = cost;
	mortgaged = false;
	owner = NULL;
}

gym::~gym(){}

player* gym::getowner(){
    return owner;
}

int gym::getcost(){
	return this->cost;
}


void gym::tomortgaged(){
	this->mortgaged = true;
}

void gym::unmortgaged(){
	this->mortgaged = false;
}

bool gym::getmortgaged(){
	return this->mortgaged;
}

int gym::getpay(){
	srand(time(NULL));
	int roll1 = rand()%6 + 1;
	int roll2 = rand()%6 + 1;
    cout << "You are in gym lets roll, good luck!" << endl;
    cout << "The result is :" << roll1 << " " << roll2 << endl;
	if(owner->gymnum == 2){
        cout << owner->getname() << " have two gyms you need to pay 10 times!!" << endl;
        return (10 * (roll1+roll2));
    }
	else {
        cout << "So you need to pay 4 * (" << roll1 << " + " << roll2 << ")" << endl; 
        return (4 * (roll1+roll2));}
    
}


void gym::setowner(player* players){
	owner = players;
}

void gym::changepay(){}

void gym::action() {
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
        int pay = getpay();
        cout << "you paid $" << pay << " to " << owner->getname() << endl;
        whosturn->setbalance(- pay);
        owner->setbalance(pay);
        string continue1;
        cout << "Press any key to continue" << endl;
        cout << ">";
        cin >> continue1;
    }
}
