
#pragma once
#include "Menu.h"
#include "Database.h"
#include "User.h"

class StudentMenu : public Menu {
private:
    Database* database;
    User* user;

public:
    StudentMenu(Database* database, User* user) {
        this->database = database;
        this->user = user;

        header = "Welcome " + user->firstName + ", please select an option below.\n";
        options = { "View Teacher", "View Reports", "Logout" };
    }

    bool handleOption(int option) {
        vector<Student*> students;
			
        if (user->type == Type::Student) {
            // If user is a student push self to students vector
            students.push_back(dynamic_cast<Student*>(user));
        }
        else if (user->type == Type::Guardian) {
            // If user is a guardian, push all their students to students vector
            auto g = dynamic_cast<Guardian*>(user);

            for (auto u : database->users) {
                if (
                    u->type == Type::Student &&
                    find(g->studentIds.begin(), g->studentIds.end(), u->id) != g->studentIds.end()
                    ) {
                    students.push_back(dynamic_cast<Student*>(u));
                }
            }
        }
		
        if (option == 1) { // View Teacher
			if (students.size() == 0) {
			    // If no students in vector, return
				cout << "You have no students.\n";
				return true;
			}

			// Loop over each student and print their teacher
            for (auto s : students) {
                cout << "=== " << s->firstName << "'s Teacher ===\n";

                for (auto u : database->users) {
                    if (u->type != Type::Teacher) continue;
                    auto t = dynamic_cast<Teacher*>(u);
                    if (s->classId != t->classId) continue;
					
					cout << "Name: " << u->firstName << " " << u->lastName;
					cout << "\nEmail: " << u->emailAddress;
					cout << "\nPhone: " << u->contactNumber << endl << endl;
				    break;
                }
            }

            Util::pauseProgram();
            return true;
        }

        if (option == 2) { // View Reports
            Student* student;

            if (students.size() == 0) {
                // If no students in vector, return
                cout << "You have no students.\n";
                return true;
            }
            else if (students.size() == 1) {
				// If only one student in vector, set student to that student
                student = students[0];
            }
            else {
				// If more than one student, ask user to select one
				cout << "Please select a student.\n";
				for (int i = 0; i < students.size(); i++) {
					cout << i + 1 << ") "
                        << students[i]->firstName
                        << " " << students[i]->lastName
                        << endl;
				}
                int studentId = Util::requestInteger(1, students.size());
				student = students[studentId - 1];
            }

			cout << "===== " << student->firstName << "'s Reports =====\n";

            // Loop over each report and find the students
            int index = 1;
            for (auto r : database->reports) {
                if (r->studentId != student->id) continue;

                cout << "\n=== Report #" << index++ << " ===\n";
                cout << "\nTeachers Note:\n" << r->teacherNote;
                cout << "\nPrincipals Note:\n" << r->principalNote;
                cout << "\n\n=== Subjects ===\n";

                for (SubjectReport sub : r->subjects) {
                    cout << "\nSubject: " << Report::resolveSubject(sub.subject);
                    cout << "\nGrade: " << Report::resolveGrade(sub.grade);
                    cout << "\nNote: " << sub.note << endl;
                }
            }
			
            cout << endl;
            Util::pauseProgram();
            return true;
        }
        
        if (option == 3) {
            return false;
        }

        return true;
    }
};
