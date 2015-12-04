#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>
//#include "display.h"
#include "building.h"
#include "academic.h"
#include "residences.h"
#include "gym.h"

class Display;

class player {
    const std::string name;//reallyname
    const std::string piece;//piece
    int balance; //money player has
    int rimcards;//rim cards player has
    int position;//position of the player
    int totalAsset;//total worth the player has
    Display *display;
    

    
public:
    int gymnum; //number of owned gym
    int resnum; //number of owned residences
    int acanum; //number of owned academic
    int intimnum; // total building
    bool inrim;//is it in rim
    int timeinrim; //how many turn the player has been in tim
    bool canmove; //can the player move
    building *buildings[40]; //pointers to buildings the player own
    
    
    
    
    Display* getdisplay();
    player(std::string name, std::string reallyname, int bal, int pos, Display* dis);
    ~player();
    std::string getname();
    std::string getpiece();
    int getbalance();
    int gettotalAsset();
    int getrimcards();
    int getPosition();
    void addbuilding(class building * b);
    void removebuilding(class building * b);
    void setposition(int pos);
    void setrimcards(int rc);
    void setbalance(int change);
    void settotalAsset(int change);
    void move(int mo);
    bool move();
    void getOuttims();
    void improve(std::string name, std::string cmd);
    void tomortgage(std::string name);
    void unmortgage(std::string name);
    void allunmortgage();
    void assets();
    bool movet(int roll1, int roll2);
    

    
};

#endif
