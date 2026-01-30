#include <iostream>
#include <tuple>

template <typename... Args>
struct X{
    X(Args... args): value(args...) {
    }

    std::tuple<Args...> value;
};


int main() {
    X x{1, "2", '3', 4.}; 
    std::cout << std::get<1>(x.value) << std::endl; // 输出 "2"
    return 0;
}