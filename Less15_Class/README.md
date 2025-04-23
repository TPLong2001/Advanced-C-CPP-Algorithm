# Bài 15: Class

## Tổng quan

Trong C++, một class là một kiểu dữ liệu trừu tượng, giúp người lập trình nhóm các thuộc tính và phương thức có liên quan thành một đơn vị.  
Class là một cơ sở của lập trình hướng đối tượng (OOP), nơi đối tượng (object) là một thể hiện (instance) của class. Class cho phép tổ chức mã nguồn, quản lý dữ liệu và hành vi của đối tượng một cách dễ dàng.

Cú pháp cơ bản:
```cpp
class ClassName {
    // Các thành phần trong class
};
```
Ví dụ:
```cpp
class Car {
public:
    // Thuộc tính
    string color;
    int speed;

    // Phương thức
    void accelerate() {
        speed += 10;
    }

    void brake() {
        speed -= 10;
    }
};
```

## Phạm vi truy cập
Phạm vi truy cập trong class là cách quy định mức độ truy cập của các thành viên (biến và phương thức) trong một lớp.  

Có ba loại phạm vi truy cập chính: 
- `public`: Các thành phần công khai có thể được truy cập từ bất kỳ đâu, cả bên ngoài class.
```cpp
class Example {
public:
    int x;
};

```
-  `private`: Các thành phần riêng tư chỉ có thể được truy cập từ bên trong class. 
```cpp
class Example {
private:
    int x;
public:
    void setX(int value) {
        x = value;
    }
};

```
-  `protected`: Các thành phần bảo vệ có thể được truy cập từ bên trong class và các lớp con (lớp kế thừa).
```cpp
class Base {
protected:
    int x;
};

```
## Constructor method
Constructor là một phương thức đặc biệt trong class, được gọi khi một đối tượng được khởi tạo.   
Constructor có nhiệm vụ khởi tạo các thuộc tính của đối tượng.   
Constructor có cùng tên với class và không có kiểu trả về.

__Ví dụ:__
```cpp
class Car {
public:
    string color;
    int speed;

    // Constructor
    Car(string c, int s) {
        color = c;
        speed = s;
    }
};

Car myCar("Red", 100);  // Tạo đối tượng myCar với màu đỏ và tốc độ 100

```
## Destructor method
__Destructor__ là một phương thức đặc biệt, được gọi khi một đối tượng bị hủy.  
Destructor thường được dùng để giải phóng tài nguyên hoặc làm sạch các tài nguyên mà đối tượng đã chiếm dụng.  
Destructor có tên giống với class, nhưng có dấu t ~ ở trước.

__Ví dụ:__
```cpp
class Car {
public:
    string color;
    int speed;

    // Constructor
    Car(string c, int s) {
        color = c;
        speed = s;
    }

    // Destructor
    ~Car() {
        // Dọn dẹp tài nguyên nếu cần thiết
        cout << "Car object is destroyed." << endl;
    }
};

Car myCar("Red", 100);  // Tạo đối tượng myCar với màu đỏ và tốc độ 100
// Khi myCar ra khỏi phạm vi, destructor được gọi

```
## Static property

__Static property__ là thuộc tính của class mà tất cả đối tượng của class đó chia sẻ chung. Thay vì mỗi đối tượng có một bản sao riêng của thuộc tính này, nó sẽ có một bản sao duy nhất chung cho tất cả các đối tượng.

Thuộc tính static được khai báo với từ khóa `static`. Nó không phụ thuộc vào đối tượng, mà thay vào đó nó liên quan đến chính class.

__Ví dụ:__
```cpp
#include <iostream>

using namespace std;


class HinhChuNhat
{
    public:
        double chieuDai;
        double chieuRong;
        static int var;
};
   
int HinhChuNhat::var;

int main()
{
    HinhChuNhat hinh1;
    HinhChuNhat hinh2;
    HinhChuNhat hinh3;

    cout << "address of chieu dai: " << &hinh1.chieuDai << '\n';
    cout << "address of chieu dai: " << &hinh2.chieuDai << '\n';
    cout << "address of chieu dai: " << &hinh3.chieuDai << '\n';

    cout << "address of var: " << &hinh1.var << '\n';
    cout << "address of var: " << &hinh2.var << '\n';
    cout << "address of var: " << &hinh3.var << '\n';
    return 0;
}
```

__Kết quả:__
```
address of chieu dai: 0xddec1ffde0
address of chieu dai: 0xddec1ffdd0
address of chieu dai: 0xddec1ffdc0
address of var: 0x7ff6bed97030
address of var: 0x7ff6bed97030
address of var: 0x7ff6bed97030
```
## Static method

Static method là phương thức của class mà không cần đối tượng để gọi.  

Khi một method trong class được khai báo với từ khóa static:
- Method này độc lập với bất kỳ đối tượng nào của lớp.
- Method này có thể được gọi ngay cả khi không có đối tượng nào của class tồn tại.
- Method này có thể được truy cập bằng cách sử dụng tên class thông qua toán tử :: .
- Method này có thể truy cập các static property và các static method bên trong hoặc bên ngoài class.

__Ví dụ:__
```cpp
#include <iostream>
using namespace std;

class HinhChuNhat
{
    public:
        double chieuDai;
        double chieuRong;
        static int count;

        HinhChuNhat(int dai = 5, int rong = 4);
        ~HinhChuNhat();

        double tinhDienTich();
        static void display();
};

HinhChuNhat::HinhChuNhat(int dai, int rong)
{
    chieuDai  = dai;
    chieuRong = rong;
    count++;
}

HinhChuNhat::~HinhChuNhat()
{
    cout << "Destructor" << endl;
}

void HinhChuNhat::display()
{
    cout << "Number of object: " << count << endl;
}

int HinhChuNhat::count = 0;

int main()
{

    HinhChuNhat::display();

    HinhChuNhat hcn(5,4);

    HinhChuNhat::display();
    return 0;
}

```

__Kết quả:__
```
Number of object: 0
Number of object: 1
Destructor
```