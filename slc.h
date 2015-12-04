#ifndef __SLC_H__
#define __SLC_H__


#include "block.h"
#include "player.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

class board;

class slc: public block{
	board* boardd;
	public:
		slc(int,board*);
		void action();
		~slc();
};

#endif
