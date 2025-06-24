#include <stdio.h>
#include <stdint.h>

// cần 2 bit để lưu trữ màu sắc của xe 0 -> 3
#define COLOR_RED 0	    // 0b 0000 0000
#define COLOR_BLUE 1    // 0b 0000 0001
#define COLOR_BLACK 2   // 0b 0000 0010
#define COLOR_WHITE 3   // 0b 0000 0011

// cần 2 bit để lưu trữ công suất của xe 0 -> 2
#define POWER_100HP 0   // 0b 0000 0000
#define POWER_150HP 1   // 0b 0000 0001
#define POWER_200HP 2   // 0b 0000 0010

// cần 1 bit để lưu trữ loại động cơ 0 -> 1
#define ENGINE_1_5L 0   // 0b 0000 0000
#define ENGINE_2_0L 1   // 0b 0000 0001

typedef uint8_t CarColor;
typedef uint8_t CarPower;
typedef uint8_t CarEngine;


// Thêm các bit masks khác tùy thuộc vào tùy chọn
// 3 bit cho các tùy chọn bổ sung
#define SUNROOF_MASK 1 << 0         // 0001
#define PREMIUM_AUDIO_MASK 1 << 1   // 0010
#define SPORTS_PACKAGE_MASK 1 << 2  // 0100



// Sử dụng bit fields để lưu trữ toàn bộ thông tin của xe theo các bit fields
typedef struct {
    uint8_t additionalOptions : 3;  // 3 bits cho các tùy chọn bổ sung
    CarColor color : 2;             // 2 bits cho màu sắc
    CarPower power : 2;             // 2 bits cho công suất
    CarEngine engine : 1;           // 1 bit cho loại động cơ
} CarOptions;

// Khi đó tống số bit cần sử dụng để lưu trữ thông tin của xe là 8 bit = 1 byte, khi đó bit mask của từng phần tử sẽ như sau:
// SUNROOF_MASK                 = 0b 00000(001)
// PREMIUM_AUDIO_MASK           = 0b 00000(010)
// SPORTS_PACKAGE_MASK          = 0b 00000(100)
// COLOR_RED                    = 0b 000(00)000
// COLOR_BLUE                   = 0b 000(01)000
// COLOR_BLACK                  = 0b 000(10)000
// COLOR_WHITE                  = 0b 000(11)000
// POWER_100HP                  = 0b 0(00)00000
// POWER_150HP                  = 0b 0(01)00000
// POWER_200HP                  = 0b 0(10)00000
// ENGINE_1_5L                  = 0b (0)0000000
// ENGINE_2_0L                  = 0b (1)0000000


// Hàm cấu hình thông tin của xe
void configureCar(CarOptions *car, CarColor color, CarPower power, CarEngine engine, uint8_t options) {
    car->color = color;
    car->power = power;
    car->engine = engine;
    car->additionalOptions = options;
}

// Hàm bật tùy chọn bổ xung cho xe ( 3 bit đầu)
void setOption(CarOptions *car, uint8_t optionMask) {
    car->additionalOptions |= optionMask;
}

// Hàm tắt tùy chọn bổ xung cho xe ( 3 bit đầu)
void unsetOption(CarOptions *car, uint8_t optionMask) {
    car->additionalOptions &= ~optionMask;
}

// Hàm hiển thị thông tin của xe
void displayCarOptions(const CarOptions car) {
    const char *colors[] = {"Red", "Blue", "Black", "White"};
    const char *powers[] = {"100HP", "150HP", "200HP"};
    const char *engines[] = {"1.5L", "2.0L"};

    printf("Car Configuration: \n");
    printf("Color: %s\n", colors[car.color]);
    printf("Power: %s\n", powers[car.power]);
    printf("Engine: %s\n", engines[car.engine]);
    printf("Sunroof: %s\n", (car.additionalOptions & SUNROOF_MASK) ? "Yes" : "No");
    printf("Premium Audio: %s\n", (car.additionalOptions & PREMIUM_AUDIO_MASK) ? "Yes" : "No");
    printf("Sports Package: %s\n", (car.additionalOptions & SPORTS_PACKAGE_MASK) ? "Yes" : "No");
}

int main() {
    CarOptions myCar;
    configureCar(&myCar, COLOR_BLACK, POWER_150HP, ENGINE_2_0L, 0); 
	
    // Bật các tùy chọn bổ xung cho xe
    setOption(&myCar, SUNROOF_MASK);
    setOption(&myCar, PREMIUM_AUDIO_MASK);
    
    // Hiển thị thông tin của xe
    displayCarOptions(myCar);

    // Tắt tùy chọn bổ xung cho xe
    unsetOption(&myCar, PREMIUM_AUDIO_MASK); 
    // Hiển thị thông tin của xe
    displayCarOptions(myCar);

    // Kiểm tra kích thước của biến CarOptions chính là 1 byte
    printf("size of my car: %d\n", sizeof(CarOptions));

    return 0;
}

