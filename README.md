# 下载源码
``` bash
# 构建步骤
git clone --recurse-submodules git@github.com:gaotianpeng/cpp_algo.git

cd cpp_algo
mkdir build && cd build
cmake ..

./cpp_algo

# 检查内存泄漏(Linux)
valgrind --tool=memcheck --leak-check=full  ./cpp_algo
```