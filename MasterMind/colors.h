#ifndef _colors_h_
#define _colors_h_

#include <map>
#include <string>

using namespace std;

#define NUMBER_OF_KEYS  6

enum Color {
    red,
    green,
    blue,
    black,
    white,
    yellow
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

    static ColorMaps* getColorMap();


    ~ColorMaps() {
        objColorMaps = NULL;
    };

    string getColor(int key);
    int getKey(string color);
};



#endif