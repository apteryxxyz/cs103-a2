#pragma once
#include <string>
#include <sstream>
using namespace std;

// Enum for the different types of user accounts
enum class Type {
    Base,
    Admin,
    Teacher,
    Guardian,
    Student,
};

class User {
private:
	// Generate a random ID to use for the user
    string generateId() {
        string obj;
        uint32_t rawId = reinterpret_cast<uint32_t>(&obj);
        return to_string(rawId);
    }
    
public:
    Type type; // Account type
    string id, // Unique ID
        firstName, // First name
        lastName, // The last name
        dateOfBirth; // Date of birth in the format of DD/MM/YYYY
    int gender; // 1 = male, 2 = female, 3 = other
    string contactNumber, // Contact number
        homeAddress, // Street address
        emailAddress, // Email address
        password;

    User(
        string f, string l, string d, int g,
        string c, string h, string e, string p
    ) {
        type = Type::Base;
        id = generateId();
        firstName = f;
        lastName = l;
        dateOfBirth = d;
        gender = g;
        contactNumber = c;
        homeAddress = h;
        emailAddress = e;
        password = p;
    }

	// Convert this user object into a string
    // Intended for database storage
    string toString() {
        return to_string(int(type)) + ',' +
            id + ',' + firstName + ',' + lastName + ',' +
            dateOfBirth + ',' + to_string(gender) + ',' +
            contactNumber + ',' + homeAddress + ',' +
            emailAddress + ',' + password;
    }
};
