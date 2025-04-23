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
