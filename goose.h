#ifndef __GOOSE_H__
#define __GOOSE_H__

#include "block.h"

class goose: public block {
    public:
    goose();
    void action();
    ~goose();
};
#endif
