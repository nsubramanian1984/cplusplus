#ifndef _mastermind_h_
#define _mastermind_h_


#include <iostream>
#include <string>
#include <vector>

#include "colors.h"

using namespace std;

#define NUMBER_OF_KEYS              6
#define TOTAL_COLOR_PEGS_TO_GUESS   4
#define TOTAL_NUMBER_OF_TURNS       10

class MasterMind {
private:
    typedef struct  {
        Color code;
        bool flag;
    } ColorPegPair;

    vector<ColorPegPair> codeMakersPegs;
    vector<Color> userInput;

    vector< vector<Color> > usersInputPegs;
    vector<string> keyPegs;

public:
    MasterMind() {}

    void generateCodePegs();
    void displayCodePegs();
    void printCodeAndKeyPegs();

    void displayUserInput();

    void fillAllUserInputs();
    void fillKeyPegs(string);
    int fillUserInput(string);

    void clearUserInput();
    void clearKeyPegs();

    void clearusersInputPegs();
    int getColorCode(string);
    bool getHits();
};

#endif