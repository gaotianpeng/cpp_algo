cmake_minimum_required(VERSION 3.15)
project(CppAlgo)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加调试符号和优化选项
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
    message(STATUS "Build type: Debug (with debug symbols)")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
    message(STATUS "Build type: Release")
endif()

# 添加 include 目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# 自动查找 src 目录下所有 .cpp, .cc, .c 文件
file(GLOB_RECURSE CPP_FILES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

# 为每个源文件创建一个独立的可执行文件
foreach(source_file ${CPP_FILES})
    # 获取相对于 src 目录的路径
    file(RELATIVE_PATH rel_path "${CMAKE_CURRENT_SOURCE_DIR}/src" ${source_file})
    
    # 获取文件名（不含扩展名）
    get_filename_component(file_name ${source_file} NAME_WE)
    
    # 获取目录名
    get_filename_component(dir_name ${rel_path} DIRECTORY)
    
    # 构建可执行文件名
    if(dir_name)
        # 将 / 替换为 _
        string(REPLACE "/" "_" dir_prefix ${dir_name})
        set(exe_name "${dir_prefix}_${file_name}")
    else()
        set(exe_name "${file_name}")
    endif()
    
    # 避免与 CMake 保留名称冲突（添加 app_ 前缀）
    if(exe_name STREQUAL "clean" OR exe_name STREQUAL "test" OR exe_name STREQUAL "install")
        set(exe_name "app_${exe_name}")
    endif()
    
    # 创建可执行文件
    add_executable(${exe_name} ${source_file})
    
    # 自动链接 pthread 库（如果需要）
    target_link_libraries(${exe_name} PRIVATE pthread)
endforeach()
