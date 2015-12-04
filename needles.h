#ifndef __NEEDLES_H__
#define __NEEDLES_H__


#include "block.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>


class board;

class needles: public block{
	board* boardd;
	public:
		needles(int, board*);
		void action();
		~needles();
};

#endif
