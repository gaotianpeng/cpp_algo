#include <iostream>
#include <algorithm>


template <std::size_t N>
void f() {
    std::cout << N << std::endl;
}

template <std::size_t... N> 
void f1() {
    std::size_t _[] { N... }; // 展开相当于 1UL, 2UL, 3UL, 4UL, 5UL
    std::for_each(std::begin(_), std::end(_), [](std::size_t n) {
        std::cout << n << ' ';
    });
}

int main() {
    f<100>();
    f1<1, 2, 3, 4, 5>();
    return 0;
}