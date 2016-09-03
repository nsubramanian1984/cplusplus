

#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <algorithm>

using namespace std;

enum Color {
	red,
	green,
	blue,
	black,
	white,
	yellow
};

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
	vector< vector<Color> > codePegs;
	vector< vector<Color> > keyPegs;

	vector<Color> codeMakersPegs;

	vector<Color> userInput;

public:
	MasterMind() {}
	void generateCodePegs();
	void displayCodePegs();
	void printCodeAndKeyPegs();

};

void MasterMind::generateCodePegs() {
	Rand_int randomInt(0,5);

	for(int i = 0; i < 4; i++)
		codeMakersPegs.push_back((Color)randomInt());
}

void MasterMind::displayCodePegs() {
	string tempStr = "";

	for(vector<Color>::iterator it = codeMakersPegs.begin(); it != codeMakersPegs.end(); it++) {
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

void MasterMind::printCodeAndKeyPegs() {
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

int getColorCode(string str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	if(str == "red")
		return 0;
	else if(str == "green")
		return 1;
	else if(str == "blue")
		return 2;
	else if(str == "black")
		return 3;
	else if(str == "white")
		return 4;
	else if(str == "yellow")
		return 5;
	else
		return -1;

}


int main() {

	MasterMind mm;

	mm.generateCodePegs();
	mm.displayCodePegs();

	cout << "Asking user to guess " << endl;
	cout << "Input colors separated by space " << endl;

	cout << "Available colors to choose red,green,blue,black,white,yellow" << endl;
	cout << "Enter them in lower case or upper case " << endl;

	vector<Color> userInput;

	string peg1, peg2, peg3, peg4;
	cin >> peg1 >> peg2 >> peg3 >> peg4;

	int tempHold;
	if((tempHold = getColorCode(peg1)) != -1)
		userInput.push_back((Color) tempHold);
	else {
		cout << "Invalid input from user. Terminating program " << endl;
		return 0;
	}
	if((tempHold = getColorCode(peg2)) != -1)
		userInput.push_back((Color) tempHold);
	else {
		cout << "Invalid input from user. Terminating program " << endl;
		return 0;
	}
	if((tempHold = getColorCode(peg3)) != -1)
		userInput.push_back((Color) tempHold);
	else {
		cout << "Invalid input from user. Terminating program " << endl;
		return 0;
	}
	if((tempHold = getColorCode(peg4)) != -1)
		userInput.push_back((Color) tempHold);
	else {
		cout << "Invalid input from user. Terminating program " << endl;
		return 0;
	}

	for(auto x : userInput)
		cout << x << endl;

	return 0;
}