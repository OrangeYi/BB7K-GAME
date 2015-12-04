#include "board.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "academic.h"
#include "coop.h"
#include "dctime.h"
#include "goose.h"
#include "gotodc.h"
#include "gym.h"
#include "needles.h"
#include "osap.h"
#include "residences.h"
#include "slc.h"
#include "tuition.h"
#include "block.h"
#include "player.h"
#include "display.h"
#include "building.h"

using namespace std;

player* board::whoseTurn() {
    return players[turn];
}

void board::addPlayer(player *p) {
    for (int i=0; i<8; i++) {
        if (players[i] == NULL) {
            players[i] = p;
            break;
        }
    }
}

void board::removePlayer(player *p) {
    p->getdisplay()->notify(p->getpiece(), 40);
    cout << "Player " << p->getname() << " was bankrupted. Rmoved from board" << endl;  
    for (int i = 0; i < 8; i++) {
        if (players[i] == p) {
            delete p;
            int loop = i;
            while (loop < 8) {
                players[loop] = players[loop+1];
                players[loop+1] = NULL;
                if (loop == 7){
                    players[loop] = NULL;
                }
                loop += 1;
            }
            break;
        }
    }
    int numofbuilding = p->intimnum;
    for (int i = 0; i < numofbuilding; ++i)
    {
        p->removebuilding(p->buildings[i]);
    }
}


int board::getturn() {
    return turn;
}

void board::addbuilding(string name, player * who) {
    for (int i=0; i<40; i++) {
        if (blocks[i]->getname() == name) {
            building* buil = dynamic_cast <building *> (blocks[i]);
            
            academic* aca = dynamic_cast<academic *> (buil);
            
            residences* res = dynamic_cast<residences *> (buil);
            
            if(aca != NULL){
                display->notify(i, 0, who->getpiece());
            }
            else if(res != NULL){
                display->notifyo(i, who->getpiece());
            }
            else{
                display->notifyo(i, who->getpiece());
            }
            
            who->addbuilding(buil);
            break;
        }
    }
}

void board::removebuilding(string name, player * who) {
    for (int i=0; i<40; i++) {
        if (blocks[i]->getname() == name) {
            building* buil = dynamic_cast <building *> (blocks[i]);
            
            academic* aca = dynamic_cast<academic *> (buil);
            
            residences* res = dynamic_cast<residences *> (buil);
            
            if(aca != NULL){
                display->notify(i, 0, "");
            }
            else if(res != NULL){
                display->notifyo(i, "");
            }
            else{
                display->notifyo(i, "");
            }
            
            who->removebuilding(buil);
            break;
        }
    }
}




void board::auction(building *b) {//
    int current = numplayers; //current number of biders
    vector<int> playtob;
    for(int i = 0; i < current ; ++i){
        playtob.push_back(i);
    }
    int max = b->getcost();
    int who = 0;
    int whopostion = 0;
    while (current > 0) {
        cout << players[who]->getname() << " please choose to bid(b) or withdraw(w)" << endl;
        cout << "current is " << max << endl;
        cout << ">";
        string temp;
        cin >> temp;

        if (temp == "w") {
            current--;
            if(current == 0){
                 if(max == b->getcost()){
                    cout << "No one want to buy this place" << endl;
                    string continue1;
                    cout << "Press any key to continue" << endl;
                    cout << ">";
                    cin >> continue1;
                    return;
                }else{
                    break;
                }
            }
            for(vector<int>::iterator it = playtob.begin(); it != playtob.end(); it++){
                if (*it == who)
                {
                    playtob.erase(it);
                    if(whopostion+1 > current){
                        who = playtob[0];
                        whopostion = 0;
                    }
                    else{
                        who = playtob[whopostion];
                    }
                    break;
                }
            }
        }
        else if (temp == "b") {
            cout << "please give the amount" << endl;
            cout << ">";
            int cmp;
            while(cin >> cmp){
                if (cmp > max) {
                    max = cmp;
                    whopostion = (whopostion+1)%current;
                    who = playtob[whopostion];
                    break;
                }
                else cout << "Can not underbid another player, please enter a higher price" << endl;
                cout << ">";
            }
        }
    }
    int whoismax = playtob[0];

    cout << players[whoismax]->getname() << " get " << b->getname() << " using " << "$" << max << endl;
    string continue1;
    cout << "Press any key to continue" << endl;
    cout << ">";
    cin >> continue1;

    b->setowner(players[whoismax]);
    
    players[whoismax]->addbuilding(b);
    
    players[whoismax]->setbalance(-max);

    this->display->notify(b->getPosition(), 0, players[whoismax]->getpiece());   
}


