#include <string>
#include <vector>
#include <iostream>

#include "Database.h"
#include "User.h"
#include "Admin.h"
#include "Teacher.h"
#include "Guardian.h"
#include "Student.h"

using namespace std;

int main() {
	Database database = {};
	database.loadUsers();

	string id = Database::generateId();
	User user(id, "John", "Doe", "21/11/1976", 1, "111", "10 Downing Street", "jd@mail.com", "p@ssw0rd");
	cout << id << endl;

	Teacher *teacher = new Teacher(user, id);
	Guardian *guardian = new Guardian(user, { id });
	Student *student = new Student(user, id);
	

	if (database.users.empty()) {
		database.users.push_back(teacher);
		database.users.push_back(guardian);
		database.users.push_back(student);
	}

	for (auto i = database.users.begin(); i != database.users.end(); i++) {
		cout << (*i)->toString() << endl;
	}

	database.saveUsers();
	return 0;
}