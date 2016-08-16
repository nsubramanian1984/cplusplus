#include <iostream>

using namespace std;

int repRep(string needle) {
    string temp = needle.substr(0,1);
    cout << "substr " << temp << endl;

    size_t pos = needle.substr(1).find(temp);
    if(pos != string::npos)
        return pos+1; // add one to position since we have to count for first character.

    // return needle length for search to start after the current match.
    return needle.length();
}

int main() {

    string needle;

    cin >> needle;
    int pos = repRep(needle);
    cout << "next occur " << pos << endl;
}
