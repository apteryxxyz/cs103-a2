#include <string>
#include <vector>
#include <iostream>

#include "Database.h"
#include "User.h"
#include "Admin.h"
#include "Teacher.h"
#include "Guardian.h"
#include "Student.h"
#include "Report.h"
#include "Class.h"

using namespace std;

int main() {
    Database database;
    database.load();

    string id1 = Database::generateId(),
        id2 = Database::generateId(),
        id3 = Database::generateId();

    User user(id1, "John", "Smith", "21/11/1976", 1, "111", "10 Downing Street", "jd@mail.com", "p@ssw0rd");
    Teacher* teacher = new Teacher(user, id1);
    Guardian* guardian = new Guardian(user, { id1 });
	Student* student = new Student(user, id2);

    Class* xlass = new Class(id2, 5);
	Report* x = new Report(id3, "T Note", "P Note", 100, {
        { Subject::English, Grade::Merit, "Note" },
        { Subject::Arts, Grade::NotAchieved, "Note" },
    });

    database.users.push_back(teacher);
	database.users.push_back(guardian);
	database.users.push_back(student);
	database.classes.push_back(xlass);
	database.reports.push_back(x);
	
    cout << "Users\n";
	for (auto i : database.users)
        cout << i-> toString() << endl;
    cout << "\nClasses\n";
	for (auto i : database.classes)
        cout << i-> toString() << endl;
	cout << "\nReports\n";
	for (auto i : database.reports)
		cout << i-> toString() << endl;
    
    database.save();
    return 0;
}
