#include "slc.h"
#include "board.h"
#include "display.h"

using namespace std;

slc::~slc(){}

slc::slc(int pos, class board* boardd):block("SLC", pos), boardd(boardd){}

void slc::action(){
	srand(time(NULL));

	int random = rand()%100 + 1;

	if (random == 1)
	{
		if (boardd->rimcups < 4)
		{
			cout << "Cong! Winning Roll Up the Rim cup. " << endl;
			whosturn->setrimcards(1);
			boardd->rimcups += 1;
			return;
		}
	}

	int prob = rand()%48 + 1;

	if (prob >= 1 && prob <= 6)
	{
        whosturn->move(-3);
		cout << "Back 3" << endl;
	}
	else if (prob >= 7 && prob <= 14)
	{
		whosturn->move(-1);
		cout << "Back 1" << endl;
	}
	else if (prob >= 15 && prob <= 22)
	{
		whosturn->move(-2);
		cout << "Back 2" << endl;
	}
	else if (prob >= 23 && prob <= 28)
	{
        whosturn->move(1);
		cout << "Forward 1" << endl;
	}
	else if (prob >= 28 && prob <= 35)
	{
        whosturn->move(2);
		cout << "Forward 2" << endl;
	}
	else if (prob >= 36 && prob <= 43)
	{
        whosturn->move(3);
		cout << "Forward 3" << endl;
	}
	else if (prob >= 44 && prob <= 45)
	{
		whosturn->setposition(10);
		whosturn->getdisplay()->notify(whosturn->getpiece(), whosturn->getPosition());
		cout << "Go to DC TIMES Line" << endl;
	}
	else {
		whosturn->setposition(0);
		whosturn->getdisplay()->notify(whosturn->getpiece(), whosturn->getPosition());
		cout << "Advance to Collect OSAP" << endl;
	}
	
    boardd->blocks[whosturn->getPosition()]->action();
}


