
#include "colors.h"

ColorMaps *ColorMaps::objColorMaps = NULL;

ColorMaps* ColorMaps::getColorMap() {
    if(ColorMaps::objColorMaps == NULL)
        ColorMaps::objColorMaps = new ColorMaps();

    return ColorMaps::objColorMaps;
}

string ColorMaps::getColor(int key) {
    map<int, string>::iterator it;

    it = colormap.find(key);
    if(it != colormap.end())
        return it->second;

    return "";
}

int ColorMaps::getKey(string color) {
    int key = -1;
    map<int, string>::iterator it;

    for(it = colormap.begin(); it != colormap.end(); it++) {
        if(it->second == color)
            key = it->first;
    }

    return key;
}
