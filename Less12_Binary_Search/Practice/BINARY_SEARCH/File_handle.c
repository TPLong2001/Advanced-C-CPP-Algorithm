/**********************************************************************************
 * @file    File_handle.c
 * @brief   Triển khai hàm đọc dữ liệu từ file CSV chứa thông tin người dùng và lưu vào danh sách liên kết.
 * @details File này mở file CSV, đọc từng dòng thông tin và phân tích dữ liệu,
 *          sau đó lưu thông tin người dùng vào danh sách liên kết.
 * @version 1.0
 * @date    2025-03-25
 * @author  LongTruong
 **********************************************************************************/
#include "File_handle.h"

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
 * @brief   Đọc dữ liệu từ file CSV và lưu thông tin người dùng vào Node.
 * @details Hàm này mở file CSV theo đường dẫn cung cấp, đọc từng dòng dữ liệu,
 *          phân tích và lưu vào cấu trúc `User`, sau đó lưu thông tin. Bộ nhớ
 *          cấp phát động sẽ được giải phóng ngay sau mỗi lần sử dụng.
 * @param   filename: Đường dẫn đến file CSV cần đọc.
 * @param   head: Con trỏ bậc 2 trỏ đến vị trí đầu danh sách liên kết.
 **/
void readCSV(const char *filename, Node **head)
{
    FILE *file = fopen(filename, "r");

    /* Kiểm tra xem file có mở thành công không */
    if (file == NULL)
    {
        printf("Cannot open file!\n");
    }

    char line[100];                                     /**< Bộ đệm để lưu từng dòng từ file CSV */

    /* Bỏ qua dòng tiêu đề */
    fgets(line, sizeof(line), file);                    /**< "Name, Age, Address, Phone Number" // "Name" '\0' */
    
    /* In tiêu đề bảng dữ liệu */
    // printf("%-20s %-5s\t  %-20s\t  %-15s\n", "Name", "Age", "Address", "Phone Number");

    /* Đọc từng dòng dữ liệu từ file CSV */
    while (fgets(line, sizeof(line), file))             /**<  ,40, 789 Pine St, 555-8765 */
    {
        User user;                                      /**< Biến lưu thông tin người dùng tạm thời */
        
        /* Tách tên từ dòng hiện tại */
        char *token = strtok(line, ",");
        while(*token == ' ')     token++;               /**< Loại bỏ khoảng trắng */ 
        user.name = (char*)malloc(strlen(token)+1);     /**< Cấp phát bộ nhớ cho tên */
        strcpy(user.name, token);

        /* Tách tuổi */
        token = strtok(NULL, ",");  // "40" -> '4' - 0x30 = 4, '0' - 0x30 = 0 , '4' -> (int)'4' = 52
        user.age = atoi(token);

        /* Tách địa chỉ */
        token = strtok(NULL, ",");
        while(*token == ' ')     token++;               /**< Loại bỏ khoảng trắng */ 
        user.addr = (char*)malloc(strlen(token)+1);     /**< Cấp phát bộ nhớ cho địa chỉ */
        strcpy(user.addr, token);

        /* Tách số điện thoại */
        token = strtok(NULL, ",");
        while(*token == ' ')     token++;               /**< Loại bỏ khoảng trắng */ 
        token[strcspn(token, "\n")] = '\0';             /**< Xóa ký tự xuống dòng nếu có */
        user.phone = (char*)malloc(strlen(token)+1);    /**< Cấp phát bộ nhớ cho số điện thoại */
        strcpy(user.phone, token);

        // Lưu vào danh sách liên kết
        add_node(head, user);

        /* Giải phóng bộ nhớ của các trường trong cấu trúc User */
        free_user(&user); 
    }

    fclose(file);   /**< Đóng file sau khi đọc xong */
}