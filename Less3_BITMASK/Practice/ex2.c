#include <stdio.h>
#include <stdint.h>


#define GENDER        1 << 0  // Bit 0: Giới tính (0 = Nữ, 1 = Nam)     0b00000001
#define TSHIRT        1 << 1  // Bit 1: Áo thun (0 = Không, 1 = Có)     0b00000010
#define HAT           1 << 2  // Bit 2: Nón (0 = Không, 1 = Có)         0b00000100
#define SHOES         1 << 3  // Bit 3: Giày (0 = Không, 1 = Có)        0b00001000
// Tự thêm tính năng khác
#define FEATURE1      1 << 4  // Bit 4: Tính năng 1                     0b00010000
#define FEATURE2      1 << 5  // Bit 5: Tính năng 2                     0b00100000
#define FEATURE3      1 << 6  // Bit 6: Tính năng 3                     0b01000000
#define FEATURE4      1 << 7  // Bit 7: Tính năng 4                     0b10000000

// Hàm bật/tắt tính năng
void enableFeature(uint8_t *features, uint8_t feature);
void disableFeature(uint8_t *features, uint8_t feature);

// Hàm kiểm tra tính năng đã được bật chưa
int isFeatureEnabled(uint8_t features, uint8_t feature);

// Hàm liệt kê các tính năng đã chọn
void listSelectedFeatures(uint8_t features);


int main() {
    uint8_t options = 0;

    // Thêm tính năng GENDER, TSHIRT, HAT, SHOES = 1
    enableFeature(&options, GENDER | TSHIRT | HAT | SHOES);

    // Xóa tính năng TSHIRT => TSIRT = 0
    disableFeature(&options, TSHIRT);

    // Liệt kê các tính năng đã chọn
    listSelectedFeatures(options);
    
    return 0;
}


void enableFeature(uint8_t *features, uint8_t feature) {
    *features |= feature;
}

void disableFeature(uint8_t *features, uint8_t feature) {
    *features &= ~feature;
}


int isFeatureEnabled(uint8_t features, uint8_t feature) {
    return (features & feature) != 0;
}


void listSelectedFeatures(uint8_t features) {
    printf("Selected Features:\n");

    if (features & GENDER) {
        printf("- Gender\n");
    }
    if (features & TSHIRT) {
        printf("- T-Shirt\n");
    }
    if (features & HAT) {
        printf("- Hat\n");
    }
    if (features & SHOES) {
        printf("- Shoes\n");
    }

    for (int i = 0; i < 8; i++)
    {
        printf("feature selected: %d\n", (features >> i) & 1);
    }
    

    // Thêm các điều kiện kiểm tra cho các tính năng khác
}