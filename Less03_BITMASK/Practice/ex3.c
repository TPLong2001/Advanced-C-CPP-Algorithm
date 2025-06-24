#include <stdio.h>

// Mỗi đèn LED được biểu diễn bằng một bit và có 4 đèn led lên được biểu diễn bằng 4 bit
#define LED1 1 << 0     // 0001
#define LED2 1 << 1     // 0010
#define LED3 1 << 2     // 0100
#define LED4 1 << 3     // 1000

// Hàm bật đèn LEDx
void enableLED(unsigned int *GPIO_PORT, unsigned int LED) {
    *GPIO_PORT |= LED;
}

// Hàm tắt đèn LEDx
void disableLED(unsigned int *GPIO_PORT, unsigned int LED) {
    *GPIO_PORT &= ~LED;
}


int main() {
    unsigned int GPIO_PORT = 0; // Giả sử là biến điều khiển cổng GPIO chứa các bit để điều khiển các đèn LED

    // Bật LED1 và LED3
    enableLED(&GPIO_PORT, LED1 | LED3);

    // Kiểm tra trạng thái của đèn LED1
    if (GPIO_PORT & LED1 )
    {
        printf("LED1 is on\n");
    }

    // Kiểm tra trạng thái của đèn LED2
    if (GPIO_PORT & LED2)
    {
        printf("LED2 is on\n");
    }

    // Kiểm tra trạng thái của đèn LED3
    if (GPIO_PORT & LED3)
    {
        printf("LED3 is on\n");
    }
    
    // Tắt LED1 và bật LED2
    disableLED(&GPIO_PORT, LED1);
    enableLED(&GPIO_PORT, LED2);

    // Kiểm tra trạng thái của đèn LED1
    if (GPIO_PORT & LED1 )
    {
        printf("LED1 is on\n");
    }

    // Kiểm tra trạng thái của đèn LED2
    if (GPIO_PORT & LED2)
    {
        printf("LED2 is on\n");
    }

    // Kiểm tra trạng thái của đèn LED3
    if (GPIO_PORT & LED3)
    {
        printf("LED3 is on\n");
    }

    // Cập nhật trạng thái của GPIO_PORT tương ứng với hardware ...

    return 0;
}
