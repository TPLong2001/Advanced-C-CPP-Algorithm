#include <stdio.h>
#include <stdint.h>

/*
 * int8_t: kiểu số nguyên có dấu 8 bit
 * uint8_t: kiểu số nguyên không dấu 8 bit
 * int16_t: kiểu số nguyên có dấu 16 bit
 * uint16_t: kiểu số nguyên không dấu 16 bit
 * int32_t: kiểu số nguyên có dấu 32 bit
 * uint32_t: kiểu số nguyên không dấu 32 bit
 */


//user

// gender: nam = 0, nữ = 1
// status: 0 = single, 1 = married
// xe máy: 0 = không có, 1 = có
// xe hơi: 0 = không có, 1 = có
// nhà: 0 = không có, 1 = có
// máy bay: 0 = không có, 1 = có

// 1 user có thể có nhiều thuộc tính, mỗi thuộc tính có thể có giá trị 0 hoặc 1
// nếu mỗi thuộc tính sử dụng 1 biến thì cần 6 biến để lưu trữ
// mỗi biến có kích thước là 1 byte => cần 6 byte để lưu trữ


uint8_t gender;
uint8_t status;
uint8_t xe_may;
uint8_t xe_hoi;
uint8_t nha;
uint8_t may_bay;

// sử dụng bitmask để giảm số lượng biến cần sử dụng
// vì mỗi biến chỉ có 2 trạng thái là 0 hoặc 1 nên chỉ cần 1 bit để lưu trữ
// vì vậy với 6 thuộc tính cần lưu trữ thì chỉ cần 6 bit để lưu trữ
// 6 bit này sẽ được lưu trữ trong 1 biến có kích thước 1 byte = 8 bit
// 2 bit còn lại không sử dụng và 6 bit thấp nhất đực sử dụng để lưu trữ 6 thuộc tính

uint8_t user; //0bxxxxxxxx

//bit 0: gender => 0bxxxxxxx1 hoặc 0bxxxxxxx0
//bit 1: status => 0bxxxxxx0x hoặc 0bxxxxxx1x
//bit 2: xe_may => 0bxxxxx0xx hoặc 0bxxxxx1xx
//bit 3: xe_hoi => 0bxxxx0xxx hoặc 0bxxxx1xxx
//bit 4: nha    => 0bxxx0xxxx hoặc 0bxxx1xxxx
//bit 5: may_bay => 0bxx0xxxxx hoặc 0bxx1xxxxx




