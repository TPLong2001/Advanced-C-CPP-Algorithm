#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

// Vi phạm Liskov Substitution Principle
class Bird_ViPham {
public:
    virtual void fly() const = 0;
    virtual ~Bird_ViPham() = default;
};

class Sparrow_ViPham : public Bird_ViPham {
public:
    void fly() const override {
        cout << "Sparrow is flying" << endl;
    }
};

class Penguin_ViPham : public Bird_ViPham {
public:
    void fly() const override {
        throw runtime_error("Penguins cannot fly");
    }
};







// Áp dụng Liskov Substitution Principle
class Bird {
public:
    virtual ~Bird() = default;
};

// Interface chỉ dành cho các loài chim bay được
class Flyable {
public:
    virtual void fly() const = 0;
    virtual ~Flyable() = default;
};

// Chim bay được
class Sparrow : public Bird, public Flyable {
public:
    void fly() const override {
        cout << "Sparrow is flying" << endl;
    }
};

// Chim không bay được
class Penguin : public Bird {
public:
    void swim() const {
        cout << "Penguin is swimming" << endl;
    }
};

int main() {
    vector<Bird*> birds { new Sparrow(), new Penguin() };

    for (auto bird : birds) {
        // Dùng dynamic_cast để kiểm tra khả năng bay
        if (auto flyable = dynamic_cast<Flyable*>(bird)) {
            flyable->fly();
        } else if (auto penguin = dynamic_cast<Penguin*>(bird)) {
            penguin->swim();
        }
    }

    for (auto bird : birds) delete bird;
    return 0;
}







