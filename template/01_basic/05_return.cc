#include <iostream>
using namespace std::string_literals;

template <typename T = int>
void f() {
}


template <typename T1, typename T2, typename RT = decltype(true ? T1{} : T2{})>
RT max(const T1& a, const T2& b) {
    return a > b ? a : b;
}


template <typename T1, typename T2>
auto max1(const T1& a, const T2& b) -> decltype(true ? a : b) {
    return a > b ? a : b;
}

int main() {
    f();
    f<double>();

    auto ret = ::max("1", "2"s); // std::string max<char [2], std::string, std::string>(const char (&a)[2], const std::string &b)
    std::cout << ret << std::endl;

    auto ret1 = ::max1("1", "2"s);
    std::cout << ret1 << std::endl;

    return 0;
}