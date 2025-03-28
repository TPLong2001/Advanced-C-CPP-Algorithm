
# Tên 
TARGET = parse_json

# Trình biên dịch
CC = gcc

# Cờ biên dịch
CFLAGS = -Wall -Wextra -std=c99

# Danh sách các file nguồn
SRCS = 	main.c \
		json.c

# Tạo danh sách các file object
OBJS =  $(SRCS:.c=.o)

# Mặc định build toàn bộ chương trình
all: $(TARGET)

# Build file thực thi object(.o)
$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Build file .o từ file .c
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Thông lệnh mã giả
.PHONY: clean run

# Xóa file .o và .exe
clean:
	rm -f $(OBJS) $(TARGET)

# chạy chương trình
run: $(TARGET)
	./$(TARGET)