#include <iostream>

using namespace std;

// Vi phạm Interface Segregation Principle
// Interface quá lớn
class Animal_ViPham {
public:
    virtual void swim() = 0;
    virtual void fly() = 0;
    virtual void run() = 0;
    virtual ~Animal_ViPham() = default;
};

class Dog_ViPham : public Animal_ViPham {
public:
    void swim() override { cout << "Dog swimming\n"; }
    void fly() override { /* Dog can't fly */ }
    void run() override { cout << "Dog running\n"; }
};

class Bird_ViPham : public Animal_ViPham {
public:
    void swim() override { /* Bird doesn't swim generally */ }
    void fly() override { cout << "Bird flying\n"; }
    void run() override { cout << "Bird running\n"; }
};












// Áp dụng Interface Segregation Principle
class Animal {
public:
    virtual ~Animal() = default;
};

class Swimable : public Animal {
public:
    virtual void swim() = 0;
    virtual ~Swimable() = default;
};

class Flyable : public Animal {
public:
    virtual void fly() = 0;
    virtual ~Flyable() = default;
};

class Runable : public Animal {
public:
    virtual void run() = 0;
    virtual ~Runable() = default;
};

class Dog : public Swimable, public Runable {
public:
    void swim() override { cout << "Dog swimming\n"; }
    void run() override { cout << "Dog running\n"; }
};

class Bird : public Flyable, public Runable {
public:
    void fly() override { cout << "Bird flying\n"; }
    void run() override { cout << "Bird running\n"; }
};

int main() {
    Dog dog;
    Bird bird;

    dog.swim();
    dog.run();

    bird.fly();
    bird.run();

    return 0;
}








