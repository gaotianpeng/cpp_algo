template <class Ty>
constexpr Ty&& forward(Ty& arg) {
  return static_cast<Ty&&>(arg);
}

int main() {
    int a = 10;
    int a = 10;            // 不重要
    ::forward<int>(a);     // 返回 int&& 因为 Ty 是 int，Ty&& 就是 int&&
    ::forward<int&>(a);    // 返回 int& 因为 Ty 是 int&，Ty&& 就是 int&
    ::forward<int&&>(a);   // 返回 int&& 因为 Ty 是 int&&，Ty&& 就是 int&&
    return 0;
}