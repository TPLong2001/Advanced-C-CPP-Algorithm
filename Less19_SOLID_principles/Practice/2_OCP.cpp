#include <iostream>
#include <vector>
using namespace std;

// Vi phạm Open/Closed Principle
enum ShapeType_ViPham {
    CIRCLE,
    SQUARE
};

class Shape_ViPham {
public:
    ShapeType_ViPham type;
};

class ShapeDrawer_ViPham {
public:
    void drawShape(const Shape_ViPham& shape) {
        if (shape.type == CIRCLE) {
            cout << "Drawing Circle" << endl;
        }
        else if (shape.type == SQUARE) { 
            cout << "Drawing Square" << endl;
        }
        // Mỗi lần thêm hình mới, bạn phải sửa lại hàm này
    }
};


// Áp dụng Open/Closed Principle
class Shape {
public:
    virtual void draw() const = 0;  // phương thức thuần ảo, lớp Shape là trừu tượng
    virtual ~Shape() = default;
};

class Circle : public Shape {
public:
    void draw() const override {
        cout << "Drawing Circle" << endl;
    }
};

class Square : public Shape {
public:
    void draw() const override {
        cout << "Drawing Square" << endl;
    }
};

// Nếu muốn thêm Triangle, không cần sửa đổi class cũ
class Triangle : public Shape {
public:
    void draw() const override {
        cout << "Drawing Triangle" << endl;
    }
};

class ShapeDrawer {
public:
    void drawShapes(const vector<Shape*>& shapes) {
        for (const auto& shape : shapes) {
            shape->draw(); // không cần sửa lại method này khi thêm shape mới
        }
    }
};

int main() {
    vector<Shape*> shapes;

    shapes.push_back(new Circle());
    shapes.push_back(new Square());
    shapes.push_back(new Triangle()); // thêm mới dễ dàng

    ShapeDrawer drawer;
    drawer.drawShapes(shapes);

    // giải phóng bộ nhớ
    for (auto shape : shapes) {
        delete shape;
    }

    return 0;
}