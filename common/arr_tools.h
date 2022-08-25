//
// Created by Gao Tianpeng on 2022/8/23.
//

#ifndef CPP_ALGO_COMMON_ARR_TOOLS_H_
#define CPP_ALGO_COMMON_ARR_TOOLS_H_

#include <vector>

namespace tools {

void swap(int& a, int &b);

void RandomArr(std::vector<int>& out, int max_n, int min_val, int max_val);

void RandomSortedArr(std::vector<int>& out, int max_n, int min_val, int max_val);


void CopyArr(const std::vector<int>& src, std::vector<int>& dst);

void Print(const std::vector<int>& arr);

bool IsEqual(const std::vector<int>& arr_a, const std::vector<int>& arr_b);

bool IsReverse(const std::vector<int>& arr_a, const std::vector<int>& arr_b);

} // namespace tools
#endif //CPP_ALGO_COMMON_ARR_TOOLS_H_
