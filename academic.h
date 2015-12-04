#ifndef __ACADEMIC_H__
#define __ACADEMIC_H__


#include "building.h"
class board;
class player;

class academic: public building{
public:
	int impcost; //cost for improvement
	int numimp; // current improvment level
    int tuition[6]; // an array stores the different money should pay in different improvement level
    int Monopoly[3]; //an array stores the whether the monoply belongs to one owner
    std::string monopolyblock; //which monoplyblock this building belongs to
    
    
	academic(std::string, std::string, int, int, int, int [],board *, int []);
    void improve(std::string cmd);
	int getcost();
	void tomortgaged();
	void unmortgaged();
	bool getmortgaged();
	int getpay();
	void changepay();
	void setowner(player*);
    void action();
    player* getowner();
    int getPosition();
    ~academic();
};

#endif
