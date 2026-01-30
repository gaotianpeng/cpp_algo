#include <iostream>
#include <type_traits>
#include <numeric>

template <typename... Args, typename RT = std::common_type_t<Args...>>
RT sum(Args... args) {
    RT _[] {static_cast<RT>(args)...};
    RT n{};
    for (int i = 0; i < sizeof...(args); ++i) {
        n += _[i];
    }

    return n;
} 


template <typename... Args, typename RT = std::common_type_t<Args...>>
RT sum1(Args... args) {
    RT _[] {static_cast<RT>(args)...};

    return std::accumulate(std::begin(_), std::end(_), RT{});
} 


int main() {
    double ret = sum(1, 2, 3, 4, 5, 6.7);
    std::cout << "Sum: " << ret << std::endl;
    double ret1 = sum1(1, 2, 3, 4, 5, 6.7);
    std::cout << "Sum1: " << ret1 << std::endl;
    return 0;
}