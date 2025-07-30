#include <iostream>
#include <string>
using namespace std;
class Department;  
class FacultyMember;  
class Student;  
class Course;  
class University {
public:
    Department* departments[10];
    int departmentCount;
    University() : departmentCount(0) {}
    void addDepartment(Department* department) {
        if (departmentCount < 10) {
            departments[departmentCount++] = department;
        }
    }
    void display() {
        cout << "University Departments: " << endl;
        for (int i = 0; i < departmentCount; ++i) {
            Department* dept = departments[i];
            cout << "Department: " << dept->name << ", Chairperson: " << dept->chairperson << endl;

            cout << "Courses offered: " << endl;
            for (int j = 0; j < dept->courseCount; ++j) {
                Course* course = dept->courses[j];
                cout << "Course: " << course->name << ", Number: " << course->courseNumber << ", Credits: " << course->credits << endl;
            }

            cout << "Faculty Members: " << endl;
            for (int j = 0; j < dept->facultyCount; ++j) {
                FacultyMember* faculty = dept->facultyMembers[j];
                cout << "Name: " << faculty->name << ", Rank: " << faculty->rank << ", Office: " << faculty->officeLocation << endl;
                cout << "Courses taught: " << endl;
                for (int k = 0; k < faculty->courseCount; ++k) {
                    cout << "Course: " << faculty->courses[k]->name << endl;
                }
            }

            cout << "Students: " << endl;
            for (int j = 0; j < dept->studentCount; ++j) {
                Student* student = dept->students[j];
                cout << "Name: " << student->name << ", ID: " << student->studentID << ", GPA: " << student->GPA << endl;
                cout << "Courses enrolled: " << endl;
                for (int k = 0; k < student->courseCount; ++k) {
                    cout << "Course: " << student->courses[k]->name << endl;
                }
            }
        }
    }
};

class Department {
public:
    string name;
    string chairperson;
    FacultyMember* facultyMembers[10];
    Student* students[10];
    Course* courses[10];
    int facultyCount;
    int studentCount;
    int courseCount;

    Department(const string& name, const string& chairperson)
        : name(name), chairperson(chairperson), facultyCount(0), studentCount(0), courseCount(0) {}

    void addFacultyMember(FacultyMember* facultyMember) {
        if (facultyCount < 10) {
            facultyMembers[facultyCount++] = facultyMember;
        }
    }

    void addStudent(Student* student) {
        if (studentCount < 10) {
            students[studentCount++] = student;
        }
    }

    void addCourse(Course* course) {
        if (courseCount < 10) {
            courses[courseCount++] = course;
        }
    }
};

class FacultyMember {
public:
    string name;
    string rank;
    string officeLocation;
    Course* courses[10];
    int courseCount;

    FacultyMember(const string& name, const string& rank, const string& officeLocation)
        : name(name), rank(rank), officeLocation(officeLocation), courseCount(0) {}

    void teachCourse(Course* course) {
        if (courseCount < 10) {
            courses[courseCount++] = course;
        }
    }
};

class Student {
public:
    string name;
    int studentID;
    float GPA;
    Course* courses[10];
    int courseCount;

    Student(const string& name, int studentID, float GPA)
        : name(name), studentID(studentID), GPA(GPA), courseCount(0) {}

    void enrollInCourse(Course* course) {
        if (courseCount < 10) {
            courses[courseCount++] = course;
        }
    }
};

class Course {
public:
    string name;
    int courseNumber;
    int credits;

    Course(const string& name, int courseNumber, int credits)
        : name(name), courseNumber(courseNumber), credits(credits) {}
};

int main() {
    University university;

    Department* csDept = new Department("Computer Science", "Dr. Smith");
    university.addDepartment(csDept);

    Course* course1 = new Course("Data Structures", 101, 3);
    Course* course2 = new Course("Algorithms", 102, 3);

    csDept->addCourse(course1);
    csDept->addCourse(course2);

    FacultyMember* profJones = new FacultyMember("Prof. Jones", "Associate Professor", "Room 101");
    csDept->addFacultyMember(profJones);
    profJones->teachCourse(course1);
    profJones->teachCourse(course2);

    Student* student1 = new Student("Alice", 1001, 3.8);
    Student* student2 = new Student("Bob", 1002, 3.5);

    csDept->addStudent(student1);
    csDept->addStudent(student2);

    student1->enrollInCourse(course1);
    student2->enrollInCourse(course2);

    university.display();

    
    delete csDept;
    delete course1;
    delete course2;
    delete profJones;
    delete student1;
    delete student2;

    return 0;
}





 