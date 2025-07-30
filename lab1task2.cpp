#include <iostream>
using namespace std;

class Animal {
protected:
    string name, sound;
public:
    Animal(string n, string s) : name(n), sound(s) {}
    virtual void display() { cout << "Animal: " << name << ", Sound: " << sound << endl; }
};

class Dog : public Animal {
    string breed;
public:
    Dog(string n, string b) : Animal(n, "Bark"), breed(b) {}
    void display() override { cout << "Dog: " << name << ", Breed: " << breed << ", Sound: " << sound << endl; }
};

int main() {
    Dog d("Max", "German Shepherd");
    d.display();
    return 0;
}
  