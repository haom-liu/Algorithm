CC = g++
CFLAGS = -Wall -Iinclude
SRC_DIR = src
BIN_DIR = bin

# 目标：生成可执行文件
all: $(BIN_DIR)/main

# 生成可执行文件
$(BIN_DIR)/main: $(SRC_DIR)/main.cc 
	$(CC) $(CFLAGS) $^ -o $@

# 清理生成的文件
clean:
	rm -f $(BIN_DIR)/main