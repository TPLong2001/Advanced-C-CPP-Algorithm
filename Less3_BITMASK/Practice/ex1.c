#include <stdio.h>
#include <stdint.h>

// Ta sử dụng kỹ thật bitmask để giảm số lượng biến cần sử dụng
// vì vậy ta cần các toán tử bitwise để thao tác với các bit đó nhằm đặt, xóa hoặc kiểm tra trạng thái của các bit cụ thể
// toán tử & (AND), | (OR), ^ (XOR), ~ (NOT), << (left shift), >> (right shift)

int main() {

    uint8_t user1 = 0b00000001;
    uint8_t user2 = 0b00000000;

    // toán tử NOT (~): đảo ngược trạng thái của bit
    uint8_t not_bitwise = ~user1 ;
    // 0b00000001 => ~0b00000001 = 0b11111110
    // 0b11111110 => ~0b11111110 = 0b00000001

    // toán tử AND (&): lấy bit 1 nếu cả 2 bit đều là 1, ngược lại trả về 0 (tương tự phép nhân)
    uint8_t and_bitwise = user1 & user2;
    // 0b00000001 & 0b00000001 = 0b00000001
    // 0b00000001 & 0b00000000 = 0b00000000

    // toán tử OR (|): lấy bit 1 nếu 1 trong 2 bit là 1, ngược lại trả về 0 (tương tự phép cộng)
    uint8_t or_bitwise = user1 | user2;
    // 0b00000001 | 0b00000001 = 0b00000001
    // 0b00000001 | 0b00000000 = 0b00000001

    // toán tử XOR (^): lấy bit 1 nếu 2 bit khác nhau, ngược lại trả về 0 (tương tự phép cộng không nhớ)
    uint8_t xor_bitwise = user1 ^ user2;
    // 0b00000001 ^ 0b00000001 = 0b00000000
    // 0b00000001 ^ 0b00000000 = 0b00000001

    // toán tử left shift (<<): dịch bit sang trái n bit
    uint8_t left_shift = user1 << 2;
    // 0b00000001 << 1 = 0b00000010
    // 0b00000001 << 2 = 0b00000100

    // toán tử right shift (>>): dịch bit sang phải n bit 
    uint8_t right_shift = user1 >> 1;
    // 0b00000001 >> 1 = 0b00000000
    // 0b00000010 >> 1 = 0b00000001


    return 0;
}