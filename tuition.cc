#include "tuition.h"
#include "player.h"
#include <string>
using namespace std;

tuition::tuition():block("TUITION", 4){}

tuition::~tuition() {}

void tuition::action(){
	cout << "Choose to pay $300 tuition(T) or to pay 10% of your total worth(P): (T OR P) "<< endl;
	string tem;
	while(cin >> tem){

		if (tem == "P")
		{
			int totalmoney = 0;
			totalmoney = whosturn->gettotalAsset();
			totalmoney = totalmoney * 0.1;
			cout << "Pay $" << totalmoney << endl;
			whosturn->setbalance(- totalmoney);
			string continue1;
        	cout << "Press any key to continue" << endl;
        	cout << ">";
        	cin >> continue1;
			break;
		}
		else if (tem == "T")
		{
			cout << "Pay $300 tuition fee" << endl;
			whosturn->setbalance(- 300);
			string continue1;
        	cout << "Press any key to continue" << endl;
        	cout << ">";
        	cin >> continue1;
			break;
		}
		
		else{ cout << "Please enter the corect command (T OR P)" << endl;
        }
    }
}
