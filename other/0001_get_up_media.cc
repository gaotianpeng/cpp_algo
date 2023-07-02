#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

namespace {

class Math {
public:
    static double random() {
        std::random_device r_d;
        std::default_random_engine engine(r_d());
        std::uniform_real_distribution<> distribution(0.0, 1.0);

        return distribution(engine);
    }
};

static int RandomVal(int min, int max) {
    return (int)(Math::random()*(max - min + 1)) + min;
}

static void RandomSortedArray(int len, int min, int max, vector<int>& out) {
    for (int i = 0; i < len; ++i) {
        out.emplace_back(RandomVal(min, max));
    }

    std::sort(out.begin(), out.end());
}

static void PrintArray(const vector<int>& arr) {
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }

    cout << endl;
}

} // namespace

/*
    给定两个等长有序列数组，返回两个数组的上中位数
    s1 = [1, 2, 3, 4]
    s2 = [1, 3, 5, 6]
    返回第4小的数 3
*/

static int GetUpMedian(const vector<int>& arr1, const vector<int>& arr2) {
    int len = arr1.size() + arr2.size();
    
    int start1 = 0;
    int end1 = arr1.size() - 1;
    int start2 = 0;
    int end2 = arr2.size() - 1;

    int mid1 = 0;
    int mid2 = 0;

    while (start1 < end1) {
        mid1 = (start1 + end1) / 2;
        mid2 = (start2 + end2) / 2;

        if (arr1[mid1] == arr2[mid2]) {
            return arr1[mid1];
        }

        if (((end1 - start1 + 1) & 1) == 1) { // 奇数长度
            if (arr1[mid1] > arr2[mid2]) {
                if (arr2[mid2] >= arr1[mid1-1]) {
                    return arr2[mid2];
                }
                
                end1 = mid1 - 1;
                start2 = mid2 + 1;
            } else {
                if (arr1[mid1] >= arr2[mid2 - 1]) {
                    return arr1[mid1];
                }
                start1 = mid1 + 1;
                end2 = mid2 - 1;
            }
            
        } else { // 偶数长度
            if (arr1[mid1] > arr2[mid2]) {
                end1 = mid1;
                start2 = mid2 + 1;
            } else {
                start1 = mid1 + 1;
                end2 = mid2;
            }
        }
    }

    
    return std::min(arr1[start1], arr2[start2]);
}

static int test(const vector<int>& arr1, const vector<int>& arr2) {
    vector<int> all;
    for (auto elem: arr1) {
        all.emplace_back(elem);
    }

    for (auto elem: arr2) {
        all.emplace_back(elem);
    }

    std::sort(all.begin(), all.end());
    int n = all.size();

    return all[(n-1)/2];
}

int main(int argc, char* argv[]) {
    cout << "test start ..." << endl;
    int test_times = 50000;
    int max_n = 30;
    int min = 0;
    int max = 100;
    for (int i = 0; i < test_times; ++i) {
        int len = RandomVal(0, max_n);
        vector<int> arr1;
        vector<int> arr2;
        RandomSortedArray(len, min, max, arr1);
        RandomSortedArray(len, min, max, arr2);
        if (arr1.size() + arr2.size() < 1) {
            continue;
        }
        if (GetUpMedian(arr1, arr2) != test(arr1, arr2)) {
            cout << "test failed" << endl;
            cout << GetUpMedian(arr1, arr2) << endl;
            cout << test(arr1, arr2) << endl;

            PrintArray(arr1);
            PrintArray(arr2);
            break;
        }
    }

    cout << "test end" << endl;
    return 0;
}