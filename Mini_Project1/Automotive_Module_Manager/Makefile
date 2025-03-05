# Trình biên dịch
CC = gcc

# Cờ biên dịch
CFLAGS = -Wall -Wextra -std=c99

# Tên file thực thi
TARGET = automotive_manager

# Danh sách các file nguồn
SRCS = main.c \
       module_manager.c \
       bitmask_utils.c \
       function_handler.c \
       error_handler.c

# Tạo danh sách các file object (.o)
OBJS = $(SRCS:.c=.o)

# Mục mặc định để build toàn bộ
all: $(TARGET)

# Build file thực thi từ các object
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Quy tắc biên dịch từng file .c thành .o
# Đích, Nguồn              ( (Đích - $@), (Nguồn - $<) )
# lệnh thực thi             
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Lệnh giả phân biệt lệnh clean, run không phải là tên file
.PHONY: clean run

# Dọn dẹp file build
clean:
	rm -f $(OBJS) $(TARGET)

# Chạy tệp thực thi 
#run: $(TARGET)
#       ./$(TARGET)

# chạy chương trình

# gõ "make" để biên dịch và chạy chương trình
#gcc -Wall -Wextra -std=c99 -c main.c -o main.o
#gcc -Wall -Wextra -std=c99 -c module_manager.c -o module_manager.o
#gcc -Wall -Wextra -std=c99 -c bitmask_utils.c -o bitmask_utils.o
#gcc -Wall -Wextra -std=c99 -c function_handler.c -o function_handler.o
#gcc -Wall -Wextra -std=c99 -c error_handler.c -o error_handler.o
#gcc -Wall -Wextra -std=c99 -o automotive_manager main.o module_manager.o bitmask_utils.o function_handler.o error_handler.o

#gõ "make clean" để xóa file build
#rm -f main.o module_manager.o bitmask_utils.o function_handler.o error_handler.o automotive_manager

#gõ "make run" để chạy chương trình
#./automotive_manager
