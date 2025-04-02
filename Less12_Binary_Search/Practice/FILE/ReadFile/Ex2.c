/***************************************************************************
 * @file    DatabaseReader.c
 * @brief   Đọc dữ liệu từ file CSV chứa thông tin người dùng và in ra màn hình.
 * @details File này mở file CSV, đọc từng dòng thông tin và phân tích dữ liệu,
 *          sau đó in ra thông tin người dùng với định dạng đẹp mắt. Bộ nhớ cấp phát
 *          động được giải phóng ngay sau khi sử dụng để tránh rò rỉ.
 * @version 1.0
 * @date    2024-11-08
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE_PATH "..\\Data\\Database.csv"   /**< Đường dẫn đến file CSV chứa dữ liệu */

/**
 * @struct  User
 * @brief   Cấu trúc lưu thông tin người dùng.
 * @details Cấu trúc này chứa tên, tuổi, địa chỉ và số điện thoại của người dùng.
 */
typedef struct {
    char *name;      /**< Tên của người dùng */
    int age;         /**< Tuổi của người dùng */
    char *addr;      /**< Địa chỉ của người dùng */
    char *phone;     /**< Số điện thoại của người dùng */
} User;

/**
 * @brief   Giải phóng bộ nhớ cho các trường của cấu trúc User.
 * @details Hàm này giải phóng bộ nhớ đã cấp phát động cho các trường `name`, `addr`, và `phone` của cấu trúc `User`.
 * @param   user: Con trỏ đến cấu trúc `User` cần giải phóng.
 */
void free_user(User *user)
{
    free(user->name);    /**< Giải phóng bộ nhớ cho trường `name` */
    free(user->addr);    /**< Giải phóng bộ nhớ cho trường `addr` */
    free(user->phone);   /**< Giải phóng bộ nhớ cho trường `phone` */
}

/**
 * @brief   Đọc dữ liệu từ file CSV và in thông tin người dùng.
 * @details Hàm này mở file CSV theo đường dẫn cung cấp, đọc từng dòng dữ liệu,
 *          phân tích và lưu vào cấu trúc `User`, sau đó in ra thông tin. Bộ nhớ
 *          cấp phát động sẽ được giải phóng ngay sau khi sử dụng.
 * @param   filename: Đường dẫn đến file CSV cần đọc.
 */
void readCSV(const char *filename)
{
    FILE *file = fopen(filename, "r");  /**< Con trỏ file để truy cập file CSV */

    /* Kiểm tra xem file có mở thành công không */
    if (file == NULL)
    {
        printf("Cannot open file!\n");
        return;
    }

    char name[50];  /**< Bộ đệm tạm cho tên người dùng */
    char addr[50];  /**< Bộ đệm tạm cho địa chỉ */
    char phone[20]; /**< Bộ đệm tạm cho số điện thoại */
    int age;        /**< Biến lưu tuổi người dùng */

    /* Bỏ qua dòng tiêu đề */
    fscanf(file, "%*[^\n]\n");

    /* In tiêu đề bảng dữ liệu */
    printf("%-20s %-5s\t  %-20s\t  %-15s\n", "Name", "Age", "Address", "Phone Number");

    /* Đọc dữ liệu từ file cho đến khi hết file */
    while (fscanf(file, "%49[^,],%d,%49[^,],%19[^\n]\n", name, &age, addr, phone) == 4)
    {
        User user;  /**< Biến lưu thông tin người dùng tạm thời */
        
        /* Sao chép tên từ bộ đệm tạm vào cấu trúc User */
        user.name = (char*)malloc(strlen(name) + 1);  /**< Cấp phát bộ nhớ cho tên */
        strcpy(user.name, name);

        /* Lưu tuổi vào cấu trúc User */
        user.age = age;

        /* Sao chép địa chỉ từ bộ đệm tạm vào cấu trúc User */
        user.addr = (char*)malloc(strlen(addr) + 1);  /**< Cấp phát bộ nhớ cho địa chỉ */
        strcpy(user.addr, addr);

        /* Sao chép số điện thoại từ bộ đệm tạm vào cấu trúc User */
        user.phone = (char*)malloc(strlen(phone) + 1);  /**< Cấp phát bộ nhớ cho số điện thoại */
        strcpy(user.phone, phone);

        /* In thông tin người dùng */
        printf("%-20s %-5d\t %-20s\t %-15s\n", user.name, user.age, user.addr, user.phone);

        /* Giải phóng bộ nhớ của các trường trong cấu trúc User */
        free_user(&user);
    }

    fclose(file);  /**< Đóng file sau khi đọc xong */
}


int main(int argc, char const *argv[])
{   
    readCSV(DATABASE_PATH);   /**< Gọi hàm đọc dữ liệu CSV */
    return 0;                 /**< Trả về 0 nếu thành công */
}

/**
 * fscanf trả về số lượng giá trị được đọc thành công.
 * "%*[^\n]\n" : bỏ qua toàn bộ dòng đầu tiên (dòng tiêu đề) bằng cách đọc đến ký tự xuống dòng (\n) mà không lưu vào bộ nhớ
 * "%49[^,]"   : Đọc tối đa 49 ký tự cho đến khi gặp dấu phẩy.
 * "%19[^\n]\n": Đọc tối đa 19 ký tự cho đến khi gặp ký tự xuống dòng \n
 */