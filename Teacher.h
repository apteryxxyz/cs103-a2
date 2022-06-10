#pragma once
#include <string>
#include "User.h"

class Teacher :
    public User
{
public:
    string classId; // The ID of the class this teacher teaches
    
    Teacher(User user, string classId) : User(
        user.id,
        user.firstName, user.lastName, user.dateOfBirth,
        user.gender, user.contactNumber, user.homeAddress,
        user.emailAddress, user.password
    ) {
        type = Type::Teacher;
        this->classId = classId;
    }

    string toString() {
        return User::toString() + '~' + classId;
    }
};
