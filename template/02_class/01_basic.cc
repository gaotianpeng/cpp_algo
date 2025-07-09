template <typename T>
struct Test{
};


template<typename T>
struct Test1{
    Test1(T v) :t{ v } {}
private:
    T t;
};



int main() {
    Test<int> t;
    Test<void> t2;
    return 0;
}