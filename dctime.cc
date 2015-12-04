#include "dctime.h"
#include "player.h"
#include "board.h"
#include <cstdlib>
#include <ctime>
using namespace std;


dctime::dctime(class board* boardd):block("Dc Times Line", 10), boardd(boardd){}

dctime::~dctime(){}

void dctime::action(){

	string continue1;

	if (whosturn->inrim)
	{		
		if(!whosturn->canmove){
			cout << "You are in DC Time Line, can not roll again" << endl;
			cout << "Press any key to continue" << endl;
			cout << ">";
			cin >> continue1;
			return;
		}

		whosturn->canmove = false;
		whosturn->timeinrim -= 1;

		if (whosturn->timeinrim == 2){
			cout << "You are in Dc Time Line right now, you may move next turn. Good luck!" << endl;
			cout << "Press any key to continue" << endl;
			cout << ">";
			cin >> continue1;
			whosturn->canmove = false;

			return;
		}
		else if(whosturn->timeinrim == 1){//second in dc time

			if (whosturn->getrimcards() > 0){//have rim cards
				cout << "You have a Roll Up the Rim cup, do you want to use it(y/n)" << endl;
				string answer;
				cin >> answer;

				if (answer == "Y" || answer == "y"){
					cout << "Using Roll Up the Rim cup, you can leave now!" << endl;
					whosturn->inrim = false;
					whosturn->canmove = true;
					whosturn->timeinrim = 0;
					return;
			   	}
			}

			cout << "You are in Dc Time Line right now, please choose pay 50$(P) to leave or roll(R) a double to leave(P/R)" << endl;
			string answer;
			cin >> answer;
			if(answer == "p" || answer == "P"){//pay 50
				cout << "You pay $50, you can leave now. ROLL!!" << endl;
				whosturn->setbalance(-50);
				whosturn->inrim = false;
				whosturn->canmove = true; 
				whosturn->timeinrim = 0;
				return;
			}
			else if(answer == "R" || answer == "r"){//roll
				cout << "You choose to roll, good luck!" << endl;
				srand(time(NULL));
        		int move1 = rand()%6 + 1;
        		int move2 = rand()%6 + 1;
        		cout << move1 << " : " << move2 << " rolls " << move1+move2 << endl;
        		if (move1 == move2){//double
        			cout << "DOUBLE!!!! You can leave now!" << endl;
        			whosturn->setposition((whosturn->getPosition() + move1 + move2)%40);
        			boardd->blocks[this->whosturn->getPosition()]->whosturn = this->whosturn;
					boardd->blocks[this->whosturn->getPosition()]->action();
					this->whosturn = NULL;
					cout << "Press any key to continue" << endl;
					cout << ">";
					cin >> continue1;
					return;
        		}
        		else{
        			cout << "It is not a double. Sorry you can not leave" << endl;
        			cout << "Press any key to continue" << endl;
					cout << ">";
					cin >> continue1;
        		}
			}

		}
		else if (whosturn->timeinrim == 0){
			if (whosturn->getrimcards() > 0){//have rim cards
				cout << "You have a Roll Up the Rim cup, do you want to use it(y/n)" << endl;
				string answer;
				cin >> answer;

				if (answer == "Y" || answer == "y"){
					cout << "Using Roll Up the Rim cup, you can leave now!" << endl;
					whosturn->inrim = 0;
					whosturn->canmove = true;
					cout << "Press any key to continue" << endl;
					cout << ">";
					cin >> continue1;
					return;
			   	}
			}
			if (true){
				cout << "You mush pay $50 to leave!!" << endl;
				cout << "Pay $50" << endl;
				whosturn->setbalance(-50);
				whosturn->inrim = false;
				whosturn->canmove = true; 
				whosturn->timeinrim = 0;
				cout << "Press any key to continue" << endl;
				cout << ">";
				cin >> continue1;
				return;
			}
		}
	}
	else {
		cout << "Welcome to DC" << endl;
		cout << "Press any key to continue" << endl;
		cout << ">";
		cin >> continue1;}
}
