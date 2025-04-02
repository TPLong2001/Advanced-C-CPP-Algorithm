#Tên file thực thi
TARGET = binary_search

# Trình biên dịch
CC = gcc

# Cờ biên dịch
CFLAGS = -Wall -Wextra -std=c99

# Danh sách file nguồn
SRCS = 	main.c \
		File_handle.c \
		Binary_search_tree.c

# Danh sách file object
OBJS = $(SRCS:.c=.o)

# Mặc định build toàn bộ chương trình
all: $(TARGET)

# Build file thực thi từ file object (.o)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)


# Build file object từ file .c
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Lệnh giả
PHONY: clean run

# Xóa file .0 .exe
clean:
	rm -f $(OBJS) $(TARGET)

# Thực thi c trình
run: $(TARGET)
	./$(TARGET)