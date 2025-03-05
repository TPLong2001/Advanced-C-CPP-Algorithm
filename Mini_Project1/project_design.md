
---

# Module Management System - Thiết kế project

## 1. Mô tả project
Dự án xây dựng hệ thống quản lý nhiều module điện tử trong hệ thống giả lập như:
- ECU
- ABS
- LIGHT
- AIR CONDITIONER
- TEMPERATURE SENSOR

Mỗi module có thể bật/tắt, theo dõi trạng thái và xử lý lỗi tự động.

---
## 2. Cấu trúc file và thư mục
```
Automotive_Module_Manager/
├── main.c              // Chương trình chính
├── module_manager.c    // Xử lý danh sách module
├── module_manager.h    // Header file của module manager
├── bitmask_utils.c     // Hàm hỗ trợ bitmask
├── bitmask_utils.h     // Header file cho bitmask
├── function_handler.c  // Xử lý con trỏ hàm
├── function_handler.h  // Header file của function handler
├── error_handler.c     // Xử lý lỗi
├── error_handler.h     // Header file xử lý lỗi

```

## 2. Phân tích thiết kế

### Mục tiêu thiết kế hệ thống

Chương trình quản lý nhiều module và phải có khả năng:

* Thêm/Xóa module vào danh sách (dùng cấp phát động).
* Quản lý trạng thái ON/OFF, lỗi, cảnh báo (bitmask).
* Sử dụng function pointer để điều khiển module.
* Dùng setjmp/longjmp để xử lý lỗi khi module gặp sự cố.
* Tối ưu lưu trữ dữ liệu module bằng struct và union.

### Các thành phần chính và nhiệm vụ
| Thành phần       | Vai trò | Nhiệm vụ              |
|----------------------|--------|------------------------|
| `main`            | Chương trình chính | Khởi tạo module, vòng lặp xử lý, kiểm tra lỗi, hiển thị thông tin.| 
| `module_manager`  | Quản lý danh sách module và điều khiển| Thêm/xóa module động, cập nhật trạng thái, xuất danh sách. |
| `function_handler`| Điều khiển module thông qua function pointer | Bật/tắt/kiểm tra trạng thái module.|
|  `bitmask_utils`  | Xử lý trạng thái bằng `bitmask` | Thao tác bật, tắt, kiểm tra trạng thái bằng `bitmask`.|
| `error_handler`   | Phát hiện, xử lý ngoại lệ bằng `setjmp/longjmp`. | Phát hiện lỗi/cảnh báo và xử lý luông an toàn. |

---

### Thiết kế cấu trúc dữ liệu

__Struct Module__ để lưu thông tin module gồm: __ID, tên, trạng thái, hành động điều khiển__.
```c
typedef struct Module{
    int ID;
    char name[50];
    StatusModule statusModule;
    void (*controlAction)(void *, void *);
}Module;
```
__Union__ để tối ưu bộ nhớ trạng thái:
```c
typedef union StatusModule{
    uint8_t allStatus;
    struct{
        uint8_t on : 1;
        uint8_t error : 1;
        uint8_t warning : 1;
    } Status;
}StatusModule;
```

__Quản lý danh sách module__: 
* Sử dụng con trỏ `Module *moduleList` để lưu danh sách quản lý module.
* `uint8_t sizeList` lưu kích thước danh sách.
* `uint8_t **arrayStatus` lưu trạng thái của từng module, phục vụ xử lý lỗi.
```c
Module *moduleList = NULL;
uint8_t sizeList = 0;
uint8_t **arrayStatus = NULL;

```
### Triển khai chức năng quản lý module

__Hàm thêm module__ (`addModule`)

* Nếu danh sách rỗng → cấp phát mới.

* Nếu đã có → dùng realloc để mở rộng mảng.

* Thêm module vào cuối danh sách.

__Hàm xóa module__ (`deleteModule`)

* Tìm module cần xóa theo ID.

* Đưa module cuối cùng vào vị trí module bị xóa để tránh dịch mảng.

* Dùng realloc thu nhỏ mảng.

__Hàm kiểm tra trạng thái module__ (`updateStatus`)

* Cập nhật trạng thái từng module để kiểm tra lỗi, cảnh báo và hiển thị.

### Xử lý lỗi với setjmp/longjmp

__Mục tiêu:__

* Cảnh báo lỗi.

* Không để chương trình bị crash.

* Quay về trạng thái an toàn, tiếp tục luồng hệ thống hoặc reset.

__Triển khai:__

Sử dụng cơ chế `setjmp/longjmp` để xử lý ngoại lệ.

```c
extern int exception;
extern jmp_buf buf;

#define TRY         if((exception = setjmp(buf)) == 0)
#define CATCH(x)    else if(exception == x)
#define THROW(x)    longjmp(buf, x)

#define WARNING  THROW(1)
#define ERROR    THROW(2)
```
__Cách hoạt động:__

Trong `main`, chương trình kiểm tra trạng thái các module.

* Nếu phát hiện lỗi(`ERROR`) → gọi longjmp() để nhảy đến điểm an toàn xử lý lỗi.

* Nếu có cảnh báo (`WARNING`) → thông báo nhưng không dừng chương trình.
```c
TRY{                                            // bắt đầu xử lý ngoại lệ
            printf("Checking module status ...\n");
            updateStatusList();

            handleException(sizeList, arrayStatus);
        }
        CATCH(1){                                       // cảnh báo
            // xử lý cảnh báo
        }CATCH(2){ // lỗi
            goto OUT;
        }
```

## 3. Sử dụng kỹ thuật

### Bitmask
- Tối ưu quản lý trạng thái module qua biến `uint8_t allStatus`.
- Sử dụng các macro để tạo `bitmask`:
```c
  #define STATUS_ON        (1 << 0)
  #define STATUS_ERROR     (1 << 1)
  #define STATUS_WARNING   (1 << 2)
```
Sử dụng `bitmask` và `bitwise` để __set, clear hoặc kiểm tra trạng thái__:
```c
void setStatus(uint8_t *statusModule, uint8_t status);
void clearStatus(uint8_t *statusModule, uint8_t status);
uint8_t checkStatus(uint8_t *statusModule, uint8_t status);
```

### Function Pointer

__Function pointer__ giúp chỉ định hành động cụ thể cho từng module mà không cần sử dụng nhiều hàm giống nhau được khởi tạo sẵn trong từng `Module`.
```c
void (*controlAction)(void *, void *);
```
Sau đó __function pointer__ sẽ được gán hành động và thực hiện hành động đó:

```c
// gán hành động và thực hiện bật module
void turnOnModule(Module *module){
    module->controlAction = turnOn;
    module->controlAction(&((module->statusModule).allStatus), module->name);
}
```
Có thể gán các hàm hành động khác nhau dưới đây:
```c
void turnOn(void *statusModule, void *name);
void turnOff(void *statusModule, void *name);
void checkModuleStatus(void *statusModule, void *name);
```

### Setjmp/Longjmp

Kỹ thuật setjmp/longjmp cho phép lưu điểm khôi phục trong chương trình và quay lại đó nếu phát hiện lỗi.  

__Triển khai:__
* Dùng `TRY` để bắt đầu vùng mã cần bảo vệ.
* Nếu lỗi, gọi `THROW` để quay về `TRY`.
* Xử lý lỗi trong `CATCH`.



