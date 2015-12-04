#include "player.h"
#include "display.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

player::player(string name,string piece, int bal, int pos, Display* dis):name(name), piece(piece), balance(bal), position(pos), display(dis) {
    timeinrim = 0;
    canmove = true;
    rimcards = 0;
    totalAsset = balance;
    for (int i=0; i<40; i++) {
        buildings[i] = NULL;
    }
    inrim = false;
    gymnum=0;
    resnum=0;
    acanum=0;
    intimnum=0;
    canmove=true;
}
string player::getpiece(){
    return piece;
}

string player::getname() {
    return name;
}

int player::getbalance() {
    return balance;
}

int player::gettotalAsset() {
    return totalAsset;
}

int player::getrimcards() {
    return rimcards;
}

int player::getPosition() {
    return position;
}

void player::settotalAsset(int change) {
    totalAsset += change;
}

void player::addbuilding(building *b) {
    b->setowner(this);
    string name = b->getname();
    buildings[intimnum] = b;
    intimnum++;
    totalAsset += b->getcost();
    display->notify(b->getPosition(), 0, piece);
    if (name=="MKV" || name=="UWP" || name=="V1" || name=="REV") {
        resnum++;
    } else if (name=="CIF" || name=="PAC") {
        gymnum++;
    } else {
        acanum++;
        academic * temp = dynamic_cast <academic *> (b);
        totalAsset += temp->numimp * temp->impcost;
        temp->changepay();
    }
}




void player::removebuilding(building *b) {
    b->setowner(NULL);
    string name= b->getname();
    int acc=0;
    totalAsset -= b->getcost();
    display->notify(b->getPosition(), 0, "");
    while (acc<intimnum) {
        if (buildings[acc] == b) {
            buildings[acc]=NULL;
            intimnum--;
            break;
        }
        acc++;
    }
    if (name=="MKV" || name=="UWP" || name=="V1" || name=="REV") {
        resnum--;
    } else if (name=="CIF" || name=="PAC") {
        gymnum--;
    } else {
        acanum--;
    }
    for (int i=acc; i<intimnum; i++) {
        buildings[i] = buildings[i+1];
        if(i == 39){
            buildings[i] = NULL;
        }
    }
}

