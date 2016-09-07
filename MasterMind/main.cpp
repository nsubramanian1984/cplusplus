// author: Subramanian Narasimhan
// https://github.com/nsubramanian1984


#include "util.h"
#include "colors.h"
#include "mastermind.h"

using namespace std;

int main() {

    MasterMind mm;
    char ch;
    int points = -1;
    time_t startTime, endTime;

    mm.generateCodePegs();

    cout << endl << "********* Let's play mastermind ********" << endl << endl;

    cout << "Few things to take note when playing this version of MasterMind." << endl;
    cout << "Game supports six colors." << endl;
    cout << "Available colors to choose red(RD), green(GN), blue(BL), black(BK), white(WH), yellow(YW)." << endl << endl;
    cout << "Each turn results in a feedback from codemaker." << endl;
    cout << "A '$' indicates for each code peg from the guess which is correct in both color and position. " << endl;
    cout << "A '#' indicates the existence of a correct color code peg placed in the wrong position." << endl;
    cout << "A '?' indicates the color code peg is not present in the codemaker color code peg combination." << endl << endl;
    cout << "Please note $, # and ? do not correspond to the color peg positions." << endl;
    cout << "There is no indication given that if you hit a dollar while guessing, it corresponds to the first color" << endl;

    cout << endl << "Codemaker has chosen the keys." << endl;
    cout << "It's now your turn to guess the keys within 10 turns." << endl;
    cout << "Please input colors separated by space. For e.g. RD BL BK WH." << endl;
    cout << "Enter colors in either lower case or upper case." << endl;

    do {
        int numberOfAttempts = 1;
        bool guessed = false;

        while(numberOfAttempts <= TOTAL_NUMBER_OF_TURNS && !guessed) {
            cout << endl << ">? ";

            string peg;
            for(int i = 0; i < TOTAL_COLOR_PEGS_TO_GUESS; i++) {
                cin >> peg;
                if(mm.fillUserInput(peg) == -1) {
                    cout << "Invalid input from user. Terminating program " << endl;
                    return 0;
                }
            }

            if(numberOfAttempts == 1) {
                time(&startTime);
            }

            guessed = mm.getHits();
            if(!guessed)
                cout << "\t\tLeft with " << TOTAL_NUMBER_OF_TURNS - numberOfAttempts << " turns to guess." << endl;

            time(&endTime);

            points = rewardPoints(TOTAL_NUMBER_OF_TURNS - numberOfAttempts);

            // Fill vector with current user's input. This data can be logged into a file.
            mm.fillAllUserInputs();

            // Reset user input for every attempt
            mm.clearUserInput();

            numberOfAttempts++;
        }

        if(guessed)
            cout <<  endl << "Success. You have scored " << points << \
                " points and solved the puzzle in " << (endTime - startTime) << " seconds." << endl;
        else
            cout << "Failed to guess correctly." << endl;

        cout << endl << "****** Hits and misses ******" << endl;
        mm.printCodeAndKeyPegs();

        cout << endl <<  "****** Code maker's chosen pegs. *******" << endl;
        mm.displayCodePegs();

        // Clear the code pegs and user's input for next game.
        mm.clearKeyPegs(); mm.clearusersInputPegs();

        cout << endl << "Press 'y' to play the game again or any other key to quit.\n>? ";

    } while((cin >> ch) && (ch == 'y' || ch == 'Y'));

    delete ColorMaps::getColorMap();
    delete StringUtil::getInstance();

    return 0;
}
