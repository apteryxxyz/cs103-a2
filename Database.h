#pragma once
#include <vector>
#include <sstream>
#include <fstream>

#include "User.h"
#include "Admin.h"
#include "Teacher.h"
#include "Guardian.h"
#include "Student.h"

#include "Class.h"
#include "Report.h"

class Database {
public:
    vector<User*> users;
    vector<Class*> classes;
    vector<Report*> reports;

    Database() {
        srand(time(NULL));
    }

    ~Database() {
        // Clear the vectors to prevent memory leaks
        for (auto u : users) delete u;
        users.clear();
        for (auto c : classes) delete c;
        classes.clear();
        for (auto r : reports) delete r;
        reports.clear();
    }

    // Generate a random ID to use
    static string generateId() {
        int num = rand() * rand();
        return to_string(num).substr(0, 6);
    }

    // Open and parse the users.csv file
    // Add each student, teacher, guardian, and admin to the users vector
    void loadUsers() {
        fstream userDb("_users.data", ios::in);

        // Loop over each line in the file
        string line;
        while (getline(userDb, line)) {
            istringstream linestream(line);
            string item;

            getline(linestream, item, '~');
            // If line is empty, skip it
            if (item == "") continue;
            Type type = User::resolveType(stoi(item));
            getline(linestream, item, '~');
            string id = item;
            getline(linestream, item, '~');
            string fName = item;
            getline(linestream, item, '~');
            string lName = item;
            getline(linestream, item, '~');
            string dob = item;
            getline(linestream, item, '~');
            int gender = stoi(item);
            getline(linestream, item, '~');
            string cNumber = item;
            getline(linestream, item, '~');
            string hAddress = item;
            getline(linestream, item, '~');
            string eAddress = item;
            getline(linestream, item, '~');
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
                getline(linestream, item, '~');
                Teacher *teacher = new Teacher(user, item);
                users.push_back(teacher);
            }
            else if (type == Type::Guardian) {
                vector<string> studentIds = {};
                getline(linestream, item, '~');
                istringstream itemstream(item);

                // Student IDs are separated by a pipes
                while (getline(itemstream, item, '|')) {
                    studentIds.push_back(item);
                }

                Guardian *guardian = new Guardian(user, studentIds);
                users.push_back(guardian);
            }
            else if (type == Type::Student) {
                getline(linestream, item, '~');
                Student *student = new Student(user, item);
                users.push_back(student);
            }
        }
		
        userDb.close();
    }

    // Stringify the users vector and write it to the users.csv file
    void saveUsers() {
        ofstream userDb("_users.data", ios::trunc); // Trunc will overwrite exisitng content
        userDb << "";
        for (auto i = users.begin(); i != users.end(); i++) {
            userDb << (*i)->toString() << endl;
        }
        userDb.close();
    }

    // Open and parse the classes.csv file
    // Add class to the classes vector
    void loadClasses() {
        fstream classDb("_classes.data", ios::in);

        string line;
        while (getline(classDb, line)) {
			istringstream linestream(line);
			string item;

			getline(linestream, item, '~');
			// If line is empty, skip it
            if (item == "") continue;
			string id = item;
			getline(linestream, item, '~');
			int yLevel = stoi(item);

            Class* xlass = new Class(id, yLevel);
            classes.push_back(xlass);
        }
		
        classDb.close();
    }

    // Stringify the classes vector and write it to the classes.csv file
    void saveClasses() {
        ofstream classDb("_classes.data", ios::trunc);
        classDb << "";
        for (auto i = classes.begin(); i != classes.end(); i++) {
            classDb << (*i)->toString() << endl;
        }
        classDb.close();
    }

    // Open and parse the reports.csv file
    // Add class to the reports vector
    void loadReports() {
        fstream reportDb("_reports.data", ios::in);

        string line;
        while (getline(reportDb, line)) {
            istringstream linestream(line);
            string item;

            getline(linestream, item, '~');
            // If line is empty, skip it
            if (item == "") continue;
            string sId = item;
            getline(linestream, item, '~');
            string tNote = item;
            getline(linestream, item, '~');
            string pNote = item;
            getline(linestream, item, '~');
            int attendance = stoi(item);

            vector<string> subjectStrings;
            vector<SubjectReport> subjects;

            getline(linestream, item, '~');
            istringstream itemstream(item);
			
            while (getline(itemstream, item, '|')) {
                istringstream propstream(item);
                string prop;
				
                getline(propstream, prop, '^');
                Subject subject = Report::resolveSubject(stoi(prop));
                getline(propstream, prop, '^');
                Grade grade = Report::resolveGrade(stoi(prop));
                getline(propstream, prop, '^');
                string note = prop;

                SubjectReport sr = { subject, grade, note };
                subjects.push_back(sr);
            }
			
            Report* report = new Report(sId, tNote, pNote, attendance, subjects);
            reports.push_back(report);
        }
        
        reportDb.close();
    }

    // Stringify the reports vector and write it to the reports.csv file
    void saveReports() {
        ofstream reportDb("_reports.data", ios::trunc);
        reportDb << "";
        for (auto i = reports.begin(); i != reports.end(); i++) {
            reportDb << (*i)->toString() << endl;
        }
        reportDb.close();
    }

    // Load all csv files
    void load() {
        loadUsers();
        loadClasses();
        loadReports();
    }

    // Save all vectors
    void save() {
        saveUsers();
        saveClasses();
        saveReports();
    }
};
