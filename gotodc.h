#ifndef __GOTODC_H__
#define __GOTODC_H__


#include "block.h"
#include "player.h"

class gotodc: public block{
	public:
		board* boardd;
		gotodc(board* boardd);
		void action();
		~gotodc();
};

#endif
