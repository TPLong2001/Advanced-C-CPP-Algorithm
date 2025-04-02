#include <stdio.h>
#include <stdlib.h>

#define FILE_CREATE_FAILED -1

#define DATABASE_PATH "..\\Data\\Database.csv"

// đường dẫn tuyệt đối: "D\\Advance_C_Cpp\\"
// đường dẫn tương đối: "..\\Data\\Database.csv"

int main() 
{
    // Mở file để ghi, nếu chưa có sẽ tạo file mới
    FILE *file = fopen(DATABASE_PATH, "w");
    
    // Kiểm tra nếu file không mở được
    if (file == NULL) 
    {
        printf("Cannot create file.\n");
        return FILE_CREATE_FAILED;
    }

    // Ghi dòng tiêu đề vào file CSV
    fprintf(file, "Name, Age, Address, Phone Number\n");

    // Ghi các dòng thông tin vào file CSV
    fprintf(file, "Bob Johnson, 40, 789 Pine St, 555-8765\n", "hello world\n", 1, 3.14);
    fprintf(file, "Jane Smith, 25, 456 Oak St, 555-5678\n");
    fprintf(file, "John Doe, 30, 123 Main St, 555-1234\n");
    fprintf(file, "Trung, 22, 10 Ly Thuong Kiet, 037777\n");
    fprintf(file, "Hoang, 20, 23 Le Loi, 0123456\n");

    // Đóng file sau khi ghi
    fclose(file);

    printf("File created successfully\n");
    
    return 0;
}
