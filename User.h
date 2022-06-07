#pragma once
#include <string>
#include <sstream>
using namespace std;

enum class Type {
    Base,
    Admin,
    Teacher,
    Guardian,
    Student,
};

class User {
private:
    string generateId() {
        string obj;
        uint32_t rawId = reinterpret_cast<uint32_t>(&obj);
        return to_string(rawId);
    }
    
public:
    Type type;
    string id, firstName, lastName, dateOfBirth;
    int gender;
    string contactNumber, homeAddress, emailAddress, password;

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

    string toString() {
        return to_string(int(type)) + ',' +
            id + ',' + firstName + ',' + lastName + ',' +
            dateOfBirth + ',' + to_string(gender) + ',' +
            contactNumber + ',' + homeAddress + ',' +
            emailAddress + ',' + password;
    }
};
