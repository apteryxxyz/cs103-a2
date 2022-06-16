#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Util.h"

using namespace std;

class Menu {

public:
    string header;
    vector<string> options;

    // Call this menu
    void run() {
        // Clear the screen
        Util::clearScreen();

        cout << header;
		
        // Print the options
        for (int i = 0; i < options.size(); i++)
            cout << i + 1 << ". " << options[i] << endl;
        
        // Request a selection from the user
        int maxOption = options.size();
        int selectedOption = Util::requestInteger(1, maxOption);
        
        // Clear the screen
        Util::clearScreen();

        // Call the handleOption method with the selected option
        bool runAgain = handleOption(selectedOption);

        // If should run again, do so
        if (runAgain) run(clearBefore, clearAfter);
    }

    // Handle an option
    // This method is abstract and must be overwritten
    virtual bool handleOption(int option) {
        cout << "Menu has not been implemented.\n";
        return false;
    }

    // Quick way to show a basic mini menu
    static int runMiniMenu(vector<string> options) {
        for (int i = 0; i < options.size(); i++)
            cout << i + 1 << ". " << options[i] << endl;

        int maxOption = options.size();
        return Util::requestInteger(1, maxOption);
    }
};
