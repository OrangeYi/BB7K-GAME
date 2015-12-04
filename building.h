#ifndef __BUILDING_H__
#define __BUILDING_H__

#include <string>
#include "block.h"

class player;
class board;

class building: public block{
	protected:
		int cost; //money needed to buy this building
		bool mortgaged; //whether this building is mortgaged
		player* owner; //the owner of this building
		int pay; //the money should pay when other players land on this building
   
	public:
    	board *b;
    
		building(std::string, int, board*);
		virtual int getPosition();
		virtual int getcost();
		virtual void tomortgaged();
		virtual void unmortgaged();
		virtual bool getmortgaged();
		virtual int getpay();
		virtual void changepay();
		virtual void setowner(player *);
		virtual player* getowner();
     	void action();
     	~building();
    
    
};

#endif
