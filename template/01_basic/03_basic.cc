#include <iostream>

template <typename T>
void f(T&& t) {
}

int main() {
    int a = 10;
    f(a); // f<int&>(int& t)
    f(10); // f<int>(int&& tt)
    return 0;
}