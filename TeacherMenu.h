#pragma once
#include "Menu.h"
#include "Database.h"
#include "Util.h"

class TeacherMenu : public Menu
{
private:
    Database *database;

public:
    TeacherMenu(Database *database)
    {
        this->database = database;
        header = "Welcome to the Teacher menu, select an option from below!\n";
        options = {"View Students", "Create Student Reports", "View Reports", "Exit"};
    }

    bool handleOption(int option)
    {
        if (option == 1)
        { // View Students
            cout << "===== View Students =====\n\n";

            // Loop over each user and display their information
            for (int i = 0; i < database->users.size(); i++)
            {
                auto u = database->users[i];
                cout << "User Type: " << int(u->type) << endl;
                cout << "Student Id: " << u->id << endl;
                cout << "Student First Name: " << u->firstName << endl;
                cout << "Student Lastname: " << u->lastName << endl;
            }

            cout << endl;
            Util::pauseProgram();
        }

        else if (option == 2)
        { // Create Report

            // Grade grade = Report::resolveGrade(gradeInt);

            cout << "===== Create Report =====\n\n";

            cout << "Enter teachers note.\n";
            string t = Util::requestString();

            cout << "Enter principles note.\n";
            string p = Util::requestString();

            cout << "Enter your attendance.\n";
            int a = Util::requestInteger(0, 13);

            cout << "Enter note.\n";
            string sr = Util::requestString();

            cout << "Enter your Subject.\n";
            int subInt = Menu::runMiniMenu({"English", "Arts", "Health", "Languages", "Mathematics", "Science", "SocialStudies", "Technology"});
            // Subject subject = Report::resolveSubject(subInt);
            // string subStr = Report::resolveSubject(subject);
            // cout << "Subject is " << subStr << endl;
            // int gr = Util::requestInteger(0, 13);

            cout << "Select a Grade below.\n";
            int graInt = Menu::runMiniMenu({"Excellence", "Merit", "Achieved", "NotAchieved"});
            Grade grade = Report::resolveGrade(graInt);
            string gradeStr = Report::resolveGrade(grade);
            cout << "Grade is " << gradeStr << endl;

            string id = Database::generateId();
            // Report *report = new Report(string s, string t, string p, int a, vector<SubjectReport> s);
            Report *x = new Report(id, t, p, a, {
                                                    {Subject::Health, Grade::Achieved, sr},

                                                });
            database->reports.push_back(x);
            // database->reports.push_back(x);

            database->save();
            cout << "\nCreated class with the ID: " << id << endl;
            Util::pauseProgram();
        }

        else if (option == 3)

        { // View Reports
            cout << "===== View Reports =====\n\n";
            // cout << "ID - Teachers Note - Principles Note - Attendance \n";

            // int userGrades, mySubject;
            // string schoolGrades;

            // Loop over each user and display their information
            for (int i = 0; i < database->reports.size(); i++)
            {
                auto r = database->reports[i];
                cout << "Student ID: " << r->studentId << endl;
                cout << "Teachers Note: " << r->teacherNote << endl;
                cout << "Principles Note: " << r->principalNote << endl;

                for (auto s : r->subjects)
                {
                    cout << "Subject: " << Report::resolveSubject(s.subject) << endl;
                    cout << "Grade: " << Report::resolveGrade(s.grade) << endl;
                    cout << "Note: " << s.note << endl;
                }
            }

            cout << endl;
            Util::pauseProgram();
        }

        else if (option == 4)
        { // Exit
            return false;
        }

        return true;
    }
};
