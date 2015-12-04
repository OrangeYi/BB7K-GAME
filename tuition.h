#ifndef __TUITION_H__
#define __TUITION_H__


#include "block.h"
#include <string>
#include <iostream>


class tuition: public block {
    public:
	tuition();
	void action();
	~tuition();
};

#endif
