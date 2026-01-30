# VSCode C++ 开发环境配置说明

本项目已配置完整的 VSCode C++ 开发环境，支持单文件编译、运行和调试。

## 功能特性

✅ 支持任意子目录结构  
✅ 自动为每个 `.cpp`、`.cc`、`.c` 文件生成独立可执行文件  
✅ 支持 C++17 标准  
✅ 自动链接 pthread 库  
✅ 完整的调试支持（lldb）  
✅ 标准库源码语法高亮  

## 使用方法

### 1. 编译当前文件
- 快捷键：`Ctrl + Shift + B`
- 或：打开命令面板 → "Tasks: Run Build Task"

### 2. 运行当前文件
- 打开命令面板 → "Tasks: Run Task" → "Run Current File (Debug)"

### 3. 调试当前文件
- 快捷键：`F5`
- 或：点击调试面板的运行按钮

## 目录结构

```
cpp_algo/
├── .vscode/
│   ├── settings.json          # 编辑器设置
│   ├── tasks.json             # 编译任务
│   ├── launch.json            # 调试配置
│   └── get_target_name.sh     # 辅助脚本
├── CMakeLists.txt             # CMake 配置
└── src/                       # 源代码目录
    ├── concurrency/           # 并发相关代码
    ├── leetcode/              # LeetCode 题目
    ├── template/              # 模板相关
    ├── tixi/                  # 体系课代码
    ├── other/                 # 其他代码
    ├── clean.cc               # 清理工具
    └── test.c                 # 测试文件
```

## 可执行文件命名规则

- 根目录文件：`文件名`
  - 例如：`src/clean.cc` → `app_clean`（避免与 CMake 保留名冲突）
  - 例如：`src/test.c` → `app_test`（避免与 CMake 保留名冲突）
  
- 子目录文件：`目录_文件名`
  - 例如：`src/concurrency/lock.c` → `concurrency_lock`
  - 例如：`src/leetcode/array/0001_two_sum.cc` → `leetcode_array_0001_two_sum`

## 配置文件说明

### settings.json
- C++ 标准：C++17
- 编译器路径：`/usr/bin/g++`
- 标准库文件关联（支持查看源码）

### tasks.json
- Build Current File (Debug)：编译当前文件（Debug 模式）
- Run Current File (Debug)：编译并运行（Debug 模式）
- Run Current File (Release)：编译并运行（Release 模式）

### launch.json
- Debug Current File：调试当前文件（使用 lldb）

## 注意事项

1. 文件扩展名支持：`.cpp`、`.cc`、`.c`
2. 避免使用保留名称：`clean`、`test`、`install`（会自动添加 `app_` 前缀）
3. 编译输出在 `build/` 目录
4. 调试前会自动编译

## 手动编译示例

```bash
# 配置 CMake
cmake -B build -DCMAKE_BUILD_TYPE=Debug

# 编译特定文件
cmake --build build --target leetcode_array_0001_two_sum

# 运行
./build/leetcode_array_0001_two_sum
```

## 清理构建

```bash
rm -rf build
```
