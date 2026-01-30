#include <iostream>
using namespace std;

template <typename T>
T max(T a, T b) {
	return a > b ? a : b;
}

struct Test {
	int v_{};

	Test() = default;
	Test(int v): v_(v) {}

	bool operator>(const Test& t) const {
		return this->v_ > t.v_;
	}
};

int main() {
	int a{1};
	int b{2};
	std::cout << "max(a, b) = " << ::max(a, b) << std::endl; 
	::max(a, b); // 模板推导为 max<int>
	::max<double>(a, b); // 显式指定模板参数为 max<double>

	Test t1{10};
	Test t2{2};
	std::cout << "max(t1, t2) = " << ::max(t1, t2).v_ << std::endl;

	return 0;
}