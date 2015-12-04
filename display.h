#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <map>
#include <iostream>
#include <string>
#include <iomanip>


class Display {
protected:
    std::map<std::string, int > player; //first name of player, second position
    std::map<int, std::string> improvemen; //first  position of the building, second number of improvement
    std::map<int, std::string> acaorgym;//first  position of the building second owner
public:
	Display();
	void notify(std::string name, int pos); //player moves notify display
	void notify(int pos, int numofimp, std::string piece); //building changes notify display
	void notifyo(int pos, std::string piece);//notify recidences or gyms

	~Display();
	void print(std::ostream &out);
};

#endif
