#include <cstddef>

template <typename T>
struct A {
    A(T, T){}
};

template <typename T>
struct B {
    B(const T&, const T&) {}
};

template <typename T>
struct Test{
    Test(T v): t{v} {
    }

private:
    T t;
};

Test(int) -> Test<std::size_t>;

template <typename T>
Test(T*) -> Test<T[]>;

template <typename Ty, std::size_t size>
struct array {
    Ty arr[size];
};


template <typename T, typename ...Args>
array(T t, Args...) -> array<T, sizeof...(Args) + 1>;

int main() {
    auto x = new A(1, 2); // 这里的 x 会被推导为 A<int>
    auto y = new B(1, 2); // 这里的 y 会被推导为 B<int>

    Test t(1); // 这里的 t 会被推导为 Test<std::size_t>

    char* p = nullptr;
    Test t2(p); // 这里的 t2 会被推导为 Test<char[]>


    // ::array arr{1, 2, 3, 4, 5}; // Error
    ::array arr{1, 2, 3, 4, 5}; // 这里的 arr 会被推导为 array<int, 5>

    return 0;
}