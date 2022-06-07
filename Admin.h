#pragma once
#include <string>
#include "User.h"

class Admin :
    public User
{
public:
    Admin(User user) : User(
        user.firstName, user.lastName, user.dateOfBirth,
        user.gender, user.contactNumber, user.homeAddress,
        user.emailAddress, user.password
    ) {
        type = Type::Admin;
    }
    
    string toString() {
        return User::toString();
    }
};
