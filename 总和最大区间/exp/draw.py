import matplotlib.pyplot as plt

filename = '../test_data/data1'
# 从文件读取数组数据，元素按空格分隔, 只有一行
data = []
with open(filename, 'r') as f:
    data = list(map(float, f.readline().split()))
        
# 计算前缀和
prefix_sum = []
current_sum = 0
for value in data:
    current_sum += value
    prefix_sum.append(current_sum)

# 绘制折线图
plt.figure(figsize=(10, 6))
plt.plot(prefix_sum, marker='o', linestyle='-', color='b')

# 在每个点标注数值
for i, value in enumerate(prefix_sum):
    plt.text(i, value, f'{value:.2f}', ha='center', va='bottom', fontsize=12)

# 添加标题和标签
plt.title('Sum', fontsize=16)
plt.xlabel('j', fontsize=12)
plt.ylabel('value', fontsize=12)
plt.xticks(range(len(prefix_sum)))  # 设置 x 轴刻度
plt.grid(True, linestyle='--', alpha=0.6)

# 显示图表
# plt.show()
# 保存图片
plt.savefig('img/sum1.png')