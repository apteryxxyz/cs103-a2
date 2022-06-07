#include <string>
#include <vector>
#include <iostream>

#include "User.h"
#include "Admin.h"
#include "Teacher.h"
#include "Guardian.h"
#include "Student.h"

using namespace std;

int main() {
    User user("Hello", "World", "10/10/2010", 1, "111", "Home", "e@mail.com", "password");
	
    Admin admin(user);
    Teacher teacher(user, "classid");
    Guardian guardian(user, vector<string> { "studentid", "studentid" });
    Student student(user, "classid");
	
    cout << teacher.toString() << endl;
    cout << guardian.toString() << endl;
    cout << student.toString() << endl;

    return 0;
}
