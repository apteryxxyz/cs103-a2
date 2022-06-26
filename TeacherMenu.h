#pragma once
#include "Menu.h"
#include "Database.h"
#include "Util.h"

using namespace std;

class TeacherMenu : public Menu {
private:
    Database* database;
    Teacher* teacher;

public:
    TeacherMenu(Database* database, User* user) {
        this->database = database;
        this->teacher = dynamic_cast<Teacher*>(user);
        header = "Welcome " + user->firstName + "! Select an option from below.\n";
        options = { "List Students", "View Student", "View Reports", "Create Report", "Logout" };
    }

    bool handleOption(int option) {
        if (option == 1) { // List Students
            cout << "===== List Students =====\n\n";

            cout << "ID - Name\n";
            // Loop over every user
            for (auto u : database->users) {
                // If user is not a student skip
                if (u->type != Type::Student) continue;
                auto s = dynamic_cast<Student*>(u);

                // If student is not in teachers class skip
                if (s->classId != teacher->classId) continue;

                // Print user information
                cout << s->id << " - " << s->firstName << " " << s->lastName << "\n";
            }

            cout << endl;
            Util::pauseProgram();
        }

        if (option == 2) { // View Student
            cout << "===== View Student =====\n\n";

            cout << "Enter student ID or email to search for.\n";
            string query = Util::requestString();

            // Loop over every user
            for (auto u : database->users) {
                // Skip if query does not equal ID or email
                if (u->id != query && u->emailAddress != query) continue;

                if (u->type != Type::Student) {
                    cout << "User is not a student.\n";
                    Util::pauseProgram();
                    return true;
                }
                auto s = dynamic_cast<Student*>(u);
                if (s->classId != teacher->classId) {
                    cout << "User is not in your class.\n";
                    Util::pauseProgram();
                    return true;
                }

                cout << "\n=== Student ===\n\n";
                cout << "ID: " << u->id << endl;
                cout << "First Name: " << u->firstName << endl;
                cout << "Last Name: " << u->lastName << endl;
                cout << "Email Address: " << u->emailAddress << endl;
                cout << "Date Of Birth: " << u->dateOfBirth << endl;
                cout << "Gender: " << User::resolveGender(u->gender) << endl;
                cout << "Home Address: " << u->homeAddress << endl;

                cout << "\n=== Guardians ===\n";

                // Loop over every user to find students guardians
                for (auto u2 : database->users) {
                    // If user is not a guardian skip
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

                cout << endl;
                Util::pauseProgram();
                return true;
            }

            cout << "\nNo user found for query!\n";
            Util::pauseProgram();
        }

        if (option == 3) { // View Reports
            cout << "===== View Reports =====\n\n";

            // Get the search query from the admin
            cout << "Enter ID or email to search reports for.\n";
            string query = Util::requestString();

            // Loop over each user to match query
            for (auto u : database->users) {
                // Skip if query does not equal ID or email
                if (u->id != query && u->emailAddress != query) continue;

                if (u->type != Type::Student) {
                    cout << "\nUser is not a student.\n";
                    Util::pauseProgram();
                    return true;
                }
				
                auto s = dynamic_cast<Student*>(u);
                if (s->classId != teacher->classId) {
                    cout << "\nUser is not in your class.\n";
                    Util::pauseProgram();
                    return true;
                }

                int index = 1;
                // Loop over each report and find the students
                for (auto r : database->reports) {
                    if (r->studentId != s->id) continue;

                    cout << "\nTeachers Note:\n" << r->teacherNote;
                    cout << "\nPrincipals Note:\n" << r->principalNote;
                    cout << "\n\n=== Subjects ===\n\n";

                    for (SubjectReport sub : r->subjects) {
                        cout << "Subject: " << Report::resolveSubject(sub.subject);
                        cout << "\nGrade: " << Report::resolveGrade(sub.grade);
                        cout << "\nNote: " << sub.note << endl;
                    }
                }

                cout << endl;
                Util::pauseProgram();
                return true;
            }

            cout << "\nNo user found for query!\n";
            Util::pauseProgram();
        }

        if (option == 4) { // Create Report
            cout << "===== Create Report =====\n\n";

            cout << "Enter a student ID or email to create report for.\n";
            string query = Util::requestString();

            // Loop over each user to match query
            for (auto u : database->users) {
                // Skip if query does not equal ID or email
                if (u->id != query && u->emailAddress != query) continue;

                if (u->type != Type::Student) {
                    cout << "\nUser is not a student!\n";
                    Util::pauseProgram();
                    return true;
                }

                auto s = dynamic_cast<Student*>(u);
                if (s->classId != teacher->classId) {
                    cout << "\nUser is not in your classroom!\n";
                    Util::pauseProgram();
                    return true;
                }

                cout << "\nEnter attendance percent.\n";
                float attend = Util::requestFloat(0, 100);

                cout << "Enter teachers note.\n";
                string tNote = Util::requestString();

                cout << "Enter principals note.\n";
                string pNote = Util::requestString();

                vector<SubjectReport> subReports = {};
                vector<Subject> subjects = {
                    Subject::English, Subject::Arts, Subject::Health,
                    Subject::Languages, Subject::Mathematics,
                    Subject::Science, Subject::SocialStudies,
                    Subject::Technology
                };

                for (auto s : subjects) {
                    SubjectReport sub = { s };
                    cout << "\n=== " << Report::resolveSubject(s) << " ===\n";

                    cout << "Select a grade.\n";
                    int graInt = Menu::runMiniMenu({ "Excellence", "Merit", "Achieved", "Not Achieved" });
                    sub.grade = Report::resolveGrade(graInt);

                    cout << "Enter a note.\n";
                    sub.note = Util::requestString();

                    subReports.push_back(sub);
                }

                Report* report = new Report(s->id, tNote, pNote, attend, subReports);

                database->reports.push_back(report);
                database->save();
                cout << "\nNew report created for " << s->firstName << " " << s->lastName << ".\n";
                Util::pauseProgram();
                return true;
            }

            cout << "User not found!\n";
            Util::pauseProgram();
            return true;
        }

        if (option == 5) { // Layout
            return false;
        }

        return true;
    }
};