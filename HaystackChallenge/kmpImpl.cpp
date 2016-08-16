#include <iostream>
#include <string>
#include <vector>

using namespace std;

void construct_kmp_table(string needle, vector<int>& kmpTable) {
    int pos = 2, cnd = 0;

    kmpTable.push_back(-1) ; kmpTable.push_back(0);

    while(pos < needle.length()) {
        if(needle[pos-1] == needle[cnd]) {
            if(pos >= kmpTable.size())
                kmpTable.push_back(cnd+1);
            else
                kmpTable[pos] = cnd + 1;
            cnd++;
            pos++;
        }
        else if(cnd > 0) {
            cnd = kmpTable[cnd];
        }
        else {
            if(pos >= kmpTable.size())
                kmpTable.push_back(0);
            else
                kmpTable[pos] = 0;
            pos++;
        }
    }
}

int kmp_search(string needle, string haystack, vector<int>& T) {
    int m = 0, i = 0;

    while ((m+i) < haystack.length()) {

        if(needle[i] == haystack[m+i]) {
            if(i == needle.length() - 1)
                return m;
            i++;
        }
        else {
            if(T[i] > -1) {
                m = m + i - T[i];
                i = T[i];
            }
            else {
                m++;
                i = 0;
            }
        }
    }
    return haystack.length();
}

int nextSearchPos(string needle) {
    string temp = needle.substr(0,1);

    size_t pos = needle.substr(1).find(temp);
    if(pos != string::npos)
        // add one to position since we have to count for first character.
        return pos+1;

    // return needle length for search to start after the current match.
    return needle.length();
}

int main()
{
    int n = 0;
    int location = -1, oldLoc = 0;
    int count = 1, posRep = -1;
    int testCasesCnt = 0;

    string needle = "", haystack = "";
    string temp;

    vector<string> needleCollection;
    vector<string> haystackCollection;


    do {
        cin >> n;

        if(n < 1)
            break;

        //cout << n << endl;

        cin.ignore();
        char input;

        while(n != 0) {
            cin >> noskipws;
            cin.get(input);
            if(input == '\n')
                break;
            needle += input;
            n--;
        }
        needleCollection.push_back(needle);

        //cout << needle << endl;

        cin.ignore();
        do{
            cin.get(input);
            if(input != '\n')
                haystack += input;
            else
                break;
        } while(true);


        haystackCollection.push_back(haystack);
        //cout << haystack << endl;
        testCasesCnt++;

        needle = ""; haystack = "";

    }while(true);

    for(int i = 0; i < testCasesCnt; i++) {

        needle = needleCollection[i];
        haystack = haystackCollection[i];

        vector<int> kmpTable;
        construct_kmp_table(needle, kmpTable);

        do {
            location = kmp_search(needle, haystack, kmpTable);
            if(location != haystack.length()) {
                cout << oldLoc + location << endl;

                if(posRep == -1) {
                    posRep = nextSearchPos(needle);
                }

                if(posRep != -1) {
                    haystack = haystack.substr(location + posRep);
                }

                oldLoc += location + posRep;
                count++;
            }
            else
                break;
        } while(true);



        cout << endl;

    location = -1; oldLoc = 0;
    count = 1; posRep = -1;
    }
    return 0;
}