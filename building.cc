#include "building.h"
#include "board.h"
#include "player.h"

using namespace std;

building::building(string name, int pos, board* boar):block(name, pos), b(boar){}
void building::tomortgaged(){}
void building::unmortgaged(){}
bool building::getmortgaged(){ return mortgaged;}
int building::getpay(){ return pay;}
void building::changepay(){}
void building::setowner(player *){}
int building::getcost(){return cost;}
void building::action() {}
int building::getPosition(){return position;}
player* building::getowner(){return owner;}
building::~building() {}
    
