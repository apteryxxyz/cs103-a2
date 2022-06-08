#pragma once
#include <string>

using namespace std;

class Class {
public:
    string id;
    int yearLevel;
    
    Class(string i, int y) {
        id = i;
        yearLevel = y;
    }

    string toString() {
        return id + ',' + to_string(yearLevel);
    }
};

