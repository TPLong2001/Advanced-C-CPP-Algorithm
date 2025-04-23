# Bài 16 - 17 - 18: OOP

## Tính Đóng Gói
Tính đóng gói (Encapsulation) là cơ chế gom nhóm dữ liệu (thuộc tính) và các phương thức (hàm) thao tác trên dữ liệu đó vào cùng một đối tượng (class).  
Điều này giúp ẩn giấu chi tiết cài đặt bên trong đối tượng, chỉ cho phép truy cập qua các phương thức public, đảm bảo an toàn dữ liệu.

__C++ hỗ trợ đóng gói thông qua:__
- Access Specifiers: `private`, `protected`, `public`.

- Dữ liệu thường được đặt `private`, các phương thức truy cập (`getter`, `setter`) là `public`.

## Tính Kế Thừa
### Tổng quan
Kế thừa (Inheritance) cho phép một lớp con (derived class) kế thừa thuộc tính và phương thức của lớp cha (base class). Giúp tái sử dụng mã, giảm trùng lặp.

Có thể chỉ định phạm vi truy cập  xác định quyền truy cập của lớp con đối với các thành phần của lớp cha:
- __`Public`__ (Kế thừa công khai): tất cả các thành phần công khai (`public`) và bảo vệ (`protected`) của lớp cha sẽ giữ nguyên quyền truy cập khi chúng được kế thừa vào lớp con.
- __`Protected`__ (Kế thừa bảo vệ): các thành phần `public` và `protected` của lớp cha sẽ trở thành `protected` trong lớp con, và các thành phần `private` vẫn không thể truy cập.
- __`Private `__ (Kế thừa riêng tư): tất cả các thành phần public và protected của lớp cha sẽ trở thành private trong lớp con. Điều này có nghĩa là các thành phần này chỉ có thể được truy cập từ bên trong lớp con, không thể truy cập từ bên ngoài lớp con.
### Đa kế Thừa
Cho phép một lớp con kế thừa từ nhiều lớp cha khác nhau. Điều này giúp lớp con có thể kết hợp các đặc tính và hành vi từ nhiều nguồn.  
Tuy nhiên, đa kế thừa có thể gây ra vấn đề phức tạp như xung đột tên và vấn đề kim cương (diamond problem).

__Ví dụ:__
```cpp
class Animal {
public:
    void eat() { /*...*/ }
};

class Mammal {
public:
    void breathe() { /*...*/ }
};

class Bat : public Animal, public Mammal {
public:
    void fly() { /*...*/ }
};

```
### Kế thừa ảo
Để giải quyết vấn đề kim cương, C++ cung cấp kỹ thuật kế thừa ảo (virtual inheritance), đảm bảo rằng lớp con chỉ có một bản sao duy nhất của lớp cha chung. 

__Ví dụ:__
```cpp
class Animal {
public:
    virtual void eat() { /*...*/ }
};

class Mammal : virtual public Animal {
public:
    void breathe() { /*...*/ }
};

class WingedAnimal : virtual public Animal {
public:
    void fly() { /*...*/ }
};

class Bat : public Mammal, public WingedAnimal {
public:
    void hangUpsideDown() { /*...*/ }
};

```
## Tính Đa Hình
### Tổng quan
Đa hình (Polymorphism) cho phép cùng một hành vi nhưng có cách thực thi khác nhau tùy đối tượng. Giúp mở rộng dễ dàng, giảm phụ thuộc.
### Đa hình động (Run-time Polymorphism)
Khả năng của một đối tượng trong C++ có thể thể hiện nhiều hình thức khác nhau, phụ thuộc vào loại đối tượng thực tế mà con trỏ hoặc tham chiếu trỏ đến.

Việc chọn phương thức phù hợp để gọi sẽ được thực hiện tại thời gian chạy (runtime), chứ không phải tại thời gian biên dịch (compile-time).

__Để thực hiện đa hình động, bạn cần:__

- __Con trỏ/tham chiếu lớp cha__ trỏ đến một đối tượng của lớp con.

- __Virtual function__ (phương thức ảo) trong lớp cha, cho phép lớp con ghi đè phương thức này.

=> Để __kích hoạt đa hình động__, phương thức trong lớp cha phải được khai báo là __virtual__. Khi đó, lớp con có thể __ghi đè__ (override) phương thức này để cung cấp một triển khai riêng của nó.

C++ sử dụng __bảng phương thức ảo__ (virtual function table - vtable) để quyết định phương thức nào sẽ được gọi tại thời gian chạy.  
Khi bạn gọi một phương thức ảo qua một con trỏ hoặc tham chiếu lớp cha, C++ tra cứu vtable và gọi phương thức của đối tượng thực tế mà con trỏ trỏ đến.

__Ví dụ:__
```cpp
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
```

__Kết quả:__
```
Derived class
```
#### Override
Ghi đè phương thức lớp cha bằng phương thức lớp con. Dùng từ khóa override giúp kiểm tra đúng kiểu.

### Đa hình tĩnh (Compile-time Polymorphism)
__Đa hình tĩnh__ (__Compile-time Polymorphism__) là một cơ chế cho phép chương trình lựa chọn phương thức hoặc toán tử nào để sử dụng tại thời gian biên dịch.
#### Function Overloading
Nạp chồng hàm cho phép bạn định nghĩa __nhiều hàm cùng tên__ nhưng __khác tham số__ (về số lượng hoặc kiểu dữ liệu của tham số).  
Trình biên dịch sẽ xác định hàm nào được gọi dựa trên số lượng và kiểu dữ liệu của các đối số trong lời gọi hàm, tất cả sẽ được thực hiện ở thời gian biên dịch.

__Ví dụ:__
```cpp
#include <iostream>
using namespace std;

class Print {
public:
    // Nạp chồng hàm: Hàm in số nguyên
    void display(int i) {
        cout << "Integer: " << i << endl;
    }

    // Nạp chồng hàm: Hàm in chuỗi
    void display(string s) {
        cout << "String: " << s << endl;
    }

    // Nạp chồng hàm: Hàm in số thực
    void display(double d) {
        cout << "Double: " << d << endl;
    }
};

int main() {
    Print obj;
    obj.display(5);           // Gọi hàm in số nguyên
    obj.display("Hello");     // Gọi hàm in chuỗi
    obj.display(3.14);        // Gọi hàm in số thực

    return 0;
}

```

__Kết quả:__
```
Integer: 5
String: Hello
Double: 3.14
```
#### Operator Overloading
Nạp chồng toán tử cho phép bạn định nghĩa lại cách thức hoạt động của các toán tử cho các kiểu dữ liệu tùy chỉnh (user-defined types). C++ cho phép nạp chồng hầu hết các toán tử (như +, -, *, ==, v.v.) để làm việc với các đối tượng của lớp tự định nghĩa.

__Ví dụ:__
```cpp
#include <iostream>
using namespace std;

class Complex {
private:
    int real, imag;

public:
    // Constructor
    Complex(int r, int i) : real(r), imag(i) {}

    // Nạp chồng toán tử '+' để cộng hai số phức
    Complex operator + (const Complex& other) {
        return Complex(real + other.real, imag + other.imag);
    }

    // Hàm hiển thị kết quả
    void display() {
        cout << real << " + " << imag << "i" << endl;
    }
};

int main() {
    Complex num1(3, 4), num2(1, 2);
    Complex result = num1 + num2;  // Gọi toán tử '+'
    result.display();  // In ra: 4 + 6i

    return 0;
}

```

__Kết quả:__
```
4 + 6i
```
## Tính Trừu Tượng
### Tổng quan
là khả năng che giấu bớt những chi tiết phức tạp bên trong và chỉ phơi bày những thông tin thiết yếu của đối tượng​.  
Nó giúp tập trung vào bản chất của đối tượng thay vì chi tiết hiện thực.

Trong C++, tính trừu tượng thường được thực hiện thông qua:
- __Lớp trừu tượng__ (abstract class): lớp chỉ mô tả những đặc điểm chung, còn việc triển khai chi tiết do các lớp dẫn xuất quyết định.
- __Phương thức thuần ảo__ (pure virtual function): phương thức khai báo trong lớp cơ sở nhưng không có phần triển khai, ép buộc các lớp con phải định nghĩa nó.
### Phương thức thuần ảo (Pure Virtual Function)
__Phương thức thuần ảo__ là một hàm thành viên được khai báo là `virtual` nhưng __không có thân hàm__ (không có phần định nghĩa), thường được ký hiệu bằng cú pháp = 0 ngay tại khai báo

__Phương thức thuần ảo__ thường được dùng để định nghĩa các hành động chung một cách trừu tượng.

__Ví dụ:__
```cpp
class Shape {
public:
    virtual void draw() = 0;  // Phương thức thuần ảo
};

```
### Lớp trừu tượng (Asbtract class)
__Lớp trừu tượng__ là lớp không thể tạo đối tượng được, nó sinh ra để làm lớp cha cho các lớp khác, nhằm mục đích cung cấp một giao diện chung.  
Trong C++, lớp trừu tượng là lớp chứa __ít nhất một phương thức thuần ảo__.

__Lớp trừu tượng__ không thể được dùng để tạo đối tượng trực tiếp – nếu ta cố tạo một instance của lớp trừu tượng, trình biên dịch sẽ báo lỗi​.

__Lớp trừu tượng__ thường được dùng để định nghĩa nên __các giao diện (interface) hoặc lớp cơ sở trừu tượng__ trong thiết kế phần mềm.

__Ví dụ:__
```cpp
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

```

__Kết quả:__
```
Ve hinh tron voi ban kinh = 5
Ve hinh chu nhat 3x4
```