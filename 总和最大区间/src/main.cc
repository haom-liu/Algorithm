#include "op.hpp"
#include <iostream>
#include <chrono>
#include <vector>

// 测试算法的执行时间
void test_algorithm(const std::string& name, const std::string& complexity, std::pair<size_t, size_t> (*func)(const std::vector<float>&), const std::vector<float>& input) {
    auto start = std::chrono::high_resolution_clock::now();
    auto result = func(input);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Algorithm: " << name << " (Complexity: " << complexity << ") - Time: " << elapsed.count() << " seconds\n";
    // std::cout << "Result: [" << result.first << ", " << result.second << "]\n";
}

int main(int argc, char const *argv[]) {
    // 使用命令行控制输入的文件名
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }
    std::string filename = argv[1];
    std::vector<float> input;
    handle_input(filename, input);

    // 测试各个算法
    // test_algorithm("op1", "O(N^3)", op1, input);
    test_algorithm("op2_1_1_2", "O(N^2)", op2_1_1_2, input);
    test_algorithm("op2_1_2", "O(N^2)", op2_1_2, input);
    test_algorithm("op2_2", "O(N) ~ O(N^2)", op2_2, input);
    test_algorithm("op3_1", "O(N)", op3_1, input);
    test_algorithm("op3_2", "O(N)", op3_2, input);
    test_algorithm("op4_1", "O(N log N)", op4_1, input);
    test_algorithm("op4_2", "O(N)", op4_2, input);

    return 0;
}
