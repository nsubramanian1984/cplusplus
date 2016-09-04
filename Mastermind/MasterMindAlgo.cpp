//
//  main.cpp
//  Mastermind
//
//  Created by Subramanian Narasimhan on 4/9/16.
//  Copyright © 2016 Subramanian Narasimhan. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>

using namespace std;

#define NUMBER_OF_KEYS 6
#define TOTAL_COLOR_PEGS_TO_GUESS 6

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
    int operator()() { return dist(re); } //draw an int

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

typedef struct  {
    Color code;
    bool flag;
} ColorPegPair;

vector<ColorPegPair> codeMakersPegs;
vector<Color> userInput;

// int getHits() {

//     bool isGuessCorrect = true;

//     // for (auto x : userInput) {
//     //     vector<Color>::iterator it;
//     //     it = find(codeMakersPegs.begin(), codeMakersPegs.end(), x);
//     //     if(it != codeMakersPegs.end()) {
//     //         cout << "Element " << ColorMaps::getColorMap()->getColor(x) << " is found at index " << distance(codeMakersPegs.begin(), it) << endl;
//     //     }
//     // }
//     string seqBlack = "", seqWhite = "", seqHoles = "";

//     vector<Color>::iterator colorIter;
//     for (colorIter = userInput.begin(); colorIter != userInput.end(); colorIter++) {
//         vector<ColorPegPair>::iterator it;

//         Color x = (*colorIter);
//         it = find_if(codeMakersPegs.begin(), codeMakersPegs.end(), [x](ColorPegPair y) {
//             return (x == y.code && !y.flag);
//             });

//         if(it != codeMakersPegs.end() && !(*it).flag) {
//             cout << "Element " << ColorMaps::getColorMap()->getColor(x) << " is found at index " << distance(codeMakersPegs.begin(), it) << endl;
//             if(distance(codeMakersPegs.begin(), it) != distance(userInput.begin(), colorIter)) {
//                 isGuessCorrect = false;
//                 seqWhite += "# ";
//             }
//             else {
//                 seqBlack += "$ ";
//             }

//             (*it).flag = true;
//         }

//         else {
//             isGuessCorrect = false;
//             seqHoles += "? ";
//             (*it).flag = true;
//         }
//     }

//     cout << "is guess correct " << isGuessCorrect << " " << seqBlack+seqWhite+seqHoles << endl;
//     return 0;
// }

int getHitsComplex() {

    string strQuestions = "", strHashes = "", strDollars = "";

    int indexUserInput = 0, indexCodeMakerPegs = 0;

    for(; indexUserInput < TOTAL_COLOR_PEGS_TO_GUESS; indexUserInput++)
    {
        Color x = userInput[indexUserInput];

        int count = 0;
        for(indexCodeMakerPegs = 0; indexCodeMakerPegs < TOTAL_COLOR_PEGS_TO_GUESS; indexCodeMakerPegs++)
        {
            if(x == codeMakersPegs[indexCodeMakerPegs].code && !codeMakersPegs[indexCodeMakerPegs].flag)
            {
                if(indexUserInput < indexCodeMakerPegs)
                {
                    if((Color) userInput[indexCodeMakerPegs] != (Color) codeMakersPegs[indexCodeMakerPegs].code)
                    {
                        // this is a case of printing '#'
//                        cout << "Printing #" << endl;
                        strHashes += "# ";
                        codeMakersPegs[indexCodeMakerPegs].flag = true;
                        break;
                    }
                    else
                    {
                        // if user has entered same values then algorithm goes for a spin.


                        vector<int> positions;

                        for(int i = (indexCodeMakerPegs+1); i < TOTAL_COLOR_PEGS_TO_GUESS; i++)
                        {
                            if((Color) userInput[indexUserInput] == (Color) codeMakersPegs[i].code)
                                positions.push_back(i);
                        }

                        if(positions.empty())
                        {
//                            cout << "Printing ?. Move to the next element" << endl;
                            strQuestions += "? ";
                            break;
                        }
                        else
                        {
                            bool allSame = false;

                            for(int i = 0; i < positions.size(); i++)
                            {
                                if((Color) userInput[positions[i]] == (Color) codeMakersPegs[positions[i]].code)
                                    allSame = true;
                                else
                                    allSame = false;
                            }

                            if(allSame) {
                                //cout << "Printing ?. Its over.. Search ends here."<< endl;
                                strQuestions += "? ";
                                break;
                            }
                            else {
//                                cout << "Printing #. Its also over here.." << endl;
//                                cout << "set the first element in vector to zero" << endl;
                                codeMakersPegs[positions[0]].flag = true;
                                strHashes += "# ";
                                break;
                            }
                        }
                    }
                }
                else if (indexUserInput > indexCodeMakerPegs)
                {
                    // There are possibilities for a next index.
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
                else
                {
                    // they are of same index... so return '$'
//                    cout << "jackpot  ... $"<< endl;

                    codeMakersPegs[indexCodeMakerPegs].flag = true;
                    strDollars += "$ ";
                    break;
                }
            }
            else
            {
                // If hitting this TOTAL_COLOR_PEGS_TO_GUESS times, then no way this is a '?'
                count++;
                if(count == TOTAL_COLOR_PEGS_TO_GUESS)
                    strQuestions += "? ";
            }
        }
    }

    cout << strDollars+strHashes+strQuestions << endl;
    return 0;
}



int main() {

    Rand_int randomInt(0,5);

     for(int i = 0; i < 2; i++) {

         cout << "**********" << endl;

         for(int i = 0; i < TOTAL_COLOR_PEGS_TO_GUESS; i++) {
             codeMakersPegs.push_back({(Color)randomInt(), false});
             userInput.push_back((Color)randomInt());
         }

         for(auto x : codeMakersPegs) {
             cout << ColorMaps::getColorMap()->getColor(x.code) <<  " ";
         }

         cout << endl;

         for(auto x : userInput) {
             cout << ColorMaps::getColorMap()->getColor(x) << " " ;
         }
         cout << endl;

         getHitsComplex();

         for(auto x : codeMakersPegs) {
             cout << ColorMaps::getColorMap()->getColor(x.code) << " " << x.flag <<  endl;
         }

         codeMakersPegs.clear(); userInput.clear();

         cout << "**********" << endl;
     }

//    codeMakersPegs.push_back({(Color)2, false});codeMakersPegs.push_back({(Color)3, false});
//    codeMakersPegs.push_back({(Color)4, false});codeMakersPegs.push_back({(Color)3, false});
//
//    userInput.push_back((Color) 3);
//    userInput.push_back((Color) 5);
//    userInput.push_back((Color) 5);
//    userInput.push_back((Color) 5);
//    for(auto x : codeMakersPegs) {
//        cout << ColorMaps::getColorMap()->getColor(x.code) <<  " ";
//    }
//
//    cout << endl;
//
//    for(auto x : userInput) {
//        cout << ColorMaps::getColorMap()->getColor(x) << " " ;
//    }
//    cout << endl;
//
//    getHitsComplex();
//
//    for(auto x : codeMakersPegs) {
//        cout << ColorMaps::getColorMap()->getColor(x.code) << " " << x.flag <<  endl;
//    }
//
    return 0;
}