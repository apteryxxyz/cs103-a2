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
            cout << "Account Type - ID - Name \n";

            // Loop over each user and display their information
            for (int i = 0; i < database->users.size(); i++)
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
        { // Create Report

            // Grade grade = Report::resolveGrade(gradeInt);

            cout << "===== Create Report =====\n\n";

            cout << "Enter teachers note.\n";
            string t = Util::requestString();

            cout << "Enter principles note.\n";
            string p = Util::requestString();

            cout << "Enter your attendance.\n";
            int a = Util::requestInteger(0, 13);

            cout << "Enter your Subject.\n";
            int subInt = Menu::runMiniMenu({"English", "Arts", "Health", "Languages", "Mathematics", "Science, SocialStudies", "Technology"});
            Subject subject = Report::resolveSubject(subInt);

            cout << "Select a Grade below.\n";
            int gradeInt = Menu::runMiniMenu({"Excellence", "Merit", "Achieved", "Not Achieved"});
            Grade grade = Report::resolveGrade(gradeInt);

            string id = Database::generateId();
            // Report *report = new Report(string s, string t, string p, int a, vector<SubjectReport> s);

            Report *x = new Report(id, t, p, a, {
                                                    {Subject::Health, Grade::Achieved, "Well Done"},

                                                });
            database->reports.push_back(x);
            // database->reports.push_back(x);

            database->save();
            cout << "\nCreated class with the ID: " << id << endl;
            Util::pauseProgram();
        }

        else if (option == 3)

        { // View Reports
            int userGrades;
            cout << "===== View Reports =====\n\n";
            cout << "ID - Teachers Note - Principles Note - Attendance \n";

            // int userGrades, mySubject;
            // string schoolGrades;

            // enum myGrades
            // {
            //     Excellence = 1,
            //     Merit = 2,
            //     Achieved = 3,
            //     NotAchieved = 4
            // };

            // Loop over each user and display their information
            for (int i = 0; i < database->reports.size(); i++)
            {
                auto s = database->reports[i];
                // auto u = database->subjects[i];
                cout << s->toString()
                     << endl;

                cout << endl;
                Util::pauseProgram();
            }
        }

        else if (option == 8)
        { // Exit
            return false;
        }

        return true;
    }
};