#include "needles.h"
#include "player.h"
#include <iostream>
#include <string>
#include "board.h"



using namespace std;

needles::needles(int pos, class board* boardd):block("Needles Hall", pos), boardd(boardd){}

needles::~needles() {}

void needles::action(){
	srand(time(NULL));

	int random = rand()%100;

	if (random == 1)
	{
		if (boardd->rimcups < 4)
		{
			cout << "Cong! Winning Roll Up the Rim cup. " << endl;
			whosturn->setrimcards(1);
			boardd->rimcups += 1;
			string continue1;
        	cout << "Press any key to continue" << endl;
        	cout << ">";
        	cin >> continue1;
			return;
		}
	}


	int prob = rand()%36;

	if(prob >= 1 && prob <= 2){
		whosturn->setbalance( - 200);
		cout << "Lose $200" << endl;
	}
	else if (prob >= 3 && prob <= 4) {
		whosturn->setbalance( 200);
		cout << "Get $200" << endl;
	}
	else if (prob >= 5 && prob <= 8) {
		whosturn->setbalance( - 100);
		cout << "Lose $100" << endl;
	}
	else if (prob >= 9 && prob <= 12) {
		whosturn->setbalance( 100);
		cout << "Get $100" << endl;
	}
	else if (prob >= 13 && prob <= 18) {
		whosturn->setbalance( - 50);
		cout << "Lose $50" << endl;
	}
	else if (prob >= 19 && prob <= 24) {
		whosturn->setbalance( 50);
		cout << "Get $50" << endl;
	}
	else {
		whosturn->setbalance( 25);
		cout << "Get $25" << endl;
	}

	string continue1;
    cout << "Press any key to continue" << endl;
    cout << ">";
    cin >> continue1;
}


