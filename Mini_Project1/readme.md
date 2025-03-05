# MINI-PROJECT: QUẢN LÝ TRẠNG THÁI MODULE TRONG HỆ THỐNG Ô TÔ

## Mô tả

Project mô phỏng quản lý danh sách module (ECU, ABS, LIGHT, AIR CONDITIONER, TEMPERATURE SENSOR), quản lý trạng thái, xử lý lỗi bằng bitmask, struct & union, function pointer, setjmp/longjmp, và cấp phát động (malloc/free).

## Cách build và chạy chương trình

### 1. Cách build chương trình.

Đầu tiên vào file "Automotive_Module_Manager" nơi chứa "Makefile" và source code của hệ thống.  
__Mở cmd/ Terminal hoặc GIT BASH.__    
Chạy lệnh build chương trình như sau:
```bash
make
```
Nếu bạn __sử dụng MinGW__ thì chạy:
```bash
mingw32-make
```
### 2. Cách chạy chương trình

Sau đó __chạy file thực thi chương trình__:
```bash
./automotive_manager
```


