#ifndef __GYM_H__
#define __GYM_H__

#include "building.h"
#include <string>
class board;

class gym: public building{
public:
	gym(std::string name, int cost, int pos, board* b);
	int getcost();
	void tomortgaged();
	void unmortgaged();
	bool getmortgaged();
	player* getowner();
	int getpay();
    void changepay();
    void setowner(player *);
    void action();
    ~gym();
};

#endif
