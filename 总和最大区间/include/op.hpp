// Description: 一维数组的最大子段和问题，给定一个一维数组，求出一个区间，使得区间内的元素和最大。
#pragma once

#include "input.hpp"
#include <cassert>

// 三重循环，时间复杂度O(N^3)
std::pair<size_t, size_t> op1(const std::vector<float>& input) {
    assert(!input.empty());
    auto maxx = input[0];
    size_t left = 0, right = 0;
    for (size_t i = 0; i < input.size(); ++i)
        for (size_t j = i; j < input.size(); ++j) {
            float sum = 0;
            for (auto k = i; k <= j; ++k) {
                sum += input[k];
                if (sum > maxx) {
                    maxx = sum;
                    left = i;
                    right = j;
                }
            }
        }
    return {left, right};
}

// 二重循环，时间复杂度O(N^2)
std::pair<size_t, size_t> op2_1_1_1(std::vector<float>& input) {
    // 直接使用原来数组空间记录前缀和，原数组信息会被覆盖
    assert(!input.empty());
    for (size_t i = 1; i < input.size(); ++i) input[i] += input[i - 1];
    auto maxx = input[0];
    size_t left = 0, right = 0;
    for (size_t i = 0; i < input.size(); ++i)
        for (size_t j = i; j < input.size(); ++j) {
            // 使用前缀和计算区间和，时间复杂度O(1)
            auto sum = input[j] - (i == 0 ? 0 : input[i - 1]);
            if (sum > maxx) {
                maxx = sum;
                left = i;
                right = j;
            }
        }
    return {left, right};
}

std::pair<size_t, size_t> op2_1_1_2(const std::vector<float>& input) {
    // 使用额外数组记录前缀和，原数组信息不会被覆盖，空间复杂度O(N)
    assert(!input.empty());
    std::vector<float> prefix_sum(input.size(), 0);
    prefix_sum[0] = input[0];
    for (size_t i = 1; i < input.size(); ++i) prefix_sum[i] = prefix_sum[i - 1] + input[i];
    auto maxx = input[0];
    size_t left = 0, right = 0;
    for (size_t i = 0; i < input.size(); ++i)
        for (size_t j = i; j < input.size(); ++j) {
            // 使用前缀和计算区间和，时间复杂度O(1)
            auto sum = prefix_sum[j] - (i == 0 ? 0 : prefix_sum[i - 1]); 
            if (sum > maxx) {
                maxx = sum;
                left = i;
                right = j;
            }
        }
    return {left, right};
}

// 使用一个变量记录中间计算结果，就无需从头遍历求区间和，空间复杂度O(1)
std::pair<size_t, size_t> op2_1_2(const std::vector<float>& input) {
    assert(!input.empty());
    auto maxx = input[0];
    size_t left = 0, right = 0;
    for (size_t i = 0; i < input.size(); ++i) {
        float sum = 0;
        for (size_t j = i; j < input.size(); ++j) {
            sum += input[j];
            if (sum > maxx) {
                maxx = sum;
                left = i;
                right = j;
            }
        }
    }
    return {left, right};
}


// 正向遍历数组，记录前缀和，找到最大值，为右端点，然后反向遍历找到最小值，确立左端点。之后对下一段区间重复上述过程，最好情况时间复杂度O(N)，最坏情况时间复杂度O(N^2)
std::pair<size_t, size_t> op2_2(const std::vector<float>& input) {
    assert(!input.empty());
    // 求前缀和
    std::vector<float> prefix_sum(input.size() + 1, 0);
    
    // 为了方便，下标从1开始，prefix_sum[0] = 0
    for (size_t i = 1; i <= input.size(); ++i) prefix_sum[i] = prefix_sum[i - 1] + input[i - 1];
    // 从头开始遍历，找到前缀和的最大值
    auto maxx = prefix_sum[1];
    size_t left = 0, right = 0;
    // 记录最大值的位置
    size_t max_pos = 1;
    while (max_pos < prefix_sum.size() - 1) {
        auto pre_pos = max_pos;
        auto cur_maxx = prefix_sum[max_pos + 1];
        for (size_t j = max_pos + 1; j < prefix_sum.size(); ++j) {
            if (prefix_sum[j] >= cur_maxx) {
                cur_maxx = prefix_sum[j];
                max_pos = j;
            }
        }
        // 从最大值位置开始反向遍历，找到前缀和的最小值
        auto minn = prefix_sum[max_pos];
        size_t min_pos = max_pos;
        for (size_t i = min_pos; i >= pre_pos; --i) {
            if (prefix_sum[i - 1] < minn) {
                minn = prefix_sum[i - 1];
                min_pos = i;
            }
        }
        if (prefix_sum[max_pos] - prefix_sum[min_pos - 1] > maxx) {
            maxx = prefix_sum[max_pos] - prefix_sum[min_pos - 1];
            left = min_pos;
            right = max_pos;
        }
    }
    return {left - 1, right - 1};
}

// 优化op2_2，时间复杂度O(N)
std::pair<size_t, size_t> op3_1(const std::vector<float>& input) {
    assert(!input.empty());
    size_t left = 0, right = 0;
    auto maxx = input[0];
    // 计算前向累计和
    std::vector<float> prefix_sum(input.size() + 1, 0);
    for (size_t i = 1; i <= input.size(); ++i) prefix_sum[i] = prefix_sum[i - 1] + input[i - 1];
    size_t pre = 1;
    for (size_t j = pre; j < prefix_sum.size(); ++j) {
        if (prefix_sum[prefix_sum.size() - 1] - prefix_sum[j + 1] < 0) {
            for (size_t i = j; i >= pre; --i) {
                if (prefix_sum[j] - prefix_sum[i - 1] > maxx) {
                    maxx = prefix_sum[j] - prefix_sum[i - 1];
                    left = i - 1;
                    right = j - 1;  
                }
            }
            pre = j + 1;
        
        }
    }
    return {left, right};
}

// 优化op3_1，时间复杂度O(N)
std::pair<size_t, size_t> op3_2(const std::vector<float>& input) {
    assert(!input.empty());
    size_t left = 0, right = 0;
    auto maxx = input[0];
    auto sum = 0;
    size_t pre = 0;
    for (size_t j = 0; j < input.size(); ++j) {
        sum += input[j];
        if (sum > maxx) {
            maxx = sum;
            right = j;
            left = pre;
        }
        if (sum < 0) {
            sum = 0;
            pre = j + 1;
        }
    }
    return {left, right};
}

std::pair<size_t, size_t> _op4_1(const std::vector<float>& input, size_t left, size_t right) {
    assert(!input.empty());
    if (left == right) return {left, right};
    auto mid = (left + right) >> 1;
    auto left_pair = _op4_1(input, left, mid);
    auto right_pair = _op4_1(input, mid + 1, right);
    auto left_l = left_pair.first, left_r = left_pair.second;
    auto right_l = right_pair.first, right_r = right_pair.second;
    float left_sum = 0, right_sum = 0, cross_sum = 0;
    for (size_t i = left_l; i <= left_r; ++i) left_sum += input[i];
    for (size_t i = right_l; i <= right_r; ++i) right_sum += input[i];
    for (size_t i = left_l; i <= right_r; ++i) cross_sum += input[i];
    if (left_r == mid && right_l == mid + 1)
        if (left_sum > 0 && right_sum > 0) return {left_l, right_r};
        else if (left_sum > right_sum) return {left_l, left_r};
        else return {right_l, right_r};
    
    if (left_sum > right_sum && left_sum > cross_sum) return {left_l, left_r};
    else if (right_sum > left_sum && right_sum > cross_sum) return {right_l, right_r};
    else return {left_l, right_r};
}

// 分治法求解最大子段和问题，时间复杂度O(N log N)
std::pair<size_t, size_t> op4_1(const std::vector<float>& input) {
    assert(!input.empty());
    return _op4_1(input, 0, input.size() - 1);
}

std::pair<size_t, size_t> _op4_2(const std::vector<float>& input, const std::vector<float>& prefix_sum, size_t left, size_t right) {
    if (left == right) return {left, right};
    auto mid = (left + right) >> 1;
    auto left_pair = _op4_2(input, prefix_sum, left, mid);
    auto right_pair = _op4_2(input, prefix_sum, mid + 1, right);
    auto left_l = left_pair.first, left_r = left_pair.second;
    auto right_l = right_pair.first, right_r = right_pair.second;
    auto left_sum = prefix_sum[left_r + 1] - prefix_sum[left_l];
    auto right_sum = prefix_sum[right_r + 1] - prefix_sum[right_l];
    auto cross_sum = prefix_sum[right_r + 1] - prefix_sum[left_l];
    if (left_sum > right_sum && left_sum > cross_sum) return {left_l, left_r};
    else if (right_sum > left_sum && right_sum > cross_sum) return {right_l, right_r};
    else return {left_l, right_r};
}

// 分治法求解最大子段和问题，使用前缀和优化，时间复杂度O(N)
std::pair<size_t, size_t> op4_2(const std::vector<float>& input) {
    assert(!input.empty());
    // 计算前缀和
    std::vector<float> prefix_sum(input.size() + 1, 0);
    for (size_t i = 1; i <= input.size(); ++i) prefix_sum[i] = prefix_sum[i - 1] + input[i - 1];
    return _op4_2(input, prefix_sum, 0, input.size() - 1);
}
