#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include "User.h"

class Guardian :
    public User
{
    vector<string> studentIds; // A list of student IDs that the guardian is responsible for

public:
    Guardian(User user, vector<string> studentIds) : User(
        user.id,
        user.firstName, user.lastName, user.dateOfBirth,
        user.gender, user.contactNumber, user.homeAddress,
        user.emailAddress, user.password
    ) {
        type = Type::Guardian;
        this->studentIds = studentIds;
    }

    string toString() {
        ostringstream students;
        // Because values are separate by commas, we will use | to separate student IDs
        copy(studentIds.begin(), studentIds.end() - 1,
            ostream_iterator<string>(students, "|"));
        students << studentIds.back();
        return User::toString() + ',' + students.str();
    }
};
