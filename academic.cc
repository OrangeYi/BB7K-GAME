#include "academic.h"
#include "player.h"
#include <iostream>
#include <string>
#include "board.h"
#include "display.h"

using namespace std;

player* academic::getowner(){return owner;}

academic::~academic() {}

academic::academic(string name, string monblock, int cost, int imp, int pos, int tui[], board* b, int Mono[]):building(name, pos, b), numimp(0){
    mortgaged = false;
    owner = NULL;
    this->cost = cost;
    impcost = imp;
    monopolyblock = monblock;
    numimp = 0;
    pay = tui[numimp];
    for(int i = 0; i < 6; ++i){
        tuition[i] = tui[i];
    }
    for (int i = 0; i < 3; ++i)
    {
        Monopoly[i] = Mono[i];
    }
}
int academic::getPosition(){
    return position;
}

void academic::improve(string cmd){
	if (cmd == "buy") {
        numimp += 1;
        owner->setbalance(- impcost);
        owner->settotalAsset(+ impcost);
        changepay();
        whosturn->getdisplay()->notify(position, numimp, whosturn->getpiece());
        cout << "Improve success" << endl;
        string continue1;
        cout << "Press any key to continue" << endl;
        cout << ">";
        cin >> continue1;

    }
    if (cmd == "sell" ) {
        numimp -=1;
        owner->setbalance(impcost*0.5);
        owner->settotalAsset(-impcost);
        changepay();
        whosturn->getdisplay()->notify(position, -1, whosturn->getpiece());
        cout << "Improve success" << endl;
        string continue1;
        cout << "Press any key to continue" << endl;
        cout << ">";
        cin >> continue1;
    }
}

int academic::getcost(){
	return this->cost;
}


void academic::tomortgaged(){
	this->mortgaged = true;
}

void academic::unmortgaged(){
	this->mortgaged = false;
}

bool academic::getmortgaged(){
	return this->mortgaged;
}

int academic::getpay(){
	return pay;
}
void academic::changepay(){
    pay = tuition[numimp];
}

void academic::setowner(player* players){
	owner = players;
}

void academic::action() {//
    if (owner == NULL && (whosturn->getbalance() > cost)) {
        cout << "You can buy "<< this->getname() << ", using $" << cost << " yes(y) or no(n)" << endl;
        string temp;
        cin >> temp;
        if (temp == "y") {
            whosturn->setbalance(-cost);
            owner = whosturn;
            whosturn->addbuilding(this);

            whosturn->getdisplay()->notify(this->position, 0, whosturn->getpiece());

        } else if (temp == "n") {
            this->b->auction(this);
        } else {
            cout << "Wrong command, please enter yes(y) or no(n)" << endl;
        }
    }
    else if (owner != NULL && owner != whosturn) {
        bool doubles = false;
        int count = 0;
        if (this->getmortgaged())
        {
            cout << "This propertie is in mortgaged, do not need to pay anything!!" << endl;
            string continue1;
            cout << "Press any key to continue" << endl;
            cout << ">";
            cin >> continue1;
            return;
        }
        if (this->numimp == 0)
        {
            int first = this->Monopoly[0];
            int second = this->Monopoly[1];
            int third = this->Monopoly[2];
            for (int i = 0; i < owner->intimnum; ++i)
            {
                int postemp = owner->buildings[i]->getPosition();
                if (postemp == first || postemp == second || postemp == third)
                {
                    count += 1;
                }
                if(third == -1 && count == 2){
                    doubles = true;
                    break;
                }
                else if(count == 3){
                    doubles = true;
                }
            }
        }
        if(!doubles){
            cout << "you paid $" << getpay() << " to " << owner->getname() << endl;
            whosturn->setbalance(- getpay());
            owner->setbalance(getpay());
            string continue1;
            cout << "Press any key to continue" << endl;
            cout << ">";
            cin >> continue1;
        }else{
            cout << owner->getname() << " has all the Monopolys, so you need to pay double!" << endl;
            int doublepay = getpay()*2;
            cout << "you paid $" << doublepay << " to " << owner->getname() << endl;
            whosturn->setbalance(- doublepay);
            owner->setbalance(doublepay);
            string continue1;
            cout << "Press any key to continue" << endl;
            cout << ">";
            cin >> continue1;
        }
    }
    else if (owner == whosturn) {
        bool doubles = false;
        int count = 0;
        int first = this->Monopoly[0];
        int second = this->Monopoly[1];
        int third = this->Monopoly[2];
        for (int i = 0; i < owner->intimnum; ++i)
        {
            int postemp = owner->buildings[i]->getPosition();
            if (postemp == first || postemp == second || postemp == third)
            {
                count += 1;
            }
            if(third == -1 && count == 2){
                doubles = true;
                break;
            }
            else if(count == 3){
                doubles = true;
            }
        }
        if (!doubles)
        {
            cout << "You need to have all Monopoly then improve" << endl;
            string continue1;
            cout << "Press any key to continue" << endl;
            cout << ">";
            cin >> continue1;
            return;
        }
        if (numimp < 5 || doubles) {
            cout << "Would you like to improve this block using $"<< impcost <<".(y) or (n) or sell the improvement (s)"<< endl;
            string temp;
            cin >> temp;
            if (temp == "y") {
                cout << "block improve. -" << impcost << endl;
                improve("buy");
            } else if (temp == "n") {
            } else if (temp == "s") {
                cout << "sell complete. +" << impcost << endl;
                improve("sell");
            } else {
                cout << "wrong command. please enter yes(y) no(n) or sell(s)" <<endl;
            }
        }
    }
    
}



            
            
            
            
            
            
            
            
            
