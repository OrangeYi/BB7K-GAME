#include "gotodc.h"
#include "board.h"
#include "display.h"
using namespace std;


gotodc::gotodc(board* boardd):block("GO TO TIMES", 30),boardd(boardd){}

gotodc::~gotodc(){}

void gotodc::action(){
	whosturn->timeinrim = 3;
	whosturn->setposition(10);
	whosturn->inrim = true;
	whosturn->canmove = true;

	whosturn->getdisplay()->notify(whosturn->getpiece(), whosturn->getPosition());

	boardd->blocks[10]->whosturn = this->whosturn;
	this->whosturn = NULL;
	boardd->blocks[10]->action();
}
