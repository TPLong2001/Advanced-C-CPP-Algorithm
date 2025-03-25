# Tên của chương trình  (main)
TARGET = queue_ring

# Trình biên dịch
CC = gcc

# Cờ biên dịch
CFLAGS = -Wall -Wextra -std=c99

# Danh sách các file nguồn
SRCS = main.c \
	   queue_ring.c

# Tạo danh sách các file object (.o)
OBJS = $(SRCS:.c=.o)

# Mục mặc định để build toàn bộ
all: $(TARGET)

# Build file thực thi từ các object
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Quy tắc biên dịch từng file .c thành .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Lệnh giả phân biệt lệnh clean, run không phải là tên file
.PHONY: clean run

# Dọn dẹp file build

clean:
	rm -f $(OBJS) $(TARGET)


# Chạy tệp thực thi
run: $(TARGET)
	./$(TARGET)