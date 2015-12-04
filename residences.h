#ifndef __RESIDENCES_H__
#define __RESIDENCES_H__
#include <string>
#include "building.h"
class board;
class player;
class residences: public building{
public:
	residences(std::string name, int cost, int pos, board *);
	int getcost();
	void tomortgaged();
	void unmortgaged();
	bool getmortgaged();
	int getpay();
	void setowner(player*);
    void changepay();
    void action();
    player* getowner();
    ~residences();
};

#endif
