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