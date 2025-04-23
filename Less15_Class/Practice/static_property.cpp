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
