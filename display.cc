#include "display.h"


using namespace std;


Display::Display(){
	acaorgym[5] = " ";
	acaorgym[12] = " ";
	acaorgym[15] = " ";
	acaorgym[25] = " ";
	acaorgym[28] = " ";
	acaorgym[35] = " ";
}

Display::~Display() {}

void Display::notify(string name, int pos){
	player[name] = pos;
}

void Display::notify(int pos, int numofimp, std::string piece){
	if (numofimp > 0)
	{
		improvemen[pos] = piece + " ";
		for (int i = 0; i < numofimp; ++i)
		{
			improvemen[pos] += "I"; 
		}
	}
	else if (numofimp < 0)
	{
		int len = improvemen[pos].length();
		improvemen[pos] = improvemen[pos].substr(0, len + numofimp);
	}
	else{
		improvemen[pos] = piece + " ";
	}
}

void Display::notifyo(int pos, std::string piece){
	acaorgym[pos] = piece;
}

void Display::print(std::ostream &out){
	map<int , string> playernow;//first pos of building, second name of player


    string mkvo = acaorgym[5];
    string paco = acaorgym[12];
    string uwpo = acaorgym[15];
    string v1o = acaorgym[25];
    string cifo = acaorgym[28];
    string revo = acaorgym[35];



 	string ev1i = improvemen[21];
	string ev2i = improvemen[23];
	string ev3i = improvemen[24];
	string physi = improvemen[26];
	string b1i = improvemen[27];
	string b2i = improvemen[29];
	string opti = improvemen[19];
	string eiti = improvemen[31];
	string bmhi = improvemen[18];
	string esci = improvemen[32];
	string lhii = improvemen[16];
	string c2i = improvemen[34];
	string cphi = improvemen[14];
	string dwei = improvemen[13];
	string mci = improvemen[37];
	string rchi = improvemen[11];
	string dci = improvemen[39];
	string hhi = improvemen[9];
	string pasi = improvemen[8];
	string echi = improvemen[6];
	string mli = improvemen[3];
	string ali = improvemen[1];


	for (int i = 0; i < 40; ++i)
	{
		playernow[i] = "";
	}

	for(map<string, int>::iterator i = player.begin(); i != player.end(); ++i){
		int pos = i->second;
		playernow[pos] += i->first;
	}

	string osapp = playernow[0];
	string alp = playernow[1];
	string slcdp = playernow[2];
	string mlp = playernow[3];
	string tuitionp = playernow[4];
	string mkvp = playernow[5];
	string echp = playernow[6];
	string needlesdp = playernow[7];
	string pasp = playernow[8];
	string hhp = playernow[9];
	string dctimesp = playernow[10];
	string rchp = playernow[11];
	string pacp = playernow[12];
	string dwep = playernow[13];
	string cphp = playernow[14];
	string uwpp = playernow[15];
	string lhip = playernow[16];
	string slclp = playernow[17];
	string bmhp = playernow[18];
	string optp = playernow[19];
	string goosep = playernow[20];
	string ev1p = playernow[21];
	string needlesup = playernow[22];
	string ev2p = playernow[23];
	string ev3p = playernow[24];
	string v1p = playernow[25];
	string physp = playernow[26];
	string b1p = playernow[27];
	string cifp = playernow[28];
	string b2p = playernow[29];
	string gotop = playernow[30];
	string eitp = playernow[31];
	string escp = playernow[32];
	string slcrp = playernow[33];
	string c2p = playernow[34];
	string revp = playernow[35];
	string needlesrp = playernow[36];
	string mcp = playernow[37];
	string coopp = playernow[38];
	string dcp = playernow[39];


    //first row
	out << "____________________________________________________________________________________________________" << endl;

	//second row
	out << '|' << left << setw(8) << "Goose" << '|';
	out << "\033[43m"<< setw(12) << setfill(' ') << right << ev1i + "\33[0m";
	out << '|' << left << setw(8) << "NEEDLES" << '|';
	out << "\033[43m"<< setw(12) << setfill(' ') << right << ev2i + "\33[0m" << "|";
	out << "\033[43m"<< setw(12) << setfill(' ') << right << ev3i + "\33[0m" << "|";
	out << left << setw(8) << setfill(' ') << "V1 " + v1o <<'|';
 	out << "\033[44m"<< setw(12) << setfill(' ') << right << physi + "\33[0m" << "|";
	out << "\033[44m"<< setw(12) << setfill(' ') << right << b1i + "\33[0m" << "|";
	out << left << setw(8) << setfill(' ') << "CIF " + cifo << '|';
	out << "\033[44m"<< setw(12) << setfill(' ') << right << b2i + "\33[0m";
	out << '|' << left << setw(8) << "GO TO" << '|';
	out << endl;

	//third row
	out << '|' << left << setw(8) << "Nesting" << '|';
	out << left << setw(8) << "--------";
	out << '|' << left << setw(8) << "HALL" << '|';
	out << left << setw(8) << "--------" << '|';
	out << left << setw(8) << "--------" << '|';
	out << left << setw(8) << "        " << '|';
	out << left << setw(8) << "--------" << '|';
	out << left << setw(8) << "--------" << '|';
	out << left << setw(8) << "        " << '|';
	out << left << setw(8) << "--------" << '|';
	out << left << setw(8) << "TIMES" << '|';
	out << endl;

	//fouth row
	out << "|" << left << setw(8) << "        ";
	out << "|" << left << setw(8) << "EV1";
	out << "|" << left << setw(8) << "        ";
	out << "|" << left << setw(8) << "EV2";
	out << "|" << left << setw(8) << "EV3";
	out << "|" << left << setw(8) << "        ";
	out << "|" << left << setw(8) << "PHYS";
	out << "|" << left << setw(8) << "B1";
	out << "|" << left << setw(8) << "        ";
	out << "|" << left << setw(8) << "B2";
	out << "|" << left << setw(8) << "        " << "|";
	out << endl;

	//fivth row
	out << "|" << right << setw(8) << goosep;
	out << "|" << right << setw(8) << ev1p;
	out << "|" << right << setw(8) << needlesup;
	out << "|" << right << setw(8) << ev2p;
	out << "|" << right << setw(8) << ev3p;
	out << "|" << right << setw(8) << v1p;
	out << "|" << right << setw(8) << physp;
	out << "|" << right << setw(8) << b1p;
	out << "|" << right << setw(8) << cifp;
	out << "|" << right << setw(8) << b2p;
	out << "|" << right << setw(8) << gotop << "|";
	out << endl;

	//sixth
	out << "|" << "________";
	out << "|" << "________";
	out << "|" << "________";
	out << "|" << "________";
	out << "|" << "________";
	out << "|" << "________";
	out << "|" << "________";
	out << "|" << "________";
	out << "|" << "________";
	out << "|" << "________";
	out << "|" << "________" << "|";
	out << endl;

	//seven
	out << "|" << "\033[42m"<< setw(12) << setfill(' ') << right << opti + "\33[0m";
	out << "|" << setfill(' ') << setw(81);
	out << "|" << "\033[41m"<< setw(12) << setfill(' ') << right << eiti + "\33[0m" << "|";
	out << endl;

	//eight
	out << "|" << "--------";
	out << "|" << setfill(' ') << setw(81);
	out << "|" << "--------" << "|";
	out << endl;

	//nine
	out << "|" << "OPT     ";
	out << "|" << setfill(' ') << setw(81);
	out << "|" << "EIT     " << "|";
	out << endl;

	//ten
	out << "|" << setfill(' ') << setw(8) << optp;
	out << "|" << setfill(' ') << setw(81);
	out << "|" << setfill(' ') << setw(8) << eitp << "|";
	out << endl;

	//11
	out << "|" << "________";
	out << "|" << setfill(' ') << setw(81);
	out << "|" << "________" << "|";
	out << endl;

	//12
	out << "|" << "\033[42m"<< setw(12) << setfill(' ') << right << bmhi + "\33[0m";
	out << "|" << setfill(' ') << setw(81);
	out << "|" << "\033[41m"<< setw(12) << setfill(' ') << right << esci + "\33[0m" << "|";
	out << endl;

	//13
	out << "|" << "--------";
	out << "|" << setfill(' ') << setw(81);
	out << "|" << "--------" << "|";
	out << endl;

	//14
	out << "|" << "BMH     ";
	out << "|" << setfill(' ') << setw(81);
	out << "|" << "ESC     " << "|";
	out << endl;

	//15
	out << "|" << setfill(' ') << setw(8) << bmhp;
	out << "|" << setfill(' ') << setw(81);
	out << "|" << setfill(' ') << setw(8) << escp << "|";
	out << endl;

	//16
	out << "|" << "________";
	out << "|" << setfill(' ') << setw(81);
	out << "|" << "________" << "|";
	out << endl;

	//17 slc
	out << "|" << "SLC     ";
	out << "|" << setfill(' ') << setw(81);
	out << "|" << "SLC     " << "|";
	out << endl;

	//18
	out << "|" << setfill(' ') << setw(9);
	out << "|" << setfill(' ') << setw(81);
	out << "|" << setfill(' ') << setw(9) << "|";
	out << endl;

	//19
	out << "|" << setfill(' ') << setw(9);
	out << "|" << setfill(' ') << setw(81);
	out << "|" << setfill(' ') << setw(9) << "|";
	out << endl;

	//20
	out << "|" << setfill(' ') << setw(8) << slclp;
	out << "|" << setfill(' ') << setw(81);
	out << "|" << setfill(' ') << setw(8) << slcrp << "|";
	out << endl;

	//21
	out << "|" << "________";
	out << "|" << setfill(' ') << setw(81);
	out << "|" << "________" << "|";
	out << endl;

	//22
	out << "|" << "\033[42m"<< setw(12) << setfill(' ') << right << lhii + "\33[0m";
	out << "|" << setfill(' ') << setw(81);
	out << "|" << "\033[41m"<< setw(12) << setfill(' ') << right << c2i + "\33[0m" << "|";
	out << endl;

	//23
	out << "|" << "--------";
	out << "|" << setfill(' ') << setw(81);
	out << "|" << "--------" << "|";
	out << endl;

	//24
	out << "|" << "LHI     ";
	out << "|" << setfill(' ') << setw(81);
	out << "|" << "C2      " << "|";
	out << endl;

	//25
	out << "|" << setfill(' ') << setw(8) << lhip;
	out << "|" << setfill(' ') << setw(61);
	out << "_________________________________________";
	out << setfill(' ') << setw(20);
	out << "|" << setfill(' ') << setw(8) << c2p << "|";
	out << endl;

	//26
	out << "|" << "________";
	out << "|" << setfill(' ') << setw(61);
	out << "|                                       |";
	out << setfill(' ') << setw(20);
	out << "|" << "________" << "|";
	out << endl;

	//27
	out << "|" << left << setw(8) << setfill(' ')<< "UWP " + uwpo << "|";
	out << "                    ";
	out << "|  ###   ###   #####  ###   ###   ###   |";
	out << "                   ";
	out << "|" << left << setw(8) << setfill(' ') << "REV " + revo << "|";
	out << endl;

	//28
	out << "|" << "        |";
	out << "                    ";
	out << "|  #  #  #  #     #  #   # #   # #   #  |";
	out << "                   ";
	out << "|" << "        " << "|";
	out << endl;

	//29
	out << "|" << "        |";
	out << "                    ";
	out << "|  ####  ####    #   #   # #   # #   #  |";
	out << "                   ";
	out << "|" << "        " << "|";
	out << endl;

	//30
	out << "|" << right << setw(8) << setfill(' ') << uwpp;
	out << "|" << setfill(' ') << setw(61);
	out << "|  #   # #   #  #    #   # #   # #   #  |";
	out << setfill(' ') << setw(20);
	out << "|" << setfill(' ') << setw(8) << revp << "|";
	out << endl;

	//31
	out << "|" << "________";
	out << "|" << setfill(' ') << setw(61);
	out << "|  ####  ####  #      ###   ###   ###   |";
	out << setfill(' ') << setw(20);
	out << "|" << "________" << "|";
	out << endl;

	//32
	out << "|" << "\033[45m"<< setw(12) << setfill(' ') << right << cphi + "\33[0m";
	out << "|" << setfill(' ') << setw(61);
	out << "|_______________________________________|";
	out << setfill(' ') << setw(20);
	out << "|" << "NEEDLES " << "|";
	out << endl;

	//33
	out << "|" << "--------";
	out << "|" << setfill(' ') << setw(81);
	out << "|" << "HALL    " << "|";
	out << endl;

	//34
	out << "|" << "CPH     ";
	out << "|" << setfill(' ') << setw(81);
	out << "|" << "        " << "|";
	out << endl;

	//35
	out << "|" << setfill(' ') << setw(8) << cphp;
	out << "|" << setfill(' ') << setw(81);
	out << "|" << setfill(' ') << setw(8) << needlesrp << "|";
	out << endl;

	//36
	out << "|" << "________";
	out << "|" << setfill(' ') << setw(81);
	out << "|" << "________" << "|";
	out << endl;

	//37
	out << "|" << "\033[45m"<< setw(12) << setfill(' ') << right << dwei + "\33[0m";
	out << "|" << setfill(' ') << setw(81);
	out << "|" << "\x1b[48;5;54m"<< setw(12) << setfill(' ') << right << mci + "\33[0m" << "|";
	out << endl;

	//38
	out << "|" << "--------";
	out << "|" << setfill(' ') << setw(81);
	out << "|" << "--------" << "|";
	out << endl;

	//39
	out << "|" << "DWE     ";
	out << "|" << setfill(' ') << setw(81);
	out << "|" << "MC      " << "|";
	out << endl;

	//40
	out << "|" << setfill(' ') << setw(8) << dwep;
	out << "|" << setfill(' ') << setw(81);
	out << "|" << setfill(' ') << setw(8) << mcp << "|";
	out << endl;

	//41
	out << "|" << "________";
	out << "|" << setfill(' ') << setw(81);
	out << "|" << "________" << "|";
	out << endl;

	//41
	out << "|" << left << setfill(' ') << setw(8) << "PAC " + paco;
	out << "|" << "                                                                                ";
	out << "|" << "COOP    " << "|";
	out << endl;

	//42
	out << "|" << "        ";
	out << "|" << "                                                                                ";
	out << "|" << "FEE     " << "|";
	out << endl;

	//43
	out << "|" << "        ";
	out << "|" << "                                                                                ";
	out << "|" << "        " << "|";
	out << endl;

	//44
	out << "|" << setfill(' ') << setw(8) << pacp;
	out << "|" << "                                                                                ";
	out << "|" << setfill(' ') << setw(8) << coopp << "|";
	out << endl;

	//45
	out << "|" << "________";
	out << "|" << "                                                                                ";
	out << "|" << "________" << "|";
	out << endl;

	//46
	out << "|" << "\033[45m"<< setw(12) << setfill(' ') << right << rchi + "\33[0m";
	out << "|" << setfill(' ') << setw(81);
	out << "|" << "\x1b[48;5;54m"<< setw(12) << setfill(' ') << right << dci + "\33[0m" << "|";
	out << endl;

	//47
	out << "|" << "--------";
	out << "|" << setfill(' ') << setw(81);
	out << "|" << "--------" << "|";
	out << endl;

	//48
	out << "|" << "RCH     ";
	out << "|" << setfill(' ') << setw(81);
	out << "|" << "DC      " << "|";
	out << endl;

	//49
	out << "|" << setfill(' ') << setw(8) << rchp;
	out << "|" << setfill(' ') << setw(81);
	out << "|" << setfill(' ') << setw(8) << dcp << "|";
	out << endl;

	//50
	out << "|" << "________";
	out << "|" << setfill('_') << setw(81);
	out << "|" << "________" << "|";
	out << endl;



	//51
	out << '|' << left << setw(8) << "DC Tims" << '|';
	out << "\033[46m"<< setw(12) << setfill(' ') << right << hhi + "\33[0m" << "|";
	out << "\033[46m"<< setw(12) << setfill(' ') << right << pasi + "\33[0m" << "|";
	out << left << setw(8) << "NEEDLES" << '|';
	out << "\033[46m"<< setw(12) << setfill(' ') << right << echi + "\33[0m" << "|";
	out << left << setw(8) << setfill(' ') << "MKV " + mkvo <<'|';
	out << left << setw(8) << "TUITION" << '|';
	out << "\033[47m"<< setw(12) << setfill(' ') << right << mli + "\33[0m" << "|";
	out << left << setw(8) << "SLC" << '|';
	out << "\033[47m"<< setw(12) << setfill(' ') << right << ali + "\33[0m";
	out << '|' << left << setw(8) << "COLLECT" << "\33[0m" << '|';
	out << endl;

	//52
	out << '|' << left << setw(8) << "Line" << '|';
	out << left << setw(8) << "--------" << "|";
	out << left << setw(8) << "--------" << '|';
	out << left << setw(8) << "HALL" << '|';
	out << left << setw(8) << "--------" << '|';
	out << left << setw(8) << "        " << '|';
	out << left << setw(8) << "        " << '|';
	out << left << setw(8) << "--------" << '|';
	out << left << setw(8) << "        " << '|';
	out << left << setw(8) << "--------" << '|';
	out << left << setw(8) << "OSAP" << '|';
	out << endl;

	//53
	out << "|" << left << setw(8) << "        ";
	out << "|" << left << setw(8) << "HH";
	out << "|" << left << setw(8) << "PAS";
	out << "|" << left << setw(8) << "        ";
	out << "|" << left << setw(8) << "ECH";
	out << "|" << left << setw(8) << "        ";
	out << "|" << left << setw(8) << "        ";
	out << "|" << left << setw(8) << "ML";
	out << "|" << left << setw(8) << "        ";
	out << "|" << left << setw(8) << "AL";
	out << "|" << left << setw(8) << "        " << "|";
	out << endl;

	//54
	out << "|" << right << setw(8) << dctimesp;
	out << "|" << right << setw(8) << hhp;
	out << "|" << right << setw(8) << pasp;
	out << "|" << right << setw(8) << needlesdp;
	out << "|" << right << setw(8) << echp;
	out << "|" << right << setw(8) << mkvp;
	out << "|" << right << setw(8) << tuitionp;
	out << "|" << right << setw(8) << mlp;
	out << "|" << right << setw(8) << slcdp;
	out << "|" << right << setw(8) << alp;
	out << "|" << right << setw(8) << osapp << "|";
	out << endl;

	//55
	out << "|" << "________";
	out << "|" << "________";
	out << "|" << "________";
	out << "|" << "________";
	out << "|" << "________";
	out << "|" << "________";
	out << "|" << "________";
	out << "|" << "________";
	out << "|" << "________";
	out << "|" << "________";
	out << "|" << "________" << "|";
	out << endl;

}
