#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Menu {

private:
	// Ask for a number from the user
	int requestNumber(int min, int max) {
		int num; string str;
		cout << "> ";
		cin >> str;

		try {
			// Try and convert the inputted string to an integer
			num = stoi(str);
		} catch (exception e) {
			// If it cant be converted, it is not a number
			cout << "Input is not a number, please try again.\n";
			return requestNumber(min, max);
		}

		// Ensure the number is within the range
		if (num < min || num > max) {
			cout << "Input is out of range, please try again.\n";
			return requestNumber(min, max);
		}

		return num;
	}
	
public:
	string header;
	vector<string> options;
	
	// Call this menu
	void run(bool clearBefore, bool clearAfter) {
		// Clear the screen if requested
		if (clearBefore) system("cls");
		cout << header << endl;

		// Print the options
		for (int i = 0; i < options.size(); i++)
			cout << i + 1 << ". " << options[i] << endl;
		
		// Request a selection from the user
		int maxOption = options.size();
		int selectedOption = requestNumber(1, maxOption);
		
		// Clear the screen if requested
		if (clearAfter) system("cls");

		// Call the handleOption method with the selected option
		handleOption(selectedOption);

		// Once the option has been handled, run the menu again
		return run(clearBefore, clearAfter);
	}

	// Handle an option
	// This method is abstract and must be overwritten
	virtual void handleOption(int option) {
		cout << "Menu has not been implemented.\n";
	}
};

