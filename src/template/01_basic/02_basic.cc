#include <iostream>

using namespace std::string_literals;

template <typename T>
T max(const T& a, const T& b) {
    return a > b ? a : b;
}

int main() {
    ::max(1, 2); // 模板推导为 max<int>
    // ::max(1, 1.2);  // 错误：类型冲突，注释掉
    // ::max("luse"s, "乐");  // 错误：类型冲突，注释掉

    ::max<double>(1, 1.2);  // 显式指定类型，正确
    ::max<std::string>("luse"s, "乐");  // 显式指定类型，正确
    

    return 0;
}