#pragma once
#include <iostream>
#include <string>

using namespace std;

#ifdef _WIN32
#define CLEAR "cls"
#define PAUSE "pause"
#else
#define CLEAR "clear"
#define PAUSE "read -p \"Press Enter to continue . . .\""
#endif

class Util {
public:
	// Ask for a string from the user
	static string requestString() {
		string str;
		cout << "> ";
		getline(cin, str);
		return str;
	}
	
	// Ask for an integer from the user
	static int requestInteger(int min, int max) {
		string str = requestString();
		int num;
		
		try {
			// Try and convert the inputted string to an integer
			num = stoi(str);
		}
		catch (exception e) {
			// If it cant be converted, it is not an integer
			cout << "Input is not a whole number, please try again.\n";
			return requestInteger(min, max);
		}

		// Ensure the number is within the range
		if (num < min || num > max) {
			cout << "Input is out of range, please try again.\n";
			return requestInteger(min, max);
		}

		return num;
	}

	// Ask for a float from the user
	static float requestFloat(float min, float max) {
		string str = requestString();
		float num;

		try {
			// Try and convert the inputted string to a float
			num = stof(str);
		}
		catch (exception e) {
			// If it cant be converted, it is not an float
			cout << "Input is not a number, please try again.\n";
			return requestFloat(min, max);
		}

		// Ensure the number is within the range
		if (num < min || num > max) {
			cout << "Input is out of range, please try again.\n";
			return requestFloat(min, max);
		}

		return num;
	}

	// Clear the terminal screen
	static void clearScreen() {
		system(CLEAR);
	}

	// Pause the program
	static void pauseProgram() {
		system(PAUSE);
	}
};

