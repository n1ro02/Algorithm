cmake_minimum_required(VERSION 3.15)
project(Algorithm)

# 全局设置 C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 把 src 和 test 子目录都加进来
add_subdirectory(src)
enable_testing()       # 打开 CTest 支持
add_subdirectory(test)
