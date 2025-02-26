
# Bài 3 BITMASK

## DATA TYPE

__Kiểu dữ liệu chuẩn trong C__
| Kiểu dữ liệu | Kích thước      | Phạm vi giá trị       |
|--------------|------------|------------|
| ```char```   | 1 byte     | 0 đến 255  |
| ```short```  | 2 byte     | 0 đến 65,535 |
| ```int```    | 4 byte     | 0 đến 4,294,967,295  |
| ```float```  | 4 byte     | 6-7 chữ số thập phân  |
| ```double``` | 8 byte     | 15-16 chữ số thập phân  |

Kiểu ```void``` Không có giá trị, dùng trong các hàm không trả về giá trị.

Trong C, ngoài các kiểu dữ liệu chuẩn của C, thư viện __stdint.h__ cung cấp các kiểu dữ liệu có độ dài cố định để đảm bảo tính nhất quán trên các kiến trúc phần cứng khác nhau.

__Kiểu dữ liệu trong thư viện stdint.h__
| Kiểu dữ liệu | Kích thước      | Phạm vi giá trị       |
|--------------|------------|------------|
| ```int8_t```   | 1 byte     | Số nguyên có dấu (-128 đến 127)  |
| ```uint8_t```  | 1 byte     | Số nguyên không dấu (0 đến 255) |
| ```int16_t```  | 2 byte     | Số nguyên có dấu (-32,768 đến 32,767)  |
| ```uint16_t``` | 2 byte     | Số nguyên không dấu (0 đến 65,535)  |
| ```int32_t```  | 4 byte     | Số nguyên có dấu (-2,147,483,648 đến 2,147,483,647)  |
| ```uint32_t``` | 4 byte     | Số nguyên không dấu (0 đến 4,294,967,295)  |
| ```int64_t```  | 8 byte     | Số nguyên có dấu (-9,223,372,036,854,775,808 đến 9,223,372,036,854,775,807) |
| ```uint64_t``` | 8 byte     | Số nguyên không dấu (0 đến 18,446,744,073,709,551,615) |

Thư viện __stdint.h__ được chuẩn hóa trong C99, cung cấp các kiểu dữ liệu số nguyên có kích thước cố định, giúp lập trình viên viết mã nguồn có tính tương thích cao trên nhiều kiến trúc khác nhau.  

Nên sử dụng __stdint.h__ khi làm việc với __hệ thống nhúng, truyền thông, hoặc xử lý dữ liệu nhạy cảm__ với kích thước bộ nhớ.


## BITMASK 

__Bitmask (mặt nạ bit)__ là một kỹ thuật trong lập trình dùng để __thao tác trên từng bit__ của dữ liệu nhị phân bằng các phép toán __bitwise (AND, OR, XOR, NOT, SHIFT)__.  

Kỹ thuật này thường được sử dụng để lưu trữ và xử lý thông tin hiệu quả với bộ nhớ thấp, đặc biệt trong lập trình hệ thống nhúng và xử lý dữ liệu nhị phân, thực hiện các phép toán logic trên một cụm bit, và quản lý các trạng thái, quyền truy cập, hoặc các thuộc tính khác.

__Vì sao sử dụng BITMASK__

Giả sử 1 __user__ có các thuộc tính như sau:
```
// user
// gender: nam = 0, nữ = 1
// status: 0 = single, 1 = married
// xe máy: 0 = không có, 1 = có
// xe hơi: 0 = không có, 1 = có
// nhà: 0 = không có, 1 = có
// máy bay: 0 = không có, 1 = có
```
Như bình thường ta sẽ có 6 biến ứng với từng thuộc tính đó là:
```
uint8_t gender;
uint8_t status;
uint8_t xe_may;
uint8_t xe_hoi;
uint8_t nha;
uint8_t may_bay;
```
Vậy thì ta cần __6 biến__ với kích thước nhỏ nhất để lưu trữ => ta sẽ tiêu tốn __6 byte__ bộ nhớ.  

Trong khi đó mỗi thuộc tính thực chất chỉ cần lưu trữ __2 trạng thái (0 và 1)__ => chỉ cần __1 bit__ để có thể lưu trữ mỗi thuộc tính => __6 thuộc tính__ cần __6 bit__ để lưu trữ.  

__Sử dụng ```BITMASK``` để giảm số lượng biến cần sử dụng:__

```
uint8_t user; //0b__xxxxxx

//bit 0: gender     => 0b__xxxxx1 hoặc 0b__xxxxx0
//bit 1: status     => 0b__xxxx0x hoặc 0b__xxxx1x
//bit 2: xe_may     => 0b__xxx0xx hoặc 0b__xxx1xx
//bit 3: xe_hoi     => 0b__xx0xxx hoặc 0b__xx1xxx
//bit 4: nha        => 0b__x0xxxx hoặc 0b__x1xxxx
//bit 5: may_bay    => 0b__0xxxxx hoặc 0b__1xxxxx
```
Như vậy chỉ cần tốn __1 byte__ có thể lưu trữ tất cả __6 thuộc tính__ của __user__ ứng với từng bit trong biến.

Khi đó để thao tác với từng bit tương ứng với từng thuộc tính ta cần sử dụng các phép toán __BITWISE(AND, OR, XOR, NOT, SHIFT)__  để đặt, xóa hoặc kiểm tra trạng thái của các bit cụ thể đó.  

