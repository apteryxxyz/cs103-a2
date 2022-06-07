#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include "User.h"

class Guardian :
    public User
{
    vector<string> studentIds;

public:
    Guardian(User user, vector<string> studentIds) : User(
        user.firstName, user.lastName, user.dateOfBirth,
        user.gender, user.contactNumber, user.homeAddress,
        user.emailAddress, user.password
    ) {
        type = Type::Guardian;
        this->studentIds = studentIds;
    }

    string toString() {
        ostringstream students;
        copy(studentIds.begin(), studentIds.end() - 1,
            ostream_iterator<string>(students, "/"));
        students << studentIds.back();
        return User::toString() + ',' + students.str();
    }
};