void player::improve(string name, string cmd) {
    for (int i=0; i<intimnum; i++) {
        if (buildings[i]->getname() == name) {
            academic * aca = dynamic_cast <academic *> (buildings[i]);
            if (aca->getowner() != this || aca == NULL) {
                cout << "You cannot improve this building" << endl;
                return;
            } 
            if (balance >= aca->impcost) {
                bool doubles = false;
                int count = 0;
                if (aca->numimp >= 0)
                {
                    int first = aca->Monopoly[0];
                    int second = aca->Monopoly[1];
                    int third = aca->Monopoly[2];

                    for (int i = 0; i < this->intimnum; ++i)
                    {
                        int postemp = this->buildings[i]->getPosition();
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
                if (doubles)
                {
                    aca->improve(cmd);
                    return;
                }else{
                    cout << "You need to have all Monopoly then improve" << endl;
                    string continue1;
                    cout << "Press any key to continue" << endl;
                    cout << ">";
                    cin >> continue1;
                }
                
            } else {
                cout << "you dont have enough money." << endl;
                return;
            }
        }
        
    }
}

void player::tomortgage(string name) {
    for (int i=0; i<intimnum; i++) {
        if (buildings[i]->getname() == name) {
            academic * acatemp = dynamic_cast <academic *> (buildings[i]);
            if (acatemp!=NULL && acatemp->numimp!=0) {
                cout << "You have improvements on this building. Mortgage fail." << endl;
                string continue1;
                cout << "Press any key to continue" << endl;
                cout << ">";
                cin >> continue1;
                display->print(cout);
                return;

            }
            
            buildings[i]->tomortgaged();
            balance += (buildings[i]->getcost() / 2);
            totalAsset += (buildings[i]->getcost() / 2);

            academic* aca = dynamic_cast<academic *> (buildings[i]);

            residences* res = dynamic_cast<residences *> (buildings[i]);

            gym* gy = dynamic_cast<gym *> (buildings[i]);

            string addmtopiece = "(M)" + piece;

            if(aca != NULL){
                display->notify(aca->getPosition(), 0, addmtopiece);
            }
            else if(res != NULL){
                display->notifyo(res->getPosition(), addmtopiece);
            }
            else{
                display->notifyo(gy->getPosition(), addmtopiece);
            }
            cout << name << " has been mortgaged." << endl;
            string continue1;
            cout << "Press any key to continue" << endl;
            cout << ">";
            cin >> continue1;
            display->print(cout);

            break;
        }
    }
}

void player::unmortgage(string name) {
    for (int i=0; i<intimnum; i++) {
        if (buildings[i]->getname() == name) {
            buildings[i]->unmortgaged();
            balance -= (buildings[i]->getcost() * 0.6);
            totalAsset -= (buildings[i]->getcost() * 0.6);


            academic* aca = dynamic_cast<academic *> (buildings[i]);

            residences* res = dynamic_cast<residences *> (buildings[i]);

            gym* gy = dynamic_cast<gym *> (buildings[i]);

            if(aca != NULL){
                display->notify(aca->getPosition(), 0, piece);
            }
            else if(res != NULL){
                display->notifyo(res->getPosition(), piece);
            }
            else{
                display->notifyo(gy->getPosition(), piece);
            }
            cout << name << " has been unmortgaged." << endl;
            string continue1;
            cout << "Press any key to continue" << endl;
            cout << ">";
            cin >> continue1;
            display->print(cout);

            return;
        }
    }
    
}

void player::allunmortgage() {
    for (int i=0; i<intimnum; i++) buildings[i]->unmortgaged();
}


void player::assets() {
    if (position == 4) cout << "You are on Tuition, cant look assets." << endl;
    else {
        cout << "Your balance is " << balance << endl;
        cout << "Your total assets value is " << totalAsset << endl;
        cout << "You have rim cups: " << rimcards << endl;
        cout << "You have following buildings: " << endl;
        for (int i=0; i<intimnum; i++) {
            cout << buildings[i]->getname() << endl;
        }
    }
}



void player::setposition(int pos) {
    position = pos;
}

void player::setrimcards(int rc) {
    rimcards += rc;
}

void player::setbalance(int change) {
    balance += change;
    totalAsset += change; //
}

void player::getOuttims() {
    cout << "You are in Tim line, can leave by paying $50(p), using rim cards(r), or roll a double(d)" << endl;
    cout << "you now have" << rimcards << endl;
    while (intimnum < 3) {
        char temp;
        cin >> temp;
        if (temp == 'p') {
            balance -= 50;
            totalAsset -= 50;
            move(0);
            break;
        } else if (temp == 'r') {
            if (rimcards > 0) {
                rimcards--;
                move(0);
                break;
            } else {
                cout << "You dont have enough rim cards, please using command paying $50(p) or roll a double(d)" << endl;
            }
        } else if (temp == 'd') {
            srand(time(NULL));
            int move1 = rand()%6 + 1;
            int move2 = rand()%6 + 1;
            if (move1 == move2) {
                position = (position + move1 + move2);
                intimnum = 0;
            } else {
                intimnum++;
                break;
            }
        } else {
            cout << "Please enter a correct command: paying $50 (p), using rim cards(r), roll a double (d)" << endl;
            cout << "you now have " << rimcards << " rim cards" << endl;
        }
        
        
    }
}

bool player::move() {
    if (canmove) {
        srand(time(NULL));
        int move1 = rand()%6 + 1;
        int move2 = rand()%6 + 1;
        cout << move1 << " : " << move2 << " rolls " << move1+move2 << endl;
        if(position + move1 + move2 > 39){
            cout << "Passing OSAP collect $200" << endl;
            setbalance(200);    
        }
        position = (position + move1 + move2)%40;
        display->notify(piece, position);
        if (move1 != move2) {
            canmove = false;
            return false;
        } else {
            cout << "Double!!" << endl;
            return true;
        }
        
    } else {
        cout << "You cant move" << endl;
        return false;
    }
}

bool player::movet(int roll1, int roll2) {
    if (canmove) {
        //srand(time(NULL));
        int move1 = roll1;
        int move2 = roll2;
        cout << move1 << " : " << move2 << " rolls " << move1+move2 << endl;
        if(position + move1 + move2 > 39){
            cout << "Passing OSAP collect $200" << endl;
            setbalance(200);    
        }
        position = (position + move1 + move2);
        while(position < 0){
            position += 40;
        }
        position = (position)%40;
        display->notify(piece, position);
        if (move1 != move2) {
            canmove = false;
            return false;
        } else {
            cout << "Double!!" << endl;
            return true;
        }
        
    } else {
        cout << "You cant move" << endl;
        return false;
    }
}

    


void player::move(int mo) {
    if (mo == 0) {
        int roll=0;
        while (roll < 3) {
            if (position == 31) {
                getOuttims();
                return;
            }
            srand(time(NULL));
            int move1 = rand()%6 + 1;
            int move2 = rand()%6 + 1;
            if (roll!=2 || move1!=move2) {
                position = (position + move1 + move2)%40;
                display->notify(piece, position);
            }
            roll++;
            if (move1 != move2) break;
        }
    } else{
        position = position + mo;
        while (position < 0)
        {
            position += 40;
        }
        display->notify(piece, position);
    }
}

            
player::~player() {}


Display* player::getdisplay(){
    return display;
}









