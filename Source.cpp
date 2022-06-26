#include <iostream>

#include "Database.h"
#include "AdminMenu.h"
#include "TeacherMenu.h"
#include "StudentMenu.h"

using namespace std;

int main() {
    Database db;
    db.load();

    cout << "===== School Information System =====\n";

	// Get search query from user
    cout << "\nEnter your user ID or email to login.\n";
    string query = Util::requestString();

    bool userFound = false;

	// Loop over every user in the database
    for (auto u : db.users) {
		// If id or email does not equal the query, skip this user
        if (u->id != query && u->emailAddress != query) continue;
        userFound = true;

		// Loop 3 times if password is incorrect
        for (int i = 0; i < 3; i++) {
			// Get password from user
            cout << "Enter your account password.\n";
            string password = Util::requestString();
        
            if (u->password == password) {
			    // If password is correct direct user to menu
                if (u->type == Type::Admin) {
                    AdminMenu adminMenu(&db, u);
                    adminMenu.run();
                } else if (u->type == Type::Teacher) {
                    TeacherMenu teacherMenu(&db, u);
                    teacherMenu.run();
                } else {
                    StudentMenu studentMenu(&db, u);
                    studentMenu.run();
                }
                break;
            } else {
                // If password is incorrect, print error message
                cout << "Incorrect passowrd, try again.\n";
                if (i == 2) {
					// If password is incorrect 3 times, print error message and return
                    cout << "You have exceeded the maximum number of login attempts.\n";
                    return 0;
                }
            }
        }

        break;
    }

    if (!userFound) {
		// If no user was found with the given id or email, print an error message
        cout << "Account not found.\n";
        Util::pauseProgram();
        Util::clearScreen();
    }

    db.save();
    return main();
}