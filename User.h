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
public:
    Type type; // Account type
    string id, // Unique ID
        firstName, // First name
        lastName, // The last name
        dateOfBirth; // Date of birth in the format of DD/MM/YYYY
    int gender; // Refer to ISO/IEC 5218
    string contactNumber, // Contact number
        homeAddress, // Street address
        emailAddress, // Email address
        password;

    User(
        string i,
        string f, string l, string d, int g,
        string c, string h, string e, string p
    ) {
        type = Type::Base;
        id = i;
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
    virtual string toString() {
        return to_string(int(type)) + '~' +
            this->id + '~' + firstName + '~' + lastName + '~' +
            dateOfBirth + '~' + to_string(gender) + '~' +
            contactNumber + '~' + homeAddress + '~' +
            emailAddress + '~' + password;
    }

    // Resolve a number to a Type enum value
    static Type resolveType(int typeInt) {
        if (typeInt == 1) return Type::Admin;
        if (typeInt == 2) return Type::Teacher;
        if (typeInt == 3) return Type::Guardian;
        if (typeInt == 4) return Type::Student;
        return Type::Base;
    }
};