void board::bankrupt() {
    if (bankrupto == NULL) {
        rimcups -= players[turn]->getrimcards();
        players[turn]->allunmortgage();
        player *p = players[turn];
        
        for (int i=0; i<p->intimnum; i++) {
            auction(p->buildings[i]);
        }
        removePlayer(players[turn]);
        numplayers--;
    } else {
        for (int i=0; i<numplayers; i++) {
            if (players[i] == bankrupto) {
                for (int i=0; i<players[turn]->intimnum; i++) {
                    players[i]->addbuilding(players[turn]->buildings[i]);
                    if ((players[turn]->buildings[i])->getmortgaged()) {
                        players[i]->setbalance(- ((players[turn]->buildings[i])->getcost())*0.1);
                    }
                }
                
                break;
            }
        }
    }
}


void board::trade(string name, string give, string receive){

    player * playertemp;
    for (int i=0; i<numplayers; i++) {
        if (players[i]->getname() == name) {
            playertemp = players[i];
            break;
        }
    }


    int stringconvert1 = -1;
    istringstream(give) >> stringconvert1;
    if (stringconvert1 != -1) {
        if (players[turn]->getbalance() < stringconvert1) {
            cout << "You dont have enough money. Trade fail." << endl;
            return;
        }
    }

    int stringconvert2 = -1;
    istringstream(receive) >> stringconvert2;
    if (stringconvert2 != -1) {
        if (playertemp->getbalance() < stringconvert2) {
            cout << playertemp->getname() << " doesnt have enough money. Trade fail." << endl;
            return;
        }
    }

    if (stringconvert1 <= 0) {
        int has=0;
        for (int i=0; i<players[turn]->intimnum; i++) {
            if (players[turn]->buildings[i]->getname() == give) {
                string nametemp = players[turn]->buildings[i]->getname();
                if (nametemp!="MKV" && nametemp!="PAC" && nametemp!="CIF" 
                    && nametemp!="REV" && nametemp!="V1" && nametemp!="UWP") {
                    academic* tempchange = dynamic_cast<academic*>(players[turn]->buildings[i]);
                    if (tempchange->numimp > 0) {
                        cout << "You have improvements on this building. Trade Fail." << endl;
                        return;
                    }

                }
                has++;
                break;
            }
        }

        if (has==0) {
            cout << "You dont have the building. Trade fail." << endl;
            return;
        }
         
    }

    if (stringconvert2 <= 0) {
        int has=0;
        for (int i=0; i<playertemp->intimnum; i++) {
            if (playertemp->buildings[i]->getname() == receive) {
                string nametemp = players[turn]->buildings[i]->getname();
                if (nametemp!="MKV" && nametemp!="PAC" && nametemp!="CIF" 
                    && nametemp!="REV" && nametemp!="V1" && nametemp!="UWP") {
                    academic* tempchange = dynamic_cast<academic*>(players[turn]->buildings[i]);
                    if (tempchange->numimp > 0) {
                        cout << "You have improvements on this building. Trade Fail." << endl;
                        return;
                    }

                }
                has++;
                break;
            }
        }
        if (has==0) {
            cout << playertemp->getname() << " doesnt have the building. Trade fail." << endl;
            return;
        }
    }

    cout << name << " Would you like to receive " << give << " and give " << receive << " to " << players[turn]->getname() << endl;
    cout << "Please enter Yes(Y) or No(N)." << endl;
    string temp;
    while (cin >> temp) {
        if (temp == "Y") {
            int ismoney;
            if (istringstream(give) >> ismoney) {//nomair 500 dc

                for (int i = 0; i < 40; ++i)//testing moreged
                {
                    if (blocks[i]->getname() == receive)
                    {
                        building* tempchange = dynamic_cast<building*>(blocks[i]);
                        if (tempchange->getmortgaged())
                        {
                            cout << "You can not trade a mortgaged building" << endl;
                            string continue1;
                            cout << "Press any key to continue" << endl;
                            cout << ">";
                            cin >> continue1;
                            return;
                        }
                    }
                }

                players[turn]->setbalance(-ismoney);
                for (int i=0; i<numplayers; i++) {
                    if (players[i]->getname() == name) {
                        players[i]->setbalance(ismoney);
                        removebuilding(receive, players[i]);
                        break;
                    }
                }
                addbuilding(receive, players[turn]);
            } else if (istringstream(receive) >> ismoney) {//sean mc 500

                for (int i = 0; i < 40; ++i)//testing moreged
                {
                    if (blocks[i]->getname() == give)
                    {
                        building* tempchange = dynamic_cast<building*>(blocks[i]);
                        if (tempchange->getmortgaged())
                        {
                            cout << "You can not trade a mortgaged building" << endl;
                            string continue1;
                            cout << "Press any key to continue" << endl;
                            cout << ">";
                            cin >> continue1;
                            return;
                        }
                    }
                }

                players[turn]->setbalance(ismoney);
                removebuilding(give, players[turn]);
                for (int i=0; i<numplayers; i++) {
                    if (players[i]->getname() == name) {
                        players[i]->setbalance(-ismoney);
                        addbuilding(give, players[i]);
                        break;
                    }
                }
            } else {//kirsten dc mc
                for (int i = 0; i < 40; ++i)//testing moreged
                {
                    if (blocks[i]->getname() == receive)
                    {
                        building* tempchange = dynamic_cast<building*>(blocks[i]);
                        if (tempchange->getmortgaged())
                        {
                            cout << "You can not trade a mortgaged building" << endl;
                            string continue1;
                            cout << "Press any key to continue" << endl;
                            cout << ">";
                            cin >> continue1;
                            return;
                        }
                    }
                }
                for (int i = 0; i < 40; ++i)//testing moreged
                {
                    if (blocks[i]->getname() == give)
                    {
                        building* tempchange = dynamic_cast<building*>(blocks[i]);
                        if (tempchange->getmortgaged())
                        {
                            cout << "You can not trade a mortgaged building" << endl;
                            string continue1;
                            cout << "Press any key to continue" << endl;
                            cout << ">";
                            cin >> continue1;
                            return;
                        }
                    }
                }
                removebuilding(give, players[turn]);
                for (int i=0; i<numplayers; i++) {
                    if (players[i]->getname() == name) {
                        addbuilding(give, players[i]);
                        removebuilding(receive, players[i]);
                        break;
                    }
                }
                addbuilding(receive, players[turn]);
            }
            display->print(cout);
            break;
        }
        else if (temp == "N") {
            cout << "You are refused by player " << name << endl;
            break;
        }
        else {
            cout << "wrong command.";
            cout << "please enter Y/N" << endl;
        }
    }

}

