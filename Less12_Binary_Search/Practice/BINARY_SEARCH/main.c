#include "File_handle.h"
 
 int main()
 {
     Node *head = NULL;

     
     /**
      * @brief   Chọn hàm sắp xếp.
      */
     compareFunction = conpareByPhoneNumber;


     /**
      * @brief   Duyệt file và add node.
      */
     readCSV(DATABASE_PATH, &head);
 
 
     /**
      * @brief   In danh sách liên kết.
      */
     print_list(head);
 
     /**
      * @brief   Chuyển danh sách liên kết thành cây nhị phân tìm kiếm (BST).
      */
     CenterPoint *ptr = centerPoint(head);
    
     User user = {
        .name = "John Doe",
        .age = 30,
        .addr = "123 Main St",
        .phone = "555-1234"
     };

     print_user(user);

     /**
      * @brief   Thực hiện tìm kiếm nhị phân trong cây BST.
      * @details Tìm kiếm giá trị ngẫu nhiên vừa được thêm vào danh sách.
      */
     CenterPoint *result = binarySearch(ptr, user);
     if (result != NULL)
     {
          printf("Tìm thấy User\n");
          print_user(result->user);
     }
     else
     {
          printf("Không tìm thấy User.\n");
     }
     return 0;
 }
 
 