#include "util.h"


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
    str = str.substr(first, (last-first+1));
    str.erase(remove(str.begin(), str.end(), ' '), str.end());

    return str;
}

int rewardPoints(int numberOfTurnsLeft)
{
    return (numberOfTurnsLeft * 1000);
}