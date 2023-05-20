
#include <iostream>
#include <random>
#include <vector>
#include <set>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Math {
public:
    static double random() {
        static std::random_device rd;
        static std::default_random_engine engine(rd());
        static std::uniform_real_distribution<> distribution(0.0, 1.0);
        return distribution(engine);
    }
};

int RandomVal(int min, int max) {
    return min + (int)(Math::random() * (max - min + 1));
}


int main(int argc, char* argv[]) {
    int max = 5;
    int min = 1;
    for (int i = 0; i < 10000000; i++) {
        if (RandomVal(0, 5) == 0) {
            cout << "test success" << endl;
        }
    }
    return 0;
}