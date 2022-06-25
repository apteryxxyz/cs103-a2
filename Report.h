#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>

using namespace std;

enum class Subject {
    Unknown,
    English,
    Arts,
    Health,
    Languages,
    Mathematics,
    Science,
    SocialStudies,
    Technology,
};

enum class Grade {
    Unknown,
    Excellence,
    Merit,
    Achieved,
    NotAchieved,
};

struct SubjectReport {
    Subject subject;
    Grade grade;
    string note;
};

class Report {
public:
    string studentId, teacherNote, principalNote;
    float attendance;
    vector<SubjectReport> subjects;

    Report(
        string s, string t, string p,
        float a, vector<SubjectReport> ss
    ) {
        studentId = s;
        teacherNote = t;
        principalNote = p;
        attendance = a;
        subjects = ss;
    }

    string toString() {
        // Convert the vector of subjects to a vector of strings
        vector<string> subs = {};
        for (auto s : subjects)
            subs.push_back(subjectToString(s));

        // Convert the vector of strings to a single string
        string str = "";
        for (auto s : subs)
            str += s + "|";
        str.pop_back();

        return studentId + '~' + teacherNote + '~' +
               principalNote + '~' + to_string(attendance) + '~' +
               str;
    }

    static Subject resolveSubject(int subInt) {
        if (subInt == 1) return Subject::English;
        if (subInt == 2) return Subject::Arts;
        if (subInt == 3) return Subject::Health;
        if (subInt == 4) return Subject::Languages;
        if (subInt == 5) return Subject::Mathematics;
        if (subInt == 6) return Subject::Science;
        if (subInt == 7) return Subject::SocialStudies;
        if (subInt == 8) return Subject::Technology;
        return Subject::Unknown;
    }

    static string resolveSubject(Subject sub) {
        if (sub == Subject::English) return "English";
        if (sub == Subject::Arts) return "Arts";
        if (sub == Subject::Health) return "Health";
        if (sub == Subject::Languages) return "Languages";
        if (sub == Subject::Mathematics) return "Mathematics";
        if (sub == Subject::Science) return "Science";
        if (sub == Subject::SocialStudies) return "Social Studies";
        if (sub == Subject::Technology) return "Technology";
        return "Unknown";
    }

    static Grade resolveGrade(int graInt) {
        if (graInt == 1) return Grade::Excellence;
        if (graInt == 2) return Grade::Merit;
        if (graInt == 3) return Grade::Achieved;
        if (graInt == 4) return Grade::NotAchieved;
        return Grade::Unknown;
    }

    static string resolveGrade(Grade gra) {
        if (gra == Grade::Excellence) return "Excellence";
        if (gra == Grade::Merit) return "Merit";
        if (gra == Grade::Achieved) return "Achieved";
        if (gra == Grade::NotAchieved) return "Not Achieved";
        return "Unknown";
    }

private:
    string subjectToString(SubjectReport sr) {
        return to_string(int(sr.subject)) + '^' +
            to_string(int(sr.grade)) + '^' +
            sr.note;
    }
};
