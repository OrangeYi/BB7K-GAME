#ifndef __BOARD_H__
#define __BOARD_H__

#include <iostream>
class Display;
class block;
class player;
class building;
class needles;
class slc;


class board {
    public:
    int rollnum; //how many times the player has consecutively roll
    block* blocks[40]; //an array of pointers to 40 blocks
    int numplayers; //number of player playing this game
    player *players[8]; //an array of pointer to player who are playing the game
    int turn; //whose turn now
    int rimcups; //how many rim cups all the players have
    Display *display;
    player* bankrupto; //person who bankrupt to


    player* whoseTurn();
    void addPlayer(player *p);
    void removePlayer(player *p);
    board(int numplayers);
    int getturn();
    void trade(std::string name, std::string give, std::string receive);
    void bankrupt();
    void addbuilding(std::string name, player * who);
    void removebuilding(std::string name, player * who);
    void auction(building *b);
    void move();
    void movet(int roll1 ,int roll2);
    void save(std::string filename);
    ~board();
};

#endif