* __Toán tử NOT (~)__ : đảo ngược trạng thái của bit  
```C
    uint8_t not_bitwise = ~user1 ;
    // 0b00000001 => ~0b00000001 = 0b11111110
    // 0b11111110 => ~0b11111110 = 0b00000001
```

* __Toán tử AND (&)__: lấy bit 1 nếu cả 2 bit đều là 1, ngược lại trả về 0 (tương tự phép nhân)  
```C
    uint8_t and_bitwise = user1 & user2;
    // 0b00000001 & 0b00000001 = 0b00000001
    // 0b00000001 & 0b00000000 = 0b00000000
```

* __Toán tử OR (|)__: lấy bit 1 nếu 1 trong 2 bit là 1, ngược lại trả về 0 (tương tự phép cộng)  
```C
    uint8_t or_bitwise = user1 | user2;
    // 0b00000001 | 0b00000001 = 0b00000001
    // 0b00000001 | 0b00000000 = 0b00000001
```

* __Toán tử XOR (^)__: lấy bit 1 nếu 2 bit khác nhau, ngược lại trả về 0 (tương tự phép cộng không nhớ)
```C
    uint8_t xor_bitwise = user1 ^ user2;
    // 0b00000001 ^ 0b00000001 = 0b00000000
    // 0b00000001 ^ 0b00000000 = 0b00000001
```

* __Toán tử left shift (<<)__: dịch bit sang trái n bit 
```C
    uint8_t left_shift = user1 << 2;
    // 0b00000001 << 1 = 0b00000010
    // 0b00000001 << 2 = 0b00000100
```

* __Toán tử right shift (>>)__: dịch bit sang phải n bit
```C
    uint8_t right_shift = user1 >> 1;
    // 0b00000001 >> 1 = 0b00000000
    // 0b00000010 >> 1 = 0b00000001
```

### Ví dụ:
Có 4 đèn led với 2 trạng thái bật (1) và tắt (0). Mỗi đèn LED được biểu diễn bằng 1 bit. Sử dụng __BITMASK__ để tạo __mặt nạ bit__ cho từng đèn.

```c
//BITMASK
#define LED1 1 << 0     // 0001
#define LED2 1 << 1     // 0010
#define LED3 1 << 2     // 0100
#define LED4 1 << 3     // 1000
```

Ta có 1 biến để điều khiển trạng thái của các đèn là ```uint8_t GPIO_Port```  

Vậy để __bật đèn LED1__ thì __bit đầu tiên__ của ```GPIO_Port``` phải được đưa lên __1__. Còn tắt thì đưa về giá trị __0__.  
Tương tự với các __LED2, LED3, LED4__.  
Ta sẽ dùng kỹ thuật __BITMASK (mặt nạ bit)__ kết hợp cùng với các toán tử __BITWISE__ để xử lý như sau:

```c
// Bật đèn LED1 => bật bit1 lên = 1
// 0b____xxxx | 0b00000001 = 0b____xxx1 : Ta lấy GPIO_Port OR BITMASK_LED1 (x | 1 = 1) => bật bit1 lên = 1
GPIO_Port |= LED1;

// Tắt đèn LED1 => xóa bit1 về = 0
// 0b____xxxx & 0b11111110 = 0b____xxx0 : Ta lấy GPIO_Port AND ~BITMASK_LED1 (x & 0 = 0) => xóa bit1 về = 0
GPIO_Port &= ~LED1;

// Tương tự LED2
// 0b____xxxx | 0b00000010 = 0b____xx1x
GPIO_Port |= LED2;
// 0b____xxxx & 0b11111101 = 0b____xx0x
GPIO_Port &= ~LED2;
```

__Sử dụng BIT-FIELDS để lưu trữ__:

Bây giờ thay vì sử dụng các biến với ```uint8_t```, ```uint16_t```, ```uint32_t```, ... để lưu trữ trạng thái của các LED thì ta sẽ sử dụng một biến kiểu ```struct``` để lưu trữ trạng thái của các LED bằng cách sử dụng __bit fields__.  

```struct``` sẽ lưu trữ các biến theo thứ tự liên tục trong bộ nhớ nên ta sẽ sử dụng __bit fields__ để lưu trữ trạng thái của các LED theo từng bit. 

Mỗi __bit field__ sẽ biểu diễn trạng thái của một LED như vậy với bất kể số bit nào lẻ khác với 8, 16, 32, ... thì ta vẫn có thể lưu trữ trạng thái của các LED một cách hiệu quả. Điều này giúp giảm bộ nhớ cần sử dụng để lưu trữ trạng thái của các LED.

```C
// Định nghĩa một biến kiểu struct để lưu trữ trạng thái của các LED bằng cách sử dụng bit fields
typedef struct {
    uint8_t LED1 : 1;   
    uint8_t LED2 : 1;
    uint8_t LED3 : 1;
    uint8_t LED4 : 1;
    uint8_t LED5 : 1;
    uint8_t LED6 : 1;
    uint8_t LED7 : 1;
    uint8_t LED8 : 1;
} LEDStatus;
```
Ta vẫn sẽ sử dụng các kỹ thuật __Bitmask__ và các toán tử __Bitwise__ để xử lý các bit như ví dụ phía trên cho biến ```LEDStatus```.