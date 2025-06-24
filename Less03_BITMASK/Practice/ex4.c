#include <stdio.h>
#include <stdint.h>

#define ENABLE 1
#define DISABLE 0

// Bây giờ thay vì sử dụng các biến với uint8_t, uint16_t, uint32_t, ... để lưu trữ trạng thái của các LED
// thì ta sẽ sử dụng một biến kiểu struct để lưu trữ trạng thái của các LED bằng cách sử dụng bit fields
// vì struct sẽ lưu trữ các biến theo thứ tự liên tục trong bộ nhớ nên ta sẽ sử dụng bit fields để lưu trữ trạng thái của các LED theo từng bit
// Mỗi bit field sẽ biểu diễn trạng thái của một LED như vậy với bất kể số bit nào lẻ khác với 8, 16, 32, ... thì ta vẫn có thể lưu trữ trạng thái của các LED một cách hiệu quả
// Điều này giúp giảm bộ nhớ cần sử dụng để lưu trữ trạng thái của các LED

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

// Hàm hiển thị trạng thái của tất cả các LED
void displayAllStatusLed(LEDStatus status) {
    uint8_t* statusPtr = (uint8_t*)&status;
        for (int j = 0; j < 8; j++) {
            printf("LED%d: %d\n", j+1, (*statusPtr >> j) & 1);
        }
    
}


int main() {
    // Khởi tạo trạng thái ban đầu của các LED 5 và 7 được bật
    LEDStatus ledStatus = {.LED7 = ENABLE, .LED5 = ENABLE};

    // Bật LED 1 và 3
    ledStatus.LED1 = ENABLE;
    ledStatus.LED3 = ENABLE;

    // Hiển thị trạng thái của tất cả các LED
    displayAllStatusLed(ledStatus);

    return 0;
}

