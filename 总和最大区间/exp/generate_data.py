import random

def generate_large_data(size, filename, chunk_size=100000):
    """
    生成大量数据并写入文件，采用流式写入方式，避免内存占用过高。
    
    :param size: 数据总量
    :param filename: 输出文件名
    :param chunk_size: 每次生成和写入的数据量
    """
    with open(filename, 'w') as f:
        for i in range(0, size, chunk_size):
            # 每次生成 chunk_size 个数据
            chunk = [random.uniform(-1000, 1000) for _ in range(min(chunk_size, size - i))]
            # 将数据写入文件，每个数据之间用空格分隔
            f.write(" ".join(map(str, chunk)) + " ")
            print(f"Generated {i + len(chunk)}/{size} data points...")
    
    # 去掉最后一个多余的空格
    with open(filename, 'rb+') as f:
        f.seek(-1, 2)  # 移动到文件末尾的前一个字节
        if f.read(1) == b' ':  # 如果最后一个字符是空格
            f.seek(-1, 2)
            f.truncate()  # 去掉最后一个空格

    print(f"Data generation complete. Saved to {filename}")

if __name__ == "__main__":
    # 生成1亿个浮点数
    generate_large_data(100000, "../test_data/data3")