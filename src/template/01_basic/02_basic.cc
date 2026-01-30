#include <iostream>

using namespace std::string_literals;

template <typename T>
T max(const T& a, const T& b) {
    return a > b ? a : b;
}

int main() {
    ::max(1, 2); // 模板推导为 max<int>
    ::max(1, 1.2);
    ::max("luse"s, "乐");

    ::max<double>(1, 1.2);
    ::max<std::string>("luse"s, "乐");
    

    return 0;
}