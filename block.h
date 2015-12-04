#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <string>

class Display;
class player;

class block {
	std::string name; //name of this block

	protected:
	Display* display;
	int position; //position of this block
	player *playersOn[8]; //an array sotres the pointer to players who are on the block
    int numplayersOn; //number of players on this block
	

	public:
    player* whosturn; //pointer to the current active player
	block(std::string,int);
    virtual std::string getname();
	virtual void action();
	void addplayer(player *p);
	void deleteplayer(player *p);
    virtual ~block();
    virtual void tomortgaged();
};

#endif
