#include <iostream>
#include <random>
#include <vector>
using namespace std;

/*
    for test
*/
namespace {

class Math {
public:
    static double random() {
        static std::random_device rd;
        static std::default_random_engine engine(rd());
        static std::uniform_real_distribution<> distribution(0.0, 1.0);
        return distribution(engine);
    }
};

static void RandomArr(vector<int>& out, int max_n, int min_val, int max_val) {
	int len = (int)(Math::random() * max_n);
	for (int i = 0; i < len; i++) {
		int val = (int)(Math::random() * (max_val - min_val)) + min_val;
		out.emplace_back(val);
	}
}

static void PrintArr(const vector<int>& arr) {
    for (auto& elem: arr) {
        cout << elem << " ";
    }
    cout << endl;
}

} // namespace


int main(int argc, char* argv[]) {
    int max = 100;
    int min = -100;
    int n = 100;
    vector<int> arr;
    for (int i = 0; i < 100; ++i) {
        RandomArr(arr, n, min, max);
        PrintArr(arr);
    }

    return 0;
}