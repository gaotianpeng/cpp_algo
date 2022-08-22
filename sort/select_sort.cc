#include <iostream>
#include <vector>
#include "gtest/gtest.h"

using namespace std;
/*
    arr[0～N-1]范围上，找到最小值所在的位置，然后把最小值交换到0位置。
    arr[1～N-1]范围上，找到最小值所在的位置，然后把最小值交换到1位置。
    arr[2～N-1]范围上，找到最小值所在的位置，然后把最小值交换到2位置。
    …
    arr[N-1～N-1]范围上，找到最小值位置，然后把最小值交换到N-1位置。
*/

void swap(int& a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void SelectSort(int arr[], int n) {
    if (arr == nullptr || n <= 1) {
        return;
    }

    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[i]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swap(arr[i], arr[min_index]);
        }
    }
}


TEST(SortTest, SelectSort) {
    cout << "Select Sort start ----------\n";

    int arr[] = {4, 3, 8 , 9};
    for (int i = 0; i < 4; i++) {
        cout << arr[i] << " ";
    }   
    cout << endl;
    SelectSort(arr, 4);
    for (int i = 0; i < 4; i++) {
        cout << arr[i] << " ";
    }   
    cout << endl;
    cout << "Select Sort end-------------\n";
}