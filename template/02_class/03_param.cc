template <typename T>
struct X {};

template <template<typename T> typename C>
struct Test {
};

template <typename T>
struct my_array {
    T arr[10];
};

template <typename Ty, template<typename> typename C>
struct Array{
    C<Ty> array;
};


template <typename Ty, template<typename> typename C = my_array>
struct Array1{
    C<Ty> array;
};


template<typename T>
struct X{};

template<typename T>
struct X2 {};

template<template<typename T>typename...Ts>
struct Test1{};

template<typename... T>
struct my_array2{
    int arr[sizeof...(T)];  // 保有的数组大小根据模板类型形参的元素个数
};

template<typename Ty, template<typename... T> typename C = my_array2 >
struct Array2 {
    C<Ty> array;
};



int main() {
    Test<X> arr;

    Array<int, my_array> a;

    Test1<X, X2, X, X>t;     // 我们可以传递任意个数的模板实参

    Array2<int> arr;
    return 0;
}
