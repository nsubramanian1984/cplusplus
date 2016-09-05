// author: Subramanian Narasimhan
// https://github.com/nsubramanian1984

#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

#define NUMBER_OF_KEYS              6
#define TOTAL_COLOR_PEGS_TO_GUESS   4
#define TOTAL_NUMBER_OF_TURNS       10

enum Color {
    red,
    green,
    blue,
    black,
    white,
    yellow
};

class Rand_int {

private:
    random_device re;
    uniform_int_distribution<> dist;

public:
    Rand_int(int low, int high) :dist(low,high) { }
    int operator()() { return dist(re); }

};

class ColorMaps {

private:
    map<int, string> colormap;
    string colors[NUMBER_OF_KEYS] = {"RD", "GN", "BL", "BK", "WH", "YW"};

    ColorMaps() {
        for(int i = 0; i < NUMBER_OF_KEYS; i++)
            colormap.insert(pair<int, string>(i, colors[i]));
    }

    static ColorMaps *objColorMaps;

public:

    static ColorMaps* getColorMap() {
        if(objColorMaps == NULL)
            objColorMaps = new ColorMaps();

        return objColorMaps;
    }

    string getColor(int key) {
        map<int, string>::iterator it;

        it = colormap.find(key);
        if(it != colormap.end())
            return it->second;

        return "";
    }

    int getKey(string color) {
        int key = -1;
        map<int, string>::iterator it;

        for(it = colormap.begin(); it != colormap.end(); it++) {
            if(it->second == color)
                key = it->first;
        }

        return key;
    }
};

ColorMaps *ColorMaps::objColorMaps = NULL;

class StringUtil {
private:
    static StringUtil *instance;
public:
    StringUtil() {}

    string trim(string& str);
    static StringUtil* getInstance();
};

StringUtil* StringUtil::instance = NULL;

StringUtil* StringUtil::getInstance() {
    if(instance == NULL) {
        instance = new StringUtil();
    }

    return instance;
}

string StringUtil::trim(string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last-first+1));
}

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

void MasterMind::generateCodePegs() {
    Rand_int randomInt(0,5);

    for(int i = 0; i < TOTAL_COLOR_PEGS_TO_GUESS; i++)
        codeMakersPegs.push_back({(Color)randomInt(), false});
}

void MasterMind::displayCodePegs() {

    for(vector<ColorPegPair>::iterator it = codeMakersPegs.begin(); it != codeMakersPegs.end(); it++)
        cout << ColorMaps::getColorMap()->getColor(it->code) << " ";

    cout << endl;
}

void MasterMind::printCodeAndKeyPegs() {

    // for(int i = 0; i <= 20; i++)
    //     cout << "-";

    // cout << endl;

    // for(int k = 0 ; k < 1; k++) {
    //     string str = "";
    //     for(int i = 0; i <= 15; i++)
    //         str += " ";

    //     str += char(111);
    //     str += " ";
    //     str += char(111);
    //     cout << str << endl;

    //     for (int i = 0; i < TOTAL_COLOR_PEGS_TO_GUESS; i++)
    //         cout << " " << char(79) << "  ";

    //     cout << endl;
    //     cout << str << endl;

    //     for(int i = 0; i <= 20; i++)
    //         cout << "-";

    //     cout << endl;
    // }

    for(int i = 0; i < usersInputPegs.size(); i++) {
        string str = "";
        for(int j = 0; j < usersInputPegs[i].size(); j++) {
            str += ColorMaps::getColorMap()->getColor(usersInputPegs[i][j]) + " ";
        }

        cout << str << " " << keyPegs[i] << endl;
    }
}

int MasterMind::getColorCode(string str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return ColorMaps::getColorMap()->getKey(str);
}

int MasterMind::fillUserInput(string colorPeg) {
    int color;

    if((color = getColorCode(colorPeg)) != -1) {
        userInput.push_back((Color) color);
        return 0;
    }

    return -1;
}

void MasterMind::clearUserInput() {
    userInput.clear();
}

void MasterMind::clearKeyPegs() {
    keyPegs.clear();
}

void MasterMind::clearusersInputPegs() {
    usersInputPegs.clear();
}

void MasterMind::displayUserInput() {
    for(auto x : userInput)
        cout << x << " ";
    cout << endl;
}

void MasterMind::fillAllUserInputs() {
    usersInputPegs.push_back(userInput);
}

void MasterMind::fillKeyPegs(string str) {
    keyPegs.push_back(str);
}

bool MasterMind::getHits() {

    string strQuestions = "", strHashes = "", strDollars = "";

    for(int indexUserInput = 0; indexUserInput < TOTAL_COLOR_PEGS_TO_GUESS; indexUserInput++) {
        Color x = userInput[indexUserInput];

        int count = 0;

        for(int indexCodeMakerPegs = 0; indexCodeMakerPegs < TOTAL_COLOR_PEGS_TO_GUESS; indexCodeMakerPegs++) {
            if(x == codeMakersPegs[indexCodeMakerPegs].code && !codeMakersPegs[indexCodeMakerPegs].flag) {
                if(indexUserInput < indexCodeMakerPegs) {
                    if((Color) userInput[indexCodeMakerPegs] != (Color) codeMakersPegs[indexCodeMakerPegs].code) {
                        strHashes += "# ";
                        codeMakersPegs[indexCodeMakerPegs].flag = true;
                        break;
                    }
                    else {
                        vector<int> positions;

                        for(int i = (indexCodeMakerPegs+1); i < TOTAL_COLOR_PEGS_TO_GUESS; i++) {
                            if((Color) userInput[indexUserInput] == (Color) codeMakersPegs[i].code)
                                positions.push_back(i);
                        }

                        if(positions.empty()) {
                            strQuestions += "? ";
                            break;
                        }
                        else {
                            bool allSame = false;

                            for(unsigned int i = 0; i < positions.size(); i++) {
                                if((Color) userInput[positions[i]] == (Color) codeMakersPegs[positions[i]].code)
                                    allSame = true;
                                else
                                    allSame = false;
                            }

                            if(allSame) {
                                strQuestions += "? ";
                                break;
                            }
                            else {
                                codeMakersPegs[positions[0]].flag = true;
                                strHashes += "# ";
                                break;
                            }
                        }
                    }
                }
                else if (indexUserInput > indexCodeMakerPegs) {
                    if(codeMakersPegs[indexUserInput].code == userInput[indexUserInput]) {
                        codeMakersPegs[indexUserInput].flag = true;
                        strDollars += "$ ";
                    }
                    else {
                        strHashes += "# ";
                        codeMakersPegs[indexCodeMakerPegs].flag = true;
                    }

                    break;
                }
                else {
                    // Hitting jackpots here.
                    codeMakersPegs[indexCodeMakerPegs].flag = true;
                    strDollars += "$ ";
                    break;
                }
            }
            else {
                // If hitting this area TOTAL_COLOR_PEGS_TO_GUESS times,
                // then player is not guessing correctly.
                count++;
                if(count == TOTAL_COLOR_PEGS_TO_GUESS)
                    strQuestions += "? ";
            }
        }
    }

    // Reset after each attempt.
    vector<ColorPegPair>::iterator it;
    for(it = codeMakersPegs.begin(); it != codeMakersPegs.end(); it++) {
        it->flag = false;
    }

    string temp = strDollars+strHashes+strQuestions;
    cout << temp << endl;
    temp = StringUtil::getInstance()->trim(temp);
    fillKeyPegs(temp);

    return temp == "$ $ $ $";
}

int main() {

    MasterMind mm;
    char ch;

    mm.generateCodePegs();
    //mm.displayCodePegs();

    cout << "********* Let's play mastermind ********" << endl << endl;

    cout << "******* Game supports six colors *******" << endl;
    cout << "Few things to take note when playing this version of MasterMind." << endl;
    cout << "Available colors to choose red(RD), green(GN), blue(BL), black(BK), white(WH), yellow(YW)" << endl;
    cout << "Each turn results in a feedback from codemaker." << endl;
    cout << "A '$' indicates for each code peg from the guess which is correct in both color and position. " << endl;
    cout << "A '#' indicates the existence of a correct color code peg placed in the wrong position." << endl;
    cout << "A '?' indicates the color code peg is not present in the codemaker color peg combination." << endl << endl;
    cout << "Codemaker has chosen the keys." << endl;
    cout << "It's now your turn to guess his keys within 10 turns." << endl;
    cout << "Please input colors separated by space. For e.g. RD BL BK WH." << endl;
    cout << "Enter colors in either lower case or upper case." << endl;

    do {
        int numberOfAttempts = 1;
        bool guessed = false;

        while(numberOfAttempts <= TOTAL_NUMBER_OF_TURNS && !guessed) {
            cout << "Attempt : " << numberOfAttempts << endl;

            string peg;
            for(int i = 0; i < TOTAL_COLOR_PEGS_TO_GUESS; i++) {
                cin >> peg;
                if(mm.fillUserInput(peg) == -1) {
                    cout << "Invalid input from user. Terminating program " << endl;
                    return 0;
                }
            }

            //mm.displayUserInput();
            // mm.printCodeAndKeyPegs();

            guessed = mm.getHits();
            if(!guessed)
                cout << "Failed Attempt " << numberOfAttempts << ". Remaining " << TOTAL_NUMBER_OF_TURNS - numberOfAttempts << endl;

            // Fill vector with current user's input. This data can be logged in a file.
            mm.fillAllUserInputs();

            // Reset user input for every attempt
            mm.clearUserInput();

            numberOfAttempts++;
        }

        if(guessed)
            cout << "Success" << endl;
        else
            cout << "Failed to guess correctly." << endl;

        mm.printCodeAndKeyPegs();
        mm.displayCodePegs();

        mm.clearKeyPegs(); mm.clearusersInputPegs();

        cout << "Do you want to continue (y/n)? ";

    } while((cin >> ch) && (ch == 'y'));
    return 0;
}
