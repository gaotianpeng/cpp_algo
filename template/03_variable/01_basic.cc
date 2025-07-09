#include <iostream>

template <typename T>
T v;

template <typename T>
constexpr T v1{};


int main() {
    v<int> = 10;
    std::cout << v<int> << std::endl;

    std::cout << std::boolalpha << std::is_same_v<decltype(v1<int>), const int> << std::endl;
    return 0;
}