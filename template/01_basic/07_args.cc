#include <iostream>

void f(const char *, int, double) {
    std::puts("值");
}

void f(const char**, int*, double*) {
    std::puts("&");
}

template<typename...Args>
void sum(Args...args){  // const char * args0, int args1, double args2
    f(args...);   // 相当于 f(args0, args1, args2)
    f(&args...);  // 相当于 f(&args0, &args1, &args2)
}


template<typename...Args>
void print(const Args&...args) {
    int _[] { (std::cout << args << " " , 0)... };
}

template<typename ...Args>
void print1(const Args &...args) {
   ((std::cout << args << " "), ...); // c++ 17
}


template <typename T, std::size_t N, typename... Args>
void f(const T(&array)[N], Args... index) {
    print(array[index]...);
}



int main() {
    sum("luse", 1, 1.2);
    // (std::cout << arg0 << ' ' ,0), (std::cout << arg1 << ' ' ,0),(std::cout << arg2 << ' ' ,0)
    print("luse", 1, 1.2);
    std::cout << std::endl;
    print1("luse", 1, 1.2);

    int array[10]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    f(array, 1, 3, 5);
    return 0;
}