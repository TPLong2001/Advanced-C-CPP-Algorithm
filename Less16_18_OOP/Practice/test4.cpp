#include <iostream>
using namespace std;

// Lớp trừu tượng Shape
class Shape {
public:
    virtual void draw() = 0;  // phương thức thuần ảo, lớp Shape là trừu tượng
};

// Lớp Circle kế thừa Shape
class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    void draw() override {
        cout << "Ve hinh tron voi ban kinh = " << radius << endl;
    }
};

// Lớp Rectangle kế thừa Shape
class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    void draw() override {
        cout << "Ve hinh chu nhat " << width << "x" << height << endl;
    }
};

int main() {
    // Shape s;  // Lỗi: không thể tạo đối tượng từ lớp trừu tượng Shape
    Shape* shape1 = new Circle(5.0);
    Shape* shape2 = new Rectangle(3.0, 4.0);

    shape1->draw();  // Gọi draw() của lớp Circle
    shape2->draw();  // Gọi draw() của lớp Rectangle

    delete shape1;
    delete shape2;
    return 0;
}