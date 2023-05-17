#include <iostream>
#include <typeinfo>
#include <string>

using namespace std;

template<typename T, typename U, typename Ret, T ptr>
struct Tunnel {
    friend Ret & sneak(U& u) {
        cout << typeid(ptr).name() << endl;
        return u.*ptr;
    }
};

#define DEFINE_TUNNEL(CLASS_NAME, MEMBER_NAME, RET_TYPE) \
template struct Tunnel<decltype(&CLASS_NAME::MEMBER_NAME), \
CLASS_NAME, RET_TYPE, &CLASS_NAME::MEMBER_NAME>;

class ClassA {
private:
    int i = 0;
};
class ClassB {
private:
    int j = 1;
};

DEFINE_TUNNEL(ClassA, i, int)
DEFINE_TUNNEL(ClassB, j, int)

int& sneak(ClassA& u);
int& sneak(ClassB& u);
    
int main(int arg, char* argv[]) {
    {
        ClassA a;

        cout << sneak(a) << endl;
    }
    {
        ClassB b;

        cout << sneak(b) << endl;
    }

    return 0;
}