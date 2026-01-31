#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

namespace test_utils {

// 随机数生成器
class Random {
public:
    // 生成 [0.0, 1.0) 范围的随机浮点数
    static double nextDouble() {
        thread_local std::mt19937_64 engine = createEngine();
        thread_local std::uniform_real_distribution<double> distribution(0.0, 1.0);
        return distribution(engine);
    }

    // 生成 [min, max] 范围的随机整数
    static int nextInt(int min, int max) {
        thread_local std::mt19937_64 engine = createEngine();
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(engine);
    }

private:
    static std::mt19937_64 createEngine() {
        std::random_device rd;
        std::seed_seq seed{rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
        return std::mt19937_64(seed);
    }
};

// 数组工具类
class ArrayUtils {
public:
    // 生成随机整数数组
    static void randomArray(std::vector<int>& out, int max_n, int min_val, int max_val) {
        int len = static_cast<int>(Random::nextDouble() * max_n);
        out.clear();
        out.reserve(len);
        for (int i = 0; i < len; i++) {
            int val = Random::nextInt(min_val, max_val);
            out.emplace_back(val);
        }
    }

    // 生成指定长度的随机整数数组
    static std::vector<int> randomArray(int len, int min_val, int max_val) {
        std::vector<int> result;
        result.reserve(len);
        for (int i = 0; i < len; i++) {
            result.emplace_back(Random::nextInt(min_val, max_val));
        }
        return result;
    }

    // 复制数组
    static void copyArray(const std::vector<int>& src, std::vector<int>& dst) {
        dst = src;
    }

    // 打印数组
    static void printArray(const std::vector<int>& arr) {
        for (const auto& elem : arr) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    // 比较两个数组是否相等
    static bool isEqual(const std::vector<int>& arr1, const std::vector<int>& arr2) {
        return arr1 == arr2;
    }

    // 交换数组中两个元素
    static void swap(std::vector<int>& arr, int i, int j) {
        std::swap(arr[i], arr[j]);
    }
};

} // namespace test_utils

#endif // TEST_UTILS_H
