#ifndef __DCTIME_H__
#define __DCTIME_H__


#include "block.h"

#include <string>
#include <iostream>
class board;

class dctime: public block{
	public:
		class board* boardd;
		dctime(class board* boardd);
		void action();
		~dctime();
};

#endif
