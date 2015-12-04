#include "osap.h"
#include "player.h"
#include <iostream>


using namespace std;


osap::osap():block("osap", 0){}

void osap::action(){
	
	whosturn->setbalance(200);
	cout << "Got $200 from osap!"<< endl;
	string continue1;
    cout << "Press any key to continue" << endl;
    cout << ">";
    cin >> continue1;
}

osap::~osap() {}
