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