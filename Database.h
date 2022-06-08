#pragma once
#include <vector>
#include <sstream>
#include <fstream>
#include <variant>

#include "User.h"
#include "Admin.h"
#include "Teacher.h"
#include "Guardian.h"
#include "Student.h"

class Database {

public:
    vector<User*> users;

    ~Database() {
		// Clear the vectors to prevent memory leaks
        for (auto u : users) delete u;
        users.clear();
    }

    // Generate a random ID to use
    static string generateId() {
        string obj;
        uint32_t rawId = reinterpret_cast<uint32_t>(&obj);
        return to_string(rawId);
    }

    // Open and parse the users.csv file
    // Add each student, teacher, guardian, and admin to the users vector
    void loadUsers() {
        fstream userDb("users.csv", ios::in);

		// Loop over each line in the file
        string line;
        while (getline(userDb, line)) {
            istringstream linestream(line);
            string item;

            getline(linestream, item, ',');
            // If line is empty, skip it
            if (item == "") continue;
            Type type = User::resolveType(stoi(item));
            getline(linestream, item, ',');
            string id = item;
            getline(linestream, item, ',');
            string fName = item;
            getline(linestream, item, ',');
            string lName = item;
            getline(linestream, item, ',');
            string dob = item;
            getline(linestream, item, ',');
            int gender = stoi(item);
            getline(linestream, item, ',');
            string cNumber = item;
            getline(linestream, item, ',');
            string hAddress = item;
            getline(linestream, item, ',');
            string eAddress = item;
            getline(linestream, item, ',');
            string password = item;

            // Create the base user object and overwrite its ID
            User user(id, fName, lName, dob, gender, cNumber, hAddress, eAddress, password);

            // Every value on the line after the password
            // is specific to each account type
            if (type == Type::Admin) {
                Admin *admin = new Admin(user);
                users.push_back(admin);
            }
            if (type == Type::Teacher) {
                getline(linestream, item, ',');
                Teacher *teacher = new Teacher(user, item);
                users.push_back(teacher);
            }
            else if (type == Type::Guardian) {
                vector<string> studentIds = {};
                getline(linestream, item, ',');
                istringstream itemstream(item);

				// Student IDs are separated by a pipes
                while (getline(itemstream, item, '|')) {
                    studentIds.push_back(item);
                }

                Guardian *guardian = new Guardian(user, studentIds);
                users.push_back(guardian);
            }
            else if (type == Type::Student) {
                getline(linestream, item, ',');
                Student *student = new Student(user, item);
                users.push_back(student);
            }
        }
    }

    // Stringify the users vector and write it to the users.csv file
    void saveUsers() {
        ofstream userDb("users.csv", ios::trunc); // Trunc will overwrite exisitng content
        userDb << "";
        for (auto i = users.begin(); i != users.end(); i++) {
            userDb << (*i)->toString() << endl;
        }
    }
};
