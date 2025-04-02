/*******************************************************************************
 * @file    Ex1.c
 * @brief   Đọc dữ liệu từ file CSV chứa thông tin người dùng và in ra màn hình.
 * @details File này mở file CSV, đọc từng dòng thông tin và phân tích dữ liệu,
 *          sau đó in ra thông tin người dùng.
 * @version 1.0
 * @date    2024-11-08
 * @author  Anh Nguyen
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE_PATH "..\\Data\\Database.csv"  /**< Đường dẫn đến file CSV chứa dữ liệu */


/**
 * @struct  User
 * @brief   Cấu trúc lưu thông tin người dùng.
 * @details Cấu trúc này chứa tên, tuổi, địa chỉ và số điện thoại của người dùng.
 */
typedef struct
{
    char *name;     /**< Tên của người dùng */
    int   age;      /**< Tuổi của người dùng */
    char *addr;     /**< Tuổi của người dùng */
    char *phone;    /**< Số điện thoại của người dùng */
} User;


/**
 * @brief   Giải phóng bộ nhớ cho các trường của cấu trúc User.
 * @details Hàm này giải phóng bộ nhớ đã cấp phát động cho các member của cấu trúc `User`.
 * @param   user: Con trỏ đến cấu trúc `User` cần giải phóng.
 */
void free_user(User *user)
{
    free(user->name);
    free(user->addr);
    free(user->phone);
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
    FILE *file = fopen(filename, "r");

    /* Kiểm tra xem file có mở thành công không */
    if (file == NULL)
    {
        printf("Cannot open file!\n");
    }

    char line[100]; /**< Bộ đệm để lưu từng dòng từ file CSV */

    /* Bỏ qua dòng tiêu đề */
    fgets(line, sizeof(line), file);    // "Name, Age, Address, Phone Number" // "Name" '\0'
    

    /* In tiêu đề bảng dữ liệu */
    printf("%-20s %-5s\t  %-20s\t  %-15s\n", "Name", "Age", "Address", "Phone Number");

    /* Đọc từng dòng dữ liệu từ file CSV */
    while (fgets(line, sizeof(line), file)) //  ,40, 789 Pine St, 555-8765
    {
        User user;  /**< Biến lưu thông tin người dùng tạm thời */
        
        /* Tách tên từ dòng hiện tại */
        char *token = strtok(line, ",");
        user.name = (char*)malloc(strlen(token)+1);     /**< Cấp phát bộ nhớ cho tên */
        strcpy(user.name, token);


        /* Tách tuổi */
        token = strtok(NULL, ",");  // "40" -> '4' - 0x30 = 4, '0' - 0x30 = 0 , '4' -> (int)'4' = 52
        user.age = atoi(token);


        /* Tách địa chỉ */
        token = strtok(NULL, ",");
        user.addr = (char*)malloc(strlen(token)+1);     /**< Cấp phát bộ nhớ cho địa chỉ */
        strcpy(user.addr, token);


        /* Tách số điện thoại */
        token = strtok(NULL, ",");
        user.phone = (char*)malloc(strlen(token)+1);    /**< Cấp phát bộ nhớ cho số điện thoại */
        strcpy(user.phone, token);


        /* In thông tin người dùng */
        printf("%-20s %-5d\t %-20s\t %-15s\n", user.name, user.age, user.addr, user.phone);


        /* Giải phóng bộ nhớ của các trường trong cấu trúc User */
        free_user(&user);
    }

    fclose(file);   /**< Đóng file sau khi đọc xong */
}

int main(int argc, char const *argv[])
{   
    readCSV(DATABASE_PATH);

    // int a = (int)'4';

    // printf("%d\n", a);

    return 0;
}
