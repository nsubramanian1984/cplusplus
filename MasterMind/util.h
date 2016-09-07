#ifndef _util_h_
#define _util_h_

#include <string>
#include <random>
#include <algorithm>

using namespace std;

class StringUtil {

private:
    StringUtil() {};
    static StringUtil *instance;

public:
    static StringUtil* getInstance();

    ~StringUtil() {
        instance = NULL;
    };

    string trim(string& str);
};

class Rand_int {

private:
    random_device re;
    uniform_int_distribution<> dist;

public:
    Rand_int(int low, int high) :dist(low,high) { }
    int operator()() {
        return dist(re);
    }
};

int rewardPoints(int);

#endif