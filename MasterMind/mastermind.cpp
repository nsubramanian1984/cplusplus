

#include "mastermind.h"
#include "util.h"

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
                        strHashes += " # ";
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
                            strQuestions += " ? ";
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
                                strQuestions += " ? ";
                                break;
                            }
                            else {
                                codeMakersPegs[positions[0]].flag = true;
                                strHashes += " # ";
                                break;
                            }
                        }
                    }
                }
                else if (indexUserInput > indexCodeMakerPegs) {
                    if(codeMakersPegs[indexUserInput].code == userInput[indexUserInput]) {
                        codeMakersPegs[indexUserInput].flag = true;
                        strDollars += " $ ";
                    }
                    else {
                        strHashes += " # ";
                        codeMakersPegs[indexCodeMakerPegs].flag = true;
                    }

                    break;
                }
                else {
                    // Hitting jackpots here.
                    codeMakersPegs[indexCodeMakerPegs].flag = true;
                    strDollars += " $ ";
                    break;
                }
            }
            else {
                // If hitting this area TOTAL_COLOR_PEGS_TO_GUESS times,
                // then player is not guessing correctly.
                count++;
                if(count == TOTAL_COLOR_PEGS_TO_GUESS)
                    strQuestions += " ? ";
            }
        }
    }

    // Reset after each attempt.
    vector<ColorPegPair>::iterator it;
    for(it = codeMakersPegs.begin(); it != codeMakersPegs.end(); it++) {
        it->flag = false;
    }

    string temp = strDollars+strHashes+strQuestions;
    cout << "  " + temp << endl;
    temp = StringUtil::getInstance()->trim(temp);
    fillKeyPegs(temp);

    return temp == "$$$$";
}