board::board(int numplayers): numplayers(numplayers) {
    rollnum = 0;
    display = new Display();
    int al[6] = {2, 10, 30, 90, 160, 250};
    int ml[6] = {4, 20, 60, 180, 320, 450};
    int ech[6] = {6, 30, 90, 270, 400, 550};
    int pas[6] = {6, 30, 90, 270, 400, 550};
    int hh[6] = {8, 40, 100, 300, 450, 600};
    int rch[6] = {10, 50, 150, 450, 625, 750};
    int dwe[6] = {10, 50, 150, 450, 625, 750};
    int cph[6] = {12, 60, 180, 500, 700, 900};
    int lhi[6] = {14, 70, 200, 550, 750, 950};
    int bmh[6] = {14, 70, 200, 550, 750, 950};
    int opt[6] = {16, 80, 220, 600, 800, 1000};
    int ev1[6] = {18, 90, 250, 700, 875, 1050};
    int ev2[6] = {18, 90, 250, 700, 875, 1050};
    int ev3[6] = {20, 100, 300, 750, 925, 1100};
    int phys[6] = {22, 110, 330, 800, 975, 1150};
    int b1[6] = {22, 110, 330, 800, 975, 1150};
    int b2[6] = {24, 120, 360, 850, 1025, 1200};
    int eit[6] = {26, 130, 390, 900, 1100, 1275};
    int esc[6] = {26, 130, 390, 900, 1100, 1275};
    int c2[6] = {28, 150, 450, 1000, 1200, 1400};
    int mc[6] = { 35, 175, 500, 1100, 1300, 1500};
    int dc[6] = {50, 200, 600, 1400, 1700, 2000};
    
    
    int alm[3] = {1,3,-1};
    int mlm[3] = {1,3,-1};
    int echm[3] = {6,8,9};
    int pasm[3] = {6,8,9};
    int hhm[3] = {6,8,9};
    int rchm[3] = {11,13,14};
    int dwem[3] = {11,13,14};
    int cphm[3] = {11,13,14};
    int lhim[3] = {16,18,19};
    int bmhm[3] = {16,18,19};
    int optm[3] = {16,18,19};
    int ev1m[3] = {21,23,24};
    int ev2m[3] = {21,23,24};
    int ev3m[3] = {21,23,24};
    int physm[3] = {26,27,29};
    int b1m[3] = {26,27,29};
    int b2m[3] = {26,27,29};
    int eitm[3] = {31,32,34};
    int escm[3] = {31,32,34};
    int c2m[3] = {31,32,34};
    int mcm[3] = {37,39,-1};
    int dcm[3] = {37,39,-1};
    
    
    blocks[0] = new osap();
    blocks[1] = new academic("AL", "Arts1", 40, 50, 1, al, this,alm);
    blocks[2] = new slc(2, this);
    blocks[3] = new academic("ML", "Arts1", 60, 50, 3, ml, this,mlm);
    blocks[4] = new tuition();
    blocks[5] = new residences("MKV", 200, 5, this);
    blocks[6] = new academic("ECH", "Arts2", 100, 50, 6, ech,this,echm);
    blocks[7] = new needles(7, this);
    blocks[8] = new academic("PAS", "Arts2", 100, 50, 8, pas,this,pasm);
    blocks[9] = new academic("HH", "Arts2", 120, 50, 9, hh, this,hhm);
    blocks[10] = new dctime(this);
    blocks[11] = new academic("RCH", "Eng", 140, 100, 11, rch, this,rchm);
    blocks[12] = new gym("PAC", 150, 12, this);
    blocks[13] = new academic("DWE", "Eng", 140, 100, 13, dwe, this,dwem);
    blocks[14] = new academic("CPH", "Eng", 160, 100, 14, cph, this,cphm);
    blocks[15] = new residences("UWP", 200, 15, this);
    blocks[16] = new academic("LHI", "Health", 180, 100, 16, lhi, this,lhim);
    blocks[17] = new slc(17, this);
    blocks[18] = new academic("BMH", "Health", 180, 100, 18, bmh, this,bmhm);
    blocks[19] = new academic("OPT", "Health", 200, 100, 19, opt, this,optm);
    blocks[20] = new goose();
    blocks[21] = new academic("EV1", "Env", 220, 150, 21, ev1, this,ev1m);
    blocks[22] = new needles(22, this);
    blocks[23] = new academic("EV2", "Env", 220, 150, 23, ev2, this,ev2m);
    blocks[24] = new academic("EV3", "Env", 240, 150, 24, ev3, this,ev3m);
    blocks[25] = new residences("V1", 200, 25, this);
    blocks[26] = new academic("PHYS", "Sci1", 260, 150, 26, phys, this,physm);
    blocks[27] = new academic("B1", "Sci1", 260, 150, 27, b1, this,b1m);
    blocks[28] = new gym("CIF", 150, 28, this);
    blocks[29] = new academic("B2", "Sci1", 280, 150, 29, b2, this,b2m);
    blocks[30] = new gotodc(this);
    blocks[31] = new academic("EIT", "Sci2", 300, 200, 31, eit, this,eitm);
    blocks[32] = new academic("ESC", "Sci2", 300, 200, 32, esc, this,escm);
    blocks[33] = new slc(33, this);
    blocks[34] = new academic("C2", "Sci2", 320, 200, 34, c2, this,c2m);
    blocks[35] = new residences("REV", 200, 35, this);
    blocks[36] = new needles(36, this);
    blocks[37] = new academic("MC", "Math", 350, 200, 37, mc, this,mcm);
    blocks[38] = new coop();
    blocks[39] = new academic("DC", "Math", 400, 200, 39, dc, this,dcm);
    
    for (int i=0; i<8; i++) {
        players[i] = NULL;
    }
    
    bankrupto = NULL;
    turn = 0;
}

void board::move() {
    bool same = players[turn]->move();

    if(same){
        rollnum += 1;
    }

    if(rollnum == 3){
        cout << "ROLL DOUBLE 3 TIMES!!! SO U NEED TO STAY IN DC TIMS LINE!!!" << endl;
        players[turn]->inrim = true;
        players[turn]->timeinrim = 3;
        players[turn]->setposition(10);
        blocks[10]->addplayer(players[turn]);
        this->display->notify(players[turn]->getpiece(), 10);
        blocks[players[turn]->getPosition()]->action();
        rollnum = 0;
        return;
    }
    
    if (!same)
    {
        rollnum = 0;
    }
    
    blocks[players[turn]->getPosition()]->addplayer(players[turn]);
    blocks[players[turn]->getPosition()]->action();
    
}



void board::movet(int roll1, int roll2) {
    bool same = players[turn]->movet(roll1, roll2);

    if(same){
        rollnum += 1;
    }

    if(rollnum == 3){
        cout << "ROLL DOUBLE 3 TIMES!!! SO U NEED TO STAY IN DC TIMS LINE!!!" << endl;
        players[turn]->inrim = true;
        players[turn]->timeinrim = 3;
        players[turn]->setposition(10);
        blocks[10]->addplayer(players[turn]);
        this->display->notify(players[turn]->getpiece(), 10);
        blocks[players[turn]->getPosition()]->action();
        rollnum = 0;
        return;
    }
    
    if (!same)
    {
        rollnum = 0;
    }
    
    blocks[players[turn]->getPosition()]->addplayer(players[turn]);
    blocks[players[turn]->getPosition()]->action();
    
}

void board::save(string filename){
    ofstream ff;
    ff.open(filename.c_str(),ios::trunc);
    ff << numplayers << endl;

    for (int i = 0; i < numplayers; ++i)
    {
        player* p = players[i];
        string name = p->getname();
        string piece = p->getpiece();
        int timscups = p->getrimcards();
        int money = p->getbalance();
        int position = p->getPosition();
        if (position == 10 )
        {
            ff << name << " " << piece << " " << timscups << " " << money << " " << position << " ";
            if (!p->inrim)
            {
                ff << "0" << endl;
            }
            else{
                int turnsinrim = 3 - p->timeinrim;
                ff << "1" << " "<< turnsinrim << endl;
            }
        }else{
            ff << name << " " << piece << " " << timscups << " " << money << " " << position << " " << endl;
        }
    }
    for (int i = 0; i < 40; ++i)
    {
        building* tempbuild = dynamic_cast<building*>(blocks[i]);
        string buildname;
        string ownername;
        int improvements;
        if (tempbuild != NULL)
        {
            buildname = tempbuild->getname();
            if(tempbuild->getowner() == NULL){
                ownername = "BANK";
            }else{
                ownername = tempbuild->getowner()->getname();
            }

            if (tempbuild->getmortgaged())
            {
                improvements = -1;
            }else{
                academic* tempaca = dynamic_cast<academic*>(tempbuild);
                if (tempaca != NULL)
                {
                    improvements = tempaca->numimp;
                }else{
                    improvements = 0;
                }
            }
            ff << buildname  << " " << ownername << " " << improvements << endl;
        }
    }
}
        
    
board::~board() {
    for (int i=0; i<40; i++) {
        delete blocks[i];
    }
    delete display;
} 
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
