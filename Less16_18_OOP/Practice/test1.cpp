#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() {  // Phương thức ảo
        cout << "Base class\n";
    }
};

class Derived : public Base {
public:
    void show() override {  // Phương thức ghi đè
        cout << "Derived class\n";
    }
};

int main() {
    Base* basePtr;
    Derived derivedObj;

    basePtr = &derivedObj;  // Con trỏ lớp cha trỏ đến đối tượng lớp con
    basePtr->show();  // Gọi phương thức show() thông qua con trỏ lớp cha
    // Kết quả: "Derived class"

    return 0;
}