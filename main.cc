#include <unistd.h>
#include <cstdlib>
#include <iostream> 
#include <fstream>
#include "academic.h"
#include "block.h"
#include "board.h"
#include "building.h"
#include "coop.h"
#include "dctime.h"
#include "display.h"
#include "goose.h"
#include "gotodc.h"
#include "gym.h"
#include "needles.h"
#include "osap.h"
#include "player.h"
#include "residences.h"
#include "slc.h"
#include "tuition.h"
using namespace std;

void donghua();
void startgame1();
void startgame2(board* b);
bool load(ifstream& in);

bool test = false;

int main(int argc, char* argv[]) {
    //donghua();
    if(argc <= 1){
        startgame1();
        return 0;
    }

    for(int i = 1; i < argc; i++){
        string arg = argv[i];
        if (arg == "-testing")
        {
            test = true;
        }
    }
    if(argc <= 2){
        startgame1();
        return 0;
    }

    for(int i = 0; i < argc; i++){
        string arg = argv[i];
        if (arg == "-load")
        {
            string filename = argv[i+1];
            ifstream ifs(filename.c_str());
            load(ifs);
        }
    }
}


void startgame1(){
    system("clear");
    cout << "Welcome to BB7K" << endl;
    
    // choose number of players
    cout << "Please enter the number of players. At least two player and at most eight players" << endl;
    int numplayers;
    while (true) {
        cin >> numplayers;
        if (numplayers>=2 && numplayers<=8) break;
        else {
            cout << "Wrong number of players, please enter a number between 2 and 8 inclusively." << endl;
            cin.clear();
            cin.ignore();
        }
    }
    board *b = new board(numplayers);
    system("clear");
    
    // choose name for each player
    string namearr[8] = {"Goose                (G)","GRT Bus              (B)","Tim Hortons Doughnut (D)","Professor            (P)","Student              (S)","Money                ($)","Laptop               (L)","Pink tie             (T)"};
    string symbol = "GBDPS$LT";
    for (int i=0; i<numplayers; i++) {
        string nametemp;
        while(true){
            cout << "Player " << i+1 << " please choose your piece." << endl;
            cout << "Choose one from the following list, enter the command in the bracket:" << endl;
        
            for (int j=0; j<8; j++) {
                cout << namearr[j] << endl;
            }
        
  
            cin >> nametemp;

            if(nametemp != "G" && nametemp != "B" && nametemp != "D" && nametemp != "P" && nametemp != "S" && nametemp != "$" && nametemp != "L" && nametemp != "T"){
                system("clear");
                cout << "\033[31m" << "Please enter the correct piece name (GBDPS$LT)!!!!!!!" << "\33[0m" << endl;
                cout << endl;
                continue;
            }
            else if(symbol.find(nametemp) ==  string::npos){
                system("clear");
                cout << "This piece already picked, please choose other one" << endl;
                continue;
            }
            else{break;}
        }

        char tempnamec = nametemp[0];
        for (int j=0; j<8; j++) {
            if(tempnamec == symbol[j]){
                symbol = symbol.substr(0, j) + " " +symbol.substr(j+1, 8);
            }

            if (namearr[j].substr(22,1) == nametemp) {
                namearr[j] = "                        ";
                break;
            }
        }
        system("clear");
        cout << "player " << i+1 << " please enter your name." << endl;
        string reallyname;
        cin >> reallyname;
        
        player *p = new player(reallyname, nametemp, 1500, 0, b->display);
        b->addPlayer(p);
        system("clear");
    }
    startgame2(b);
}
    
    
void startgame2(board* b){

    for(int i = 0; i < b->numplayers ;++i){
        int position = b->players[i]->getPosition();
        string piece = b->players[i]->getpiece();
        b->display->notify(piece, position);
    }
    

    // play game
    b->display->print(cout);
    string commandarr[11];
    commandarr[0] = "enter (roll) to roll dice";
    commandarr[1] = "enter (next) to give control to next player after roll";
    commandarr[2] = "enter (trade <name> <give> <receive>) to trade with others";
    commandarr[3] = "enter (improve <property> buy/sell) to buy or sell your improvement";
    commandarr[4] = "enter (mortgage <property>) to mortgage the property";
    commandarr[5] = "enter (unmortgage <property>) to unmortgage the property";
    commandarr[6] = "enter (bankrupt) to declare bankruptcy";
    commandarr[7] = "enter (assets) to display assets";
    commandarr[8] = "enter (save <filename>) to save the current state of the game to that file";
    commandarr[9] = "enter (quit) to end the game";
    commandarr[10] = "enter (players) to print all player name and their piece.";

    while (true) {
        cout << (b->players[b->turn])->getname() << "'s turn" << endl;
        for (int i=0; i<40; i++) {
            b->blocks[i]->whosturn = b->players[b->turn];
        }

        cout << "You can enter your command or (?) to get the list of commands" << endl;
        cout << ">";
        string cmdtemp;
        cin >> cmdtemp;
        if (cmdtemp == "?") {
            cout << "Here is the list of commands:" << endl;
            cout << endl;
            for (int i=0; i<11; i++) {
                cout << commandarr[i] << endl;
            }
        } 
        else if (cmdtemp == "roll") {
            if (b->players[b->turn]->getbalance() < 0) {
                cout << "Negative balance.You cannot roll" << endl;
                cout << "You can choose bankrupt or sell assets" << endl;
                continue;
            }


            if(b->players[b->turn]->inrim){
                b->blocks[10]->action();
            }
            else if(test && b->players[b->turn]->canmove){
                int rolltest1;
                int rolltest2;
                cin >> rolltest1;
                cin >> rolltest2;
                b->movet(rolltest1,rolltest2);
                b->display->print(cout);
            }
            else if (b->players[b->turn]->canmove) {
                b->move();
                b->display->print(cout);
            } else {
                cout << "You have moved already" << endl;
            }
        } else if (cmdtemp == "players") {
            for (int i=0; i<b->numplayers; i++) {
                cout << "Name: " << b->players[i]->getname();
                cout << " Piece: " << b->players[i]->getpiece() << endl;
            }
            cout << endl;
        }
        else if (cmdtemp == "next") {
            if (b->players[b->turn]->getbalance() < 0) {
                cout << "Negative balance. You cant give next turn." << endl;
                cout << "You can choose bankrupt or sell assets" << endl;
                continue;
            }

            if(b->players[b->turn]->canmove){
                cout << "You still have chance to roll, don't waste it~" << endl;
                cout << endl;
            }
            else{
                b->turn = b->turn+1;
                if (b->turn == b->numplayers) b->turn=0;
                b->players[b->turn]->canmove = true;
            }
        } else if (cmdtemp == "quit") {
            cout << "Game end" << endl;
            delete b;
            for (int i=0; i<b->numplayers; i++) {
                delete b->players[i];
            }
            return;
        } else if (cmdtemp == "trade") {
            string checkname = "";
            string checkbuilding = "";
            string name;
            string give;
            string receive;
            cin >> name >> give >> receive;
            for (int i = 0; i < b->numplayers; ++i)
            {
                if(name == b->players[i]->getname()){
                    checkname = name;
                }
            }
            for (int i = 0; i < 40; ++i)
            {
                if(b->blocks[i]->getname() == give || b->blocks[i]->getname() == receive){
                    checkbuilding = b->blocks[i]->getname();
                }
            }
            if (checkname == ""){
                cout << "\033[31m" << "Enter a wrong players name please try again!" << "\033[0m" << endl;
                cout << "please enter anything to continue" << endl;
                cout << "> ";
                cin >> checkname;
                continue;
            }
            if (checkbuilding == ""){
                cout << "\033[31m" << "Enter a wrong building's name please try again!" << "\033[0m" << endl;
                cout << "please enter anything to continue" << endl;
                cout << "> ";
                cin >> checkname;
                continue;
            }

            b->trade(name, give, receive);
        } else if (cmdtemp == "improve") {
            string name;
            string cmd;
            cin >> name >> cmd;
            b->players[b->turn]->improve(name, cmd);
            b->display->print(cout);
        } else if (cmdtemp == "mortgage") {
            string name;
            cin >> name;
            b->players[b->turn]->tomortgage(name);
        } else if (cmdtemp == "unmortgage") {
            string name;
            cin >> name;
            b->players[b->turn]->unmortgage(name);
        } else if (cmdtemp == "bankrupt") {
            if (b->players[b->turn]->getbalance() < 0) {
                b->bankrupt();
            } else {
                cout << "You cant decalare bankruptcy now, please enter another command." << endl;
                cout << endl;
            }
        } else if (cmdtemp == "assets") {
            b->players[b->turn]->assets();
        } else if (cmdtemp == "save"){
            string filename;
            if(cin >> filename){
                b->save(filename);
                cout <<"GAME SAVED!!" << endl;
            }else{
                cout << "Please enter a file name after save command" << endl;
            }
        }
        else {
            system("clear");
            b->display->print(cout);
            cout << "Wrong command, please try again. Enter (?) for help." << endl;
            cout << endl;
        }
        if (b->numplayers <= 1) {
            cout << "Game Over" << endl;
            cout << "Player " << b->players[0]->getname() << " wins" << endl;
            break;
        }       
    }
}


