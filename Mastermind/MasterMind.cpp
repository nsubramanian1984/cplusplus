

#include <iostream>
#include <string>
#include <random>
#include <vector>

using namespace std;

enum Color {
	red,
	green,
	blue,
	black,
	white,
	yellow
};

#define STRINGIFY(x) #x

void printCodeAndKeyPegs() {
	for(int i = 0; i <= 20; i++)
		cout << "-";

	cout << endl;

	for(int k = 0 ; k < 10; k++) {
		string str = "";
		for(int i = 0; i <= 15; i++)
			str += " ";

		str += char(248);
		str += " ";
		str += char(248);
		cout << str << endl;
	
		for (int i = 0; i <= 3; i++)
			cout << " " << char(79) << "  ";

		cout << endl; 
		cout << str << endl;

		for(int i = 0; i <= 20; i++)
			cout << "-";

		cout << endl;
	}
}

class Rand_int {

public:
	Rand_int(int low, int high) :dist(low,high) { }	
	int operator()() { return dist(re); } //draw an int
	
private:
	random_device re;	
	uniform_int_distribution<> dist;
};

class MasterMind {
private:
	vector<Color> codePegs;
	vector<Color> keyPegs;

public:
	MasterMind() {}
	void generateCodePegs();
	void displayCodePegs();
};

void MasterMind::generateCodePegs() {
	Rand_int randomInt(0,5);

	for(int i = 0; i < 4; i++)
		codePegs.push_back((Color)randomInt());
}

void MasterMind::displayCodePegs() {
	string tempStr = "";

	for(vector<Color>::iterator it = codePegs.begin(); it != codePegs.end(); it++) {
		switch (*it) {
		case 0:
			tempStr += " RED ";
			break;
		case 1:
			tempStr += " GREEN ";
			break;
		case 2:
			tempStr += " BLUE";
			break;
		case 3:
			tempStr += " BLACK ";
			break;
		case 4:
			tempStr += " WHITE ";
			break;
		case 5:
			tempStr += " YELLOW ";
			break;
		}
	}

	cout << tempStr << endl;
}

int main() {

	MasterMind mm;

	mm.generateCodePegs();
	mm.displayCodePegs();


	
	return 0;
}