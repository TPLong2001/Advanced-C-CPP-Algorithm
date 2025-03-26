# Đây là file makefile để biên dịch chương trình Single Linked List

# Tên file thực thi
TARGET = linked_list

# Trình biên dịch
CC = gcc

# Cờ biên dịch
# -Wall: hiển thị tất cả các cảnh báo
# -Wextra: hiển thị thêm một số cảnh báo khác
# -std=c99: sử dụng chuẩn C99
CFLAGS = -Wall -Wextra -std=c99

# Danh sách các file nguồn
SRC = 	LinhkedList.c \
		main.c

# Tạo danh sách các file object (.o)
# $(SRC:.c=.o) sẽ thay thế tất cả các phần mở rộng .c thành .o
OBJ = $(SRC:.c=.o)

# Mục mặc định để build toàn bộ
# all: $(TARGET) sẽ biên dịch tất cả các file .c thành file .o và sau đó liên kết các file .o thành file thực thi
all: $(TARGET)

# Build file thực thi từ các object
# $(TARGET):$(OBJ) sẽ liên kết các file .o thành file thực thi
# $(CC) $(CFLAGS) -o $(TARGET) $(OBJ) sẽ biên dịch các file .o thành file thực thi
$(TARGET):$(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Quy tắc biên dịch từng file .c thành .o
# %.o: %.c sẽ biên dịch từng file .c thành file .o
# $(CC) $(CFLAGS) -c $< -o $@ sẽ biên dịch file .c thành file .o
# Đích, Nguồn              ( (Đích - $@), (Nguồn - $<) )
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Lệnh giả phân biệt lệnh clean, run không phải là tên file
# .PHONY: clean run sẽ không xem lệnh clean, run là tên file
.PHONY: clean run

# Dọn dẹp file build
# rm -f $(OBJ) $(TARGET) sẽ xóa các file .o và file thực thi
clean:
	rm -f $(OBJ) $(TARGET)

# Chạy tệp thực thi
# run: $(TARGET) sẽ chạy file thực thi
run: $(TARGET)
	./$(TARGET)

