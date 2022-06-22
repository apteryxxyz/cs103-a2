#pragma once
#include <string>
#include "User.h"

class Student : public User
{
public:
    string classId; // ID of the class the student is in

    Student(User user, string classId) : User(
                                             user.id,
                                             user.firstName, user.lastName, user.dateOfBirth,
                                             user.gender, user.contactNumber, user.homeAddress,
                                             user.emailAddress, user.password)
    {
        type = Type::Student;
        this->classId = classId;
    }

    string toString()
    {
        return User::toString() + '~' + classId;
    }
};