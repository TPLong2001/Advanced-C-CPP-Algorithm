# Bài 19: SOLID 

## 1. Tổng quan

Các nguyên tắc thiết kế hướng đối tượng __SOLID__ là tập hợp `5 nguyên tắc` giúp xây dựng mã nguồn linh hoạt, dễ bảo trì, và tái sử dụng hiệu quả hơn. Chúng bao gồm:

---
## 2. Single Responsibility Principle _(SRP - Nguyên tắc trách nhiệm duy nhất)_
### Định nghĩa:
Một class/chức năng chỉ nên có một lý do duy nhất để thay đổi, tức là chỉ đảm nhận một trách nhiệm cụ thể.
### Ý nghĩa:
Giúp code rõ ràng, dễ hiểu và dễ bảo trì. Khi thay đổi một chức năng, chỉ phải sửa đúng nơi chịu trách nhiệm.
### Lợi ích:
- Dễ sửa lỗi hoặc cập nhật tính năng.
- Giảm rủi ro khi thay đổi, vì các phần khác không bị ảnh hưởng.
- Tăng khả năng tái sử dụng class.
### Ví dụ:
Tách class `UserManager` chỉ quản lý người dùng, còn việc gửi email thông báo tách sang class `EmailService`.  

__Vi phạm SRP:__
```cpp
/// Vi phạm Single Responsibility Principle
class UserManager_ViPham {
public:
    void addUser(const string& username) {
        // Trách nhiệm 1: thêm user vào DB
        cout << "Added user: " << username << endl;
        
        // Trách nhiệm 2: Gửi email thông báo
        cout << "Email sent to: " << username << endl;
    }
};
```

__Áp dụng SRP:__
```cpp
#include <iostream>
#include <string>

using namespace std;

// Áp dụng Single Responsibility Principle
// Chỉ đảm nhiệm việc gửi email
class EmailService {
public:
    void sendEmail(const string& to, const string& message) {
        cout << "Email sent to " << to << ": " << message << endl;
    }
};

// Chỉ đảm nhiệm quản lý người dùng
class UserManager {
public:
    void addUser(const string& username) {
        cout << "Added user: " << username << endl;
    }
};

// Cách dùng rõ ràng hơn
int main() {
    UserManager userManager;
    EmailService emailService;

    string username = "alice@example.com";
    userManager.addUser(username);
    emailService.sendEmail(username, "Welcome to our service!");

    return 0;
}
```
__Kết quả:__
```cpp
Added user: alice@example.com
Email sent to alice@example.com: Welcome to our service!
```

---
## 3. Open-Closed Principle _(OCP - Nguyên tắc đóng/mở)_
### Định nghĩa:
Các thành phần (class, hàm, module) mở rộng được mà không cần sửa đổi code hiện có.
### Ý nghĩa:
Khi có yêu cầu mới, ta thêm code mới (kế thừa, implement interface) chứ không phải sửa code cũ.
### Lợi ích:
- Hạn chế phát sinh lỗi ở code cũ.
- Hệ thống dễ mở rộng, bảo trì lâu dài.
### Ví dụ:
Dùng interface `Shape` và các class con như `Circle`, `Square`, khi cần thêm hình mới chỉ việc tạo class mới mà không phải sửa hàm vẽ.  

__Vi phạm OCP:__
```cpp
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
```

__Áp dụng OCP:__
```cpp
#include <iostream>
#include <vector>
using namespace std;
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
```

__Kết quả:__
```cpp
Drawing Circle
Drawing Square
Drawing Triangle
```

---
## 4. Liskov Substitution Principle _(LSP - Nguyên tắc thay thế Liskov)_
### Định nghĩa:
Class con có thể thay thế cho class cha ở mọi nơi mà không ảnh hưởng đến đúng đắn của chương trình.
### Ý nghĩa:
Giúp kế thừa hợp lý, tránh lỗi khi sử dụng class con thay class cha.
### Lợi ích:
- Tăng tính tin cậy khi mở rộng hệ thống.
- Kế thừa rõ ràng, không gây nhầm lẫn về hành vi.
### Ví dụ:
Nếu có class `Bird` với hàm `fly()`, không nên cho `Penguin` kế thừa `Bird` vì chim cánh cụt không biết bay, tránh gây lỗi khi gọi `fly()`.

__Vi phạm LSP:__
```cpp
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
```

__Áp dụng LSP:__
```cpp
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;
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
```

__Kết quả:__
```cpp
Sparrow is flying
Penguin is swimming
```

---
## 5. Interface Segregation Principle _(ISP - Nguyên tắc phân tách interface)_
### Định nghĩa:
Không ép class phải implement các method không cần thiết – nên tách interface lớn thành các interface nhỏ, chuyên biệt.
### Ý nghĩa:
Đảm bảo mỗi class chỉ phụ trách những hành vi phù hợp, không bị “gánh” những hàm không dùng.
### Lợi ích:
- Code gọn gàng, dễ hiểu.
- Dễ mở rộng, bảo trì.
### Ví dụ:
Thay vì interface `Animal` với nhiều phương thức (`fly()`, `swim()`, `run()`), hãy chia thành `Flyable`, `Swimmable`, `Runnable…` để class chỉ implement đúng hành vi.

__Vi phạm ISP:__
```cpp
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
```

__Áp dụng ISP:__
```cpp
#include <iostream>

using namespace std;
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
```

__Kết quả:__
```cpp
Dog swimming
Dog running
Bird flying
Bird running
```

---
## 6. Dependency Inversion Principle _(DIP - Nguyên tắc đảo ngược phụ thuộc)_
### Định nghĩa:
Module cấp cao không phụ thuộc module cấp thấp mà cả hai cùng phụ thuộc vào abstraction (interface/abstract class).
### Ý nghĩa:
Giảm phụ thuộc trực tiếp vào các class cụ thể, tăng khả năng mở rộng và test.
### Lợi ích:
- Dễ thay thế, mở rộng các thành phần hệ thống.
- Dễ unit test (vì có thể mock các dependency).
### Ví dụ:
Class `UserManager` không dùng trực tiếp class `MySQLDatabase` mà thao tác thông qua interface `Database`, giúp dễ thay đổi sang MongoDB, file, v.v.

__Vi phạm DIP:__
```cpp
// Vi phạm Dependency Inversion Principle
// Module cấp thấp
class MySQLDatabase_ViPham {
public:
    void saveData(const string& data) {
        cout << "Saving " << data << " to MySQL\n";
    }
};

// Module cấp cao phụ thuộc trực tiếp vào module cấp thấp
class UserManager_ViPham {
    MySQLDatabase_ViPham db; // Phụ thuộc cụ thể
public:
    void saveUser(const string& username) {
        db.saveData(username);
    }
}; 
```

__Áp dụng DIP:__
```cpp
#include <iostream>

using namespace std;
// Áp dụng Dependency Inversion Principle   
// Interface abstraction
class Database {
public:
    virtual void save(const string& data) = 0;
    virtual ~Database() = default;
};

// Concrete implementation
class MySQL : public Database {
public:
    void save(const string& data) override {
        cout << "Saving " << data << " to MySQL\n";
    }
};

// Concrete implementation
class MongoDB : public Database {
public:
    void save(const string& data) override {
        cout << "Saving " << data << " to MongoDB\n";
    }
};

//  Module cấp cao phụ thuộc vào abstraction thay vì phụ thuộc trực tiếp vào module cấp thấp
class UserManager {
    Database* db; // Sử dụng abstraction
public:
    UserManager(Database* db) : db(db) {}
    void saveUser(const string& username) {
        db->save(username);
    }
};


int main() {
    MySQL mysqlDb;
    MongoDB mongoDb;

    UserManager userManager(&mysqlDb); // có thể thay đổi database dễ dàng
    userManager.saveUser("alice");

    UserManager userManager2(&mongoDb); // dùng MongoDB dễ dàng
    userManager2.saveUser("bob");

    return 0;
}
```

__Kết quả:__
```cpp
Saving alice to MySQL
Saving bob to MongoDB
```
