#pragma once
#include "Menu.h"
#include "Database.h"
#include "Util.h"
#include "TeacherMenu.h"

class AdminMenu : public Menu
{
private:
    Database *database;

public:
    AdminMenu(Database *database)
    {
        this->database = database;
        header = "Welcome to the admin menu, select an option from below!\n";
        options = {"List Users", "View User", "Create User", "List Classes", "View Class", "Create Class", "Teacher Menu", "Exit"};
    }

    bool handleOption(int option)
    {
        if (option == 1)
        { // List Users
            cout << "===== List Of Users =====\n\n";
            cout << "Account Type - ID - Name \n";

            // Loop over each user and display their information
            for (int i = 0; i < database->students.size(); i++)
            {
                auto u = database->users[i];
                cout << int(u->type) << " - "
                     << u->id << " - "
                     << u->firstName + " " + u->lastName << endl;
            }

            cout << endl;
            Util::pauseProgram();
        }

        else if (option == 2)
        { // View User
            cout << "===== View User =====\n\n";

            // Get the search query from the admin
            cout << "Enter ID or email to search for.\n";
            string query = Util::requestString();

            // Loop over every user in the database and
            // check if the query matches their id or email
            for (auto u : database->users)
            {
                if (u->id != query && u->emailAddress != query)
                    continue;
                cout << "\n===== User Information =====\n";
                cout << "ID: " << u->id << endl;
                cout << "First Name: " << u->firstName << endl;
                cout << "Last Name: " << u->lastName << endl;
                cout << "Email Address: " << u->emailAddress << endl;
                cout << "Account Type: " << int(u->type) << endl;
                cout << "Date Of Birth: " << u->dateOfBirth << endl;
                cout << "Gender: " << u->gender << endl;
                cout << "Home Address: " << u->homeAddress << endl;

                // If type is a teacher or student, it will have a class ID
                if (u->type == Type::Teacher || u->type == Type::Student)
                {
                    cout << "\n===== Class Information =====\n";

                    // Get the class ID depending on type
                    string classId = "";
                    if (u->type == Type::Teacher)
                    {
                        auto d = dynamic_cast<Teacher *>(u);
                        classId = d->classId;
                    }
                    else
                    {
                        auto d = dynamic_cast<Student *>(u);
                        classId = d->classId;
                    }

                    // Loop over each class and find this users
                    for (auto c : database->classes)
                    {
                        if (c->id != classId)
                            continue;

                        cout << "ID: " << c->id << endl;
                        cout << "Year Level: " << c->yearLevel << endl;

                        if (u->type == Type::Teacher)
                            break;

                        for (auto u2 : database->users)
                        {
                            if (u2->type != Type::Teacher)
                                continue;
                            auto t = dynamic_cast<Teacher *>(u2);
                            if (t->classId != classId)
                                continue;

                            cout << "Teacher ID: " << t->id << endl;
                            cout << "Teacher First Name: " << t->firstName << endl;
                            cout << "Teacher Last Name: " << t->lastName << endl;
                            cout << "Teacher Email: " << t->emailAddress << endl;
                            break;
                        }
                    }
                }

                if (u->type == Type::Student)
                {
                    cout << "\n===== Guardian Information =====\n";

                    for (auto u2 : database->users)
                    {
                        if (u2->type == Type::Guardian)
                            continue;
                        auto g = dynamic_cast<Guardian *>(u2);

                        for (int i = 0; i < g->studentIds.size(); i++)
                        {
                            if (g->studentIds[i] == u->id)
                            {
                                cout << "\n# Guardian " << i << endl;
                                cout << "ID: " << g->id << endl;
                                cout << "First Name: " << g->firstName << endl;
                                cout << "Last Name: " << g->lastName << endl;
                                cout << "Email Address: " << g->emailAddress << endl;
                                cout << "Contact Number: " << g->contactNumber << endl;
                                cout << "Home Address: " << g->homeAddress << endl;
                            }
                        }
                    }
                }

                if (u->id == query || u->emailAddress == query)
                {
                    // If type is student, it will have guardians
                    if (u->type == Type::Student)
                    {

                        for (auto u : database->users)
                        {
                            if (u->type != Type::Guardian)
                                continue;
                            auto g = dynamic_cast<Guardian *>(u);

                            for (int i = 0; i < g->studentIds.size(); i++)
                            {
                                if (g->studentIds[i] == u->id)
                                {
                                    cout << "\n# Guardian " << i << endl;
                                    cout << "ID: " << g->id << endl;
                                    cout << "First Name: " << g->firstName << endl;
                                    cout << "Last Name: " << g->lastName << endl;
                                    cout << "Email Address: " << g->emailAddress << endl;
                                    cout << "Contact Number: " << g->contactNumber << endl;
                                    cout << "Home Address: " << g->homeAddress << endl;
                                }
                            }
                        }
                    }

                    Util::pauseProgram();
                    return true;
                }
            }

            cout << "\nNo user found for query!\n";
            Util::pauseProgram();
        }

        else if (option == 3)
        { // Create User
            string id = Database::generateId();

            cout << "===== Create User =====\n\n";

            cout << "Enter user type.\n";
            int typeInt = Menu::runMiniMenu({"Admin", "Teacher", "Guardian", "Student"});
            Type type = User::resolveType(typeInt);

            cout << "Enter first name.\n";
            string fName = Util::requestString();

            cout << "Enter last name.\n";
            string lName = Util::requestString();

            cout << "Enter date of birth.\n";
            string dob = Util::requestString();

            cout << "Enter gender.\n";
            int gender = Menu::runMiniMenu({"Male", "Female"});

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
            if (type == Type::Admin)
            {
                Admin *u = new Admin(user);
                database->users.push_back(u);
            }
            else if (type == Type::Teacher)
            {
                cout << "Enter classroom ID.\n";
                string cId = Util::requestString();

                Teacher *u = new Teacher(user, cId);
                database->users.push_back(u);
            }
            else if (type == Type::Guardian)
            {
                // TODO: Add ability to add multiple children
                cout << "Enter child ID.\n";
                string cId = Util::requestString();

                Guardian *u = new Guardian(user, {cId});
                database->users.push_back(u);
            }
            else if (type == Type::Student)
            {
                cout << "Enter classroom ID.\n";
                string cId = Util::requestString();

                Student *u = new Student(user, cId);
                database->users.push_back(u);
            }

            database->save();
            cout << "\nCreated user with the ID: " << id << endl;
            Util::pauseProgram();
        }

        else if (option == 4)
        { // List Classes
            cout << "===== List Of Classes =====\n\n";
            cout << "ID - Year Level\n";

            // Loop over each class and display its information
            for (auto c : database->classes)
            {
                cout << c->id << " - " << c->yearLevel << endl;
            }

            cout << endl;
            Util::pauseProgram();
        }

        else if (option == 5)
        { // View Class
            cout << "===== View Class =====\n\n";

            cout << "Enter class ID to search for.\n";
            string id = Util::requestString();

            for (auto c : database->classes)
            {
                if (c->id == id)
                {
                    cout << "\n===== Class Information =====\n\n";
                    cout << "ID: " << c->id << endl;
                    cout << "Year Level: " << c->id << endl;

                    // Find the teacher of this class
                    for (auto u : database->users)
                    {
                        if (u->type != Type::Teacher)
                            continue;
                        auto t = dynamic_cast<Teacher *>(u);
                        if (t->classId != id)
                            continue;

                        cout << "Teacher ID: " << t->id << endl;
                        cout << "Teacher First Name: " << t->firstName << endl;
                        cout << "Teacher Last Name: " << t->lastName << endl;
                        cout << "Teacher Email: " << t->emailAddress << endl;
                    }
                }
            }

            cout << endl;
            Util::pauseProgram();
        }

        else if (option == 6)
        { // Create Class
            cout << "===== Create Class =====\n\n";

            cout << "Enter year level.\n";
            int yLevel = Util::requestInteger(0, 13);

            string id = Database::generateId();
            Class *xlass = new Class(id, yLevel);
            database->classes.push_back(xlass);

            database->save();
            cout << "\nCreated class with the ID: " << id << endl;
            Util::pauseProgram();
        }

        else if (option == 7)
        // Start Teacher Menu
        {
            Database db;
            db.load();
            TeacherMenu menu(&db);
            menu.run();
        }
        // End Teacher Menu

        else if (option == 8)
        { // Exit
            return false;
        }

        return true;
    }
};