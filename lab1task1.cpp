#include <iostream>
using namespace std;

class Person {
protected:
    string name;
    int age;
public:
    Person(string n, int a) : name(n), age(a) {}
    void display() { cout << name << ", Age: " << age << endl; }
};

class Student : public Person {
    int studentID;
public:
    Student(string n, int a, int id) : Person(n, a), studentID(id) {}
    void display() { cout << "Student ID: " << studentID << ", "; Person::display(); }
};

class Teacher : public Person {
    string subject;
public:
    Teacher(string n, int a, string sub) : Person(n, a), subject(sub) {}
    void display() { cout << "Subject: " << subject << ", "; Person::display(); }
};

int main() {
    Student("Ali", 20, 123).display();
    Teacher("Prof. Shahzad", 45, "Math").display();
    return 0;
}
