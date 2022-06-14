This markdown file is intended to explain how to use all the code written in this repository.

# Database

The `Database` class (located at `Database.h`) is the handler for all user, class, and report storing.
It has 3 main properties and 3 main methods (functions) that will be mentioned here.

Firstly, the properties are `<database>.users`, `<database>.classes` and `<database>.reports`, which are all **vectors** of **pointers** to their respective objects (To access a property on the object using the pointer, you can do `(*ptr).property` or `ptr->property`, better examples below).

Next are the 3 methods, one of which is static.
`<database>.load()`, this method will parse all the data from the files used as a database, it will store all its data in the vectors mentioned above.
`<database>.save()`, will take all the objects from the vectors, convert them to strings and write them to the files.
`Database::generateId()` (static method), will generate a random unique ID intended to be used for users and classes, more on this will be mentioned in the [Users](#users) section.

`<database>.load()` should be used at the very start of the program, and `<database>.save()` should be used after every push to a database vector.

If you wanted to loop over all of objects in any of the vectors, you could do the following:
```cpp
for (auto u : users) {
    // u is a pointer to a User object
}
```
In the case of users, `u` will always have the type of `User` which means you wouldn't be able to access, for example, the `classId` property of a teacher. So in order to do this, you must use `dynamic_cast`.
```cpp
for (auto u : users) {
    if (u->type == Type::Teacher) {
        auto t = dynamic_cast<Teacher*>(u);
        cout << t->classId << endl;
    }
}
```

# Users

The `User` class (located at `User.h`) is the base user class that all other user classes will inherit from. Those are `Admin` (`Admin.h`), `Teacher` (`Teacher.h`), `Guardian` (`Guardian.h`) and `Student` (`Student.h`). These classes will be referred to as "extended classes" in this section.

## Creating users

Some notes about these classes:
- Base `User` class objects should **never** be pushed to the `<database>.users` vector.
- Extended classes **must always** be created using the `new` keyword.
- The first parameter of all extended classes is a `User` object.

Some examples:
```cpp
string id = Database::generateId();
User user(id, "John", "Doe", "22/11/1976", 1, "022 222 2222", "10 Downing Street", "john@mail.com", "password");

Admin* admin = new Admin(user);
Teacher* teacher = new Teacher(user, "class id");
Guardian* guardian = new Guardian(user, { "child id 1", "child id 2" });
Student* student = new Student(user, "class id");
```

Now for some explaianation of the parameters (in order);
- `User`, user ID, first name, last name, date of birth, gender, contact number, home address, email address (used for login), password.
- `Admin` user object.
- `Teacher`, user object, class ID.
- `Guardian`, user object, vector of student IDs.
- `Student`, user object, class ID.

## User enums

### Type
- Base
- Admin
- Teacher
- Guardian
- Student

## User properties

### Base `User`:

- type: `Type` enum, will be `Admin`, `Teacher`, `Guardian` or `Student`.
- id: `string` user ID.
- firstName: `string` user first name.
- lastName: `string` user last name.
- dateOfBirth: `string` user date of birth, in the format of DD/MM/YYYY.
- gender: `int` 0 = not known, 1 = male, 2 = female
- contactNumber: `string` contact number for this person.
- homeAddress: `string` home address for this user.
- emailAddress: `string` email address used for login.
- password: `string` password used for login.

### `Teacher`

- classId: `string` ID of the class this teacher teaches.

### `Guardian`

- studentIds: `vector<string>` vector of student IDs.

### `Student`

- classId: `string` ID of the class this student is in.

## Modifying users

Because we are using pointers in the database vectors, you should be able to directly modify the properties of the objects in the vectors.

# Classes & Reports

The classes `Class` and `Report` work almost exactly the same as the users. Classes are stored in the `<database>.classes` vector, and reports are stored in the `<database>.reports` vector.

```cpp
Report* report = new Report("student id", "teachers note", "principal note", 100, {
    { Subject::English, Grade::Merit, "subject note" },
    { Subject::Arts, Grade::Excellence, "subject note" },
});

string id = Database::generateId();
Class* xlass = new Class(id, 5);
// 'class' is a keyword in c++, so here we use 'xlass' instead.
```

## Report enums

### Subject
- Unknown
- English
- Arts
- Health
- Languages
- Mathematics
- Science
- SocialStudies
- Technology

### Grade
- Unknown
- Excellence
- Merit
- Achieved
- NotAchieved

## Class, Report, SubjectReport properties

### Class

- id: `string` class ID.
- yearLevel: `int` year level of the class.

### Report

- studentId: `string` ID of the student this report is for.
- teacherNote: `string` note from the students teacher.
- principalNote: `string` note from the principal.
- attendance: `float` attendance percentage.
- subjects: `vector<SubjectReport>` vector of subject reports.

### SubjectReport

- subject: `Subject` subject this report is for.
- grade: `Grade` this subjects grade.
- note: `string` a note for this subject.

# Menu

The `Menu` class is intended to be used as a base class for all other menus. When you are creating a menu, you should create a new class that inherits from `Menu`. Your class **must** have a constructor that sets the `header` and `options` properties of the menu. The `header` is the title of the menu, this can be empty. `options` must be a vector of strings, each string being an option for the menu.

Your menu **must** also have a `handleOption` method, where the first parameter is a `int` representing the option selected. This method should return a `bool` representing whether the menu should be displayed again when the method ends.

The `Menu` class will **automatically** handle the displaying of the menu and taking of the users input, including vefifying that it is a valid.

```cpp
class MyMenu : public Menu {
public:
    MyMenu() {
        header = "Welcome to my menu!\n";
        options = { "Option 1", "Option 2", "Option 3" };
    }

    bool handleOption(int option) {
        if (option == 1) {
            cout << "Selected option 1!\n";
        } else if (option == 2) {
            cout << "Selected option 2!\n";
        } else if (option == 3) {
            cout << "Selected option 3!\n";
        }

        return true;
    }
}
```

Whenever you want to display the menu you must use the `<menu>.run()` method. It has two parameters; first is `bool clearBefore`, whether the screen should be cleared before the menu is displayed. Second is `bool clearAfter`, whether the screen should be cleared after an option is selected.

```cpp
MyMenu menu;
menu.run(true, true);
```

## Custom parameters

You can decide what parameters your menu needs. For example, say your menu needs access to the database, you could do the following (You should use pointers here).

```cpp
class MyMenu : public Menu {
private:
    Database* database;

public:
    MyMenu(Database* database) {
        this->database = database;
        ...
    }

    bool handleOption(int option) {
        ...
        int userCount = database->users.size();
        ...
    }
}
```

```cpp
MyMenu menu(database);
menu.run(true, true);
```

# Util

The `Util` class (located at `Util.h`) contains a number of useful (static) methods.

## `requestString`

This method will request a string from the user.

```cpp
cout << "What is your email?\n";
string email = Util::requestString();
```

## `requestInteger`

This method will request an integer from the user, it has two parameters, the first in the minimum value, the second is the maximum value.

```cpp
cout << "What is your age?\n";
int age = Util::requestInteger(0, 100);
```

## `requestFloat`

This method will request a float from the user, it has two parameters, the first in the minimum value, the second is the maximum value.

```cpp
cout << "What is your GPA?\n";
float gpa = Util::requestFloat(0, 10);
```

## `clearScreen`

This method is a cross platform way of clearing the console screen.

## `pauseProgram`

This method is a cross platform way of pausing the program.

135724