#include "block.h"


using namespace std;


block::block(string name, int position):name(name), position(position){
    for (int i=0; i<8; i++) {
        playersOn[i] = NULL;
    }
    numplayersOn = 0;
    whosturn = NULL;
    }

void block::addplayer(player *p) {
    playersOn[numplayersOn] = p;
    numplayersOn++;
}

string block::getname() {
    return name;
}

void block::deleteplayer(player *p) {
    int i=0;
    while (i<numplayersOn) {
        if (playersOn[i] == p) {
            playersOn[i] = NULL;
            break;
        }
        i++;
    }
    while (i<numplayersOn) {
        playersOn[i] = playersOn[i+1];
        i++;
    }
    
}



//void block::notify() {}

block::~block() {}


void block::action(){}

void block::tomortgaged(){}
