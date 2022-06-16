#pragma once
#include "Menu.h"
#include "Database.h"
#include "Util.h"

using namespace std;

class AdminMenu : public Menu {
private:
    Database* database;

public:
    AdminMenu(Database* database) {
        this->database = database;
        header = "Welcome to the admin menu, select an option from below!\n";
        // TODO: Add "Manage User" and "Manage Class"
        options = { "List Users", "View User", "Create User", "List Classes", "View Class", "Create Class", "Logout" };
    }

    bool handleOption(int option) {
        if (option == 1) { // List Users
            cout << "===== List Of Users =====\n\n";
            cout << "Account Type - ID - Name \n";

            // Loop over each user and display their information
            for (auto u : database->users) {
                cout << int(u->type) << " - "
                    << u->id << " - "
                    << u->firstName + " " + u->lastName
                    << endl;
            }

            cout << endl;
            Util::pauseProgram();
        }
        
        else if (option == 2) { // View User
            cout << "===== View User =====\n\n";

            // Get the search query from the admin
            cout << "Enter ID or email to search for.\n";
            string query = Util::requestString();

            // Loop over every user in the database and
            // check if the query matches their ID or email
            for (auto u : database->users) {
                // Skip if query does not equal ID or email
                if (u->id != query && u->emailAddress != query) continue;
                
                // Display user information
                cout << "\n=== User ===\n\n";
                cout << "ID: " << u->id << endl;
                cout << "First Name: " << u->firstName << endl;
                cout << "Last Name: " << u->lastName << endl;
                cout << "Email Address: " << u->emailAddress << endl;
                cout << "Account Type: " << int(u->type) << endl;
                cout << "Date Of Birth: " << u->dateOfBirth << endl;
                cout << "Gender: " << User::resolveGender(u->gender) << endl;
                cout << "Home Address: " << u->homeAddress << endl;

                // If type is a teacher or student, it will have a class ID
                if (u->type == Type::Teacher || u->type == Type::Student) {
                    cout << "\n=== Class ===\n\n";

                    // Get the class ID depending on type
                    string classId = "";
                    if (u->type == Type::Teacher) {
                        auto d = dynamic_cast<Teacher*>(u);
                        classId = d->classId;
                    }
                    else {
                        auto d = dynamic_cast<Student*>(u);
                        classId = d->classId;
                    }

                    // Loop over each class and find this users class
                    for (auto c : database->classes) {
                        if (c->id != classId) continue;

                        cout << "ID: " << c->id << endl;
                        cout << "Year Level: " << c->yearLevel << endl;

                        // If user is a teacher, stop here
                        if (u->type == Type::Teacher) break;

                        // Loop over each user and display the teachers information
                        for (auto u2 : database->users) {
                            if (u2->type != Type::Teacher) continue;
                            auto t = dynamic_cast<Teacher*>(u2);
                            if (t->classId != classId) continue;

                            cout << "Teacher ID: " << t->id << endl;
                            cout << "Teacher First Name: " << t->firstName << endl;
                            cout << "Teacher Last Name: " << t->lastName << endl;
                            cout << "Teacher Gender: " << User::resolveGender(t->gender) << endl;
                            cout << "Teacher Email: " << t->emailAddress << endl;
                            break;
                        }
                    }
                }

                // If type is student, it will have guardians
                if (u->type == Type::Student) {
                    cout << "\n=== Guardians ===\n";

                    // Loop over each guardian
                    for (auto u2 : database->users) {
                        if (u2->type != Type::Guardian) continue;
                        auto g = dynamic_cast<Guardian*>(u2);

                        int index = 1;
                        // If the guardian is the students guardian, display their information
                        if (find(g->studentIds.begin(), g->studentIds.end(), u->id) != g->studentIds.end()) {
                            cout << "\n# Guardian " << index++ << endl;
                            cout << "ID: " << g->id << endl;
                            cout << "First Name: " << g->firstName << endl;
                            cout << "Last Name: " << g->lastName << endl;
                            cout << "Date Of Birth: " << g->dateOfBirth << endl;
                            cout << "Gender: " << User::resolveGender(g->gender) << endl;
                            cout << "Email Address: " << g->emailAddress << endl;
                            cout << "Contact Number: " << g->contactNumber << endl;
                            cout << "Home Address: " << g->homeAddress << endl;
                        }
                    }
                }

                if (u->type == Type::Guardian) {
                    cout << "\n=== Students ===\n";
                    auto g = dynamic_cast<Guardian*>(u);

                    // Loop over each student
                    for (auto u2 : database->users) {
                        if (u2->type != Type::Student) continue;
                        auto s = dynamic_cast<Student*>(u2);
                        
                        int index = 1;
                        // If student is the guardians student, display their information
                        if (find(g->studentIds.begin(), g->studentIds.end(), u2->id) != g->studentIds.end()) {
                            cout << "\n# Student " << index++ << endl;
                            cout << "ID: " << s->id << endl;
                            cout << "First Name: " << s->firstName << endl;
                            cout << "Last Name: " << s->lastName << endl;
                            cout << "Email Address: " << s->emailAddress << endl;
                            cout << "Account Type: " << int(s->type) << endl;
                            cout << "Date Of Birth: " << s->dateOfBirth << endl;
                            cout << "Gender: " << User::resolveGender(s->gender) << endl;
                            cout << "Home Address: " << s->homeAddress << endl;
                            cout << "Class ID: " << s->classId << endl;
                        }
                    }
                }

                cout << endl;
                Util::pauseProgram();
                return true;
            }

            cout << "\nNo user found for query!\n";
            Util::pauseProgram();
        }
        
        else if (option == 3) { // Create User
            string id = Database::generateId();
            
            cout << "===== Create User =====\n\n";

            cout << "Enter user type.\n";
            int typeInt = Menu::runMiniMenu({ "Admin", "Teacher", "Guardian", "Student" });
            Type type = User::resolveType(typeInt);
                
            cout << "Enter first name.\n";
            string fName = Util::requestString();

            cout << "Enter last name.\n";
            string lName = Util::requestString();

            cout << "Enter date of birth.\n";
            string dob = Util::requestString();

            cout << "Enter gender.\n";
            int gender = Menu::runMiniMenu({ "Male", "Female" });

            cout << "Enter contact number.\n";
            string cNumber = Util::requestString();
            
            cout << "Enter home address.\n";
            string hAddress = Util::requestString();
            
            cout << "Enter email address.\n";
            string eAddress = Util::requestString();
            
            cout << "Enter password.\n";
            string password = Util::requestString();
            
            User user(id, fName, lName, dob, gender, cNumber, hAddress, eAddress, password);
            
            // Different types require different properties
            if (type == Type::Admin) {
                Admin* u = new Admin(user);
                database->users.push_back(u);
            }
            else if (type == Type::Teacher) {
                cout << "Enter classroom ID.\n";
                string cId = Util::requestString();
                
                Teacher* u = new Teacher(user, cId);
                database->users.push_back(u);
            }
            else if (type == Type::Guardian) {
                // TODO: Add ability to add multiple children
                cout << "Enter child ID.\n";
                string cId = Util::requestString();
                
                Guardian* u = new Guardian(user, { cId });
                database->users.push_back(u);
            }
            else if (type == Type::Student) {
                cout << "Enter classroom ID.\n";
                string cId = Util::requestString();
                
                Student* u = new Student(user, cId);
                database->users.push_back(u);
            }

            database->save();
            cout << "\nCreated user with the ID: " << id << endl;
            Util::pauseProgram();
        }
        
        else if (option == 4) { // List Classes
            cout << "===== List Of Classes =====\n\n";
            cout << "ID - Year Level\n";

            // Loop over each class and display its information
            for (auto c : database->classes) {
                cout << c->id << " - " << c->yearLevel << endl;
            }

            cout << endl;
            Util::pauseProgram();
        }
        
        else if (option == 5) { // View Class
            cout << "===== View Class =====\n\n";

            cout << "Enter class ID to search for.\n";
            string id = Util::requestString();

            for (auto c : database->classes) {
                if (c->id == id) {
                    cout << "\n=== Class ===\n\n";
                    cout << "ID: " << c->id << endl;
                    cout << "Year Level: " << c->id << endl;

                    Teacher* teacher = {};
                    vector<Student*> students = {};
                    
                    // Find the teacher and students of this class
                    for (auto u : database->users) {
                        if (u->type == Type::Student) {
                            auto s = dynamic_cast<Student*>(u);
                            if (s->classId == c->id) {
                                students.push_back(s);
                            }
                        }
                        else if (u->type == Type::Teacher) {
                            auto t = dynamic_cast<Teacher*>(u);
                            if (t->classId == c->id) {
                                teacher = t;
                            }
                        }
                    }

                    // Print the teacher information if it exists
                    if (teacher != NULL) {
                        cout << "\n=== Teacher ===\n\n";
                        cout << "ID: " << teacher->id << endl;
                        cout << "First Name: " << teacher->firstName << endl;
                        cout << "Last Name: " << teacher->lastName << endl;
                        cout << "Email: " << teacher->emailAddress << endl;
                    }

                    // Loop over each student and print their information
                    cout << "\n=== Students ===\n\n";
                    cout << "ID - Name\n";
                    for (auto s : students) {
                        cout << s->id << " - "
                            << s->firstName + " " + s->lastName
                            << endl;
                    }
                }
            }

            cout << endl;
            Util::pauseProgram();
        }
        
        else if (option == 6) { // Create Class
            cout << "===== Create Class =====\n\n";
            
            cout << "Enter year level.\n";
            int yLevel = Util::requestInteger(0, 13);

            string id = Database::generateId();
            Class* xlass = new Class(id, yLevel);
            database->classes.push_back(xlass);

            database->save();
            cout << "\nCreated class with the ID: " << id << endl;
            Util::pauseProgram();
        }
        
        else if (option == 7) { // Exit
            return false;
        }
        
        return true;
    }
};