bool load(ifstream &in){

    int numofplayers;
    in >> numofplayers;
    board *b = new board(numofplayers);
    std::map<std::string, player*> nameandpoint;

    int dcturn = 0;
    int totaltimcups = 0;
    string name, piece;
    int cups,momey,position;
    for (int i = 0; i < numofplayers; ++i)
    {
        in >> name;
        in >> piece;
        in >> cups;
        in >> momey;
        in >> position;
        totaltimcups += cups;

        if(position == 30 || position < 0 || position > 39){
            cout << "Invalid position entered for " << name << endl;
            return false;
        }

        else if(position == 10){
            in >> dcturn;
        }

        player *p = new player(name, piece, momey, position, b->display);
        p->setrimcards(cups);
        p->timeinrim = dcturn;
        if(p->timeinrim != 0){
            in >> dcturn;
            p->inrim = true;
            p->timeinrim = 3 - dcturn;
            p->canmove = true;
        }
        nameandpoint[name] = p;
        b->addPlayer(p);
        b->display->notify(piece, position);
    }

    if(totaltimcups > 4){
        cout << "Invalid number of cups, maximum cups is 4" << endl;
        return false;
    }

    string buildname;
    string owner;
    int numimp;

    while(in >> buildname){
        block * tempbuild;
        int nametime = 0;
        for (int i = 0; i < 40; ++i)
        {
            if(buildname == b->blocks[i]->getname()){
                tempbuild = b->blocks[i];
                nametime += 1;
                break;
            }
        }
        if(nametime == 0){
            cout << "Invalid name of building for " << buildname << endl;
            return false;
        }


        in >> owner;
        in >> numimp;

        if(owner == "BANK"){
            if(numimp == -1){
                tempbuild->tomortgaged();
            }
            continue;
        }

        player* p = nameandpoint[owner];

        building* tempsetowner = dynamic_cast<building*>(tempbuild);
        tempsetowner->setowner(p);

        academic* tempaca = dynamic_cast<academic*>(tempbuild);

        if(numimp == -1){
            tempbuild->tomortgaged();
        }
        else if(tempaca != NULL){
            tempaca->numimp = numimp;
            b->addbuilding(buildname, p);
            b->display->notify(tempsetowner->getPosition(), numimp, p->getpiece());
            continue;
        }
        
        b->addbuilding(buildname, p);

        if(numimp == -1){
            p->tomortgage(buildname);//it is to nitify display
        }
    }
    startgame2(b);
    return true;
}











void donghua()
{
    srand(time(NULL));
    for(int i=1; i<=1; i++)
    {
        
        if(i%2==0)
            
            system("clear");
       	cout << "loding" << endl;
        cout<<"■□□□□□□□□□"<<endl;
        usleep(150000);
        system("clear");
        
        cout << "_________________________________________" << endl;
        cout << "loding." << endl;
        cout<<"■■□□□□□□□□"<<endl;
        usleep(150000);
        system("clear");
        
        cout << "_________________________________________" << endl;
        cout << "|                                       |" << endl;
        cout << "loding.." << endl;
        cout<<"■■■□□□□□□□"<<endl;
        usleep(150000);
        system("clear");
        
        cout << "_________________________________________" << endl;
        cout << "|                                       |" << endl;
        cout << "|  ###   ###   #####  ###   ###   ###   |" << endl;
        cout << "loding..." << endl;
        cout<<"■■■■□□□□□□"<<endl;
        usleep(150000);
        system("clear");
        
        cout << "_________________________________________" << endl;
        cout << "|                                       |" << endl;
        cout << "|  ###   ###   #####  ###   ###   ###   |" << endl;
        cout << "|  #  #  #  #     #  #   # #   # #   #  |" << endl;
        cout << "loding...." << endl;
        cout<<"■■■■■□□□□□"<<endl;
        usleep(150000);
        system("clear");
        
        cout << "_________________________________________" << endl;
        cout << "|                                       |" << endl;
        cout << "|  ###   ###   #####  ###   ###   ###   |" << endl;
        cout << "|  #  #  #  #     #  #   # #   # #   #  |" << endl;
        cout << "|  ####  ####    #   #   # #   # #   #  |" << endl;
        cout << "loding" << endl;
        cout<<"■■■■■■□□□□"<<endl;
        usleep(150000);
        system("clear");
        
        cout << "_________________________________________" << endl;
        cout << "|                                       |" << endl;
        cout << "|  ###   ###   #####  ###   ###   ###   |" << endl;
        cout << "|  #  #  #  #     #  #   # #   # #   #  |" << endl;
        cout << "|  ####  ####    #   #   # #   # #   #  |" << endl;
        cout << "|  #   # #   #  #    #   # #   # #   #  |" << endl;
        cout << "loding." << endl;
        cout<<"■■■■■■■□□□"<<endl;
        usleep(150000);
        system("clear");
        
        cout << "_________________________________________" << endl;
        cout << "|                                       |" << endl;
        cout << "|  ###   ###   #####  ###   ###   ###   |" << endl;
        cout << "|  #  #  #  #     #  #   # #   # #   #  |" << endl;
        cout << "|  ####  ####    #   #   # #   # #   #  |" << endl;
        cout << "|  #   # #   #  #    #   # #   # #   #  |" << endl;
        cout << "|  ####  ####  #      ###   ###   ###   |" << endl;
        cout << "loding.." << endl;
        cout<<"■■■■■■■■□□"<<endl;
        usleep(150000);
        system("clear");
        
        cout << "_________________________________________" << endl;
        cout << "|                                       |" << endl;
        cout << "|  ###   ###   #####  ###   ###   ###   |" << endl;
        cout << "|  #  #  #  #     #  #   # #   # #   #  |" << endl;
        cout << "|  ####  ####    #   #   # #   # #   #  |" << endl;
        cout << "|  #   # #   #  #    #   # #   # #   #  |" << endl;
        cout << "|  ####  ####  #      ###   ###   ###   |" << endl;
        cout << "|_______________________________________|" << endl;
        cout << "loding..." << endl;
        cout<<"■■■■■■■■■□"<<endl;
        usleep(150000);
        system("clear");
        
        cout << "_________________________________________" << endl;
        cout << "|                                       |" << endl;
        cout << "|  ###   ###   #####  ###   ###   ###   |" << endl;
        cout << "|  #  #  #  #     #  #   # #   # #   #  |" << endl;
        cout << "|  ####  ####    #   #   # #   # #   #  |" << endl;
        cout << "|  #   # #   #  #    #   # #   # #   #  |" << endl;
        cout << "|  ####  ####  #      ###   ###   ###   |" << endl;
        cout << "|_______________________________________|" << endl;
        cout << "          ";
        cout << "ZIYI CHEN & QIUYU LUO" << endl;
        cout << "loding...." << endl;
        cout<<"■■■■■■■■■■"<<endl;
        usleep(2000000);
        system("clear");   
    } 
}












