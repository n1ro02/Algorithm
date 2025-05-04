cmake_minimum_required(VERSION 3.10)
project(ICPC_Learning LANGUAGES CXX)

# ------------------ 编译选项 ------------------
# 默认采用 Release 模式
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ------------------ 源文件收集 ------------------
# 自动查找 modules 目录下所有 .cpp 文件
file(GLOB_RECURSE CPP_SOURCES
        CONFIGURE_DEPENDS
        "${CMAKE_SOURCE_DIR}/modules/*/examples/*.cpp"
        "${CMAKE_SOURCE_DIR}/modules/*/*/*.cpp"
        "${CMAKE_SOURCE_DIR}/modules/*/templates/*.cpp"
)

# ------------------ 添加可执行目标 ------------------
foreach(src IN LISTS CPP_SOURCES)
    # 提取文件名（无扩展名）作为 target 名称
    get_filename_component(target ${src} NAME_WE)
    add_executable(${target} ${src})
    # 包含项目根目录，可包含 headers
    target_include_directories(${target}
            PRIVATE ${CMAKE_SOURCE_DIR}
    )
endforeach()

# ------------------ 可选：打印收集信息 ------------------
message(STATUS "Found ${CPP_SOURCES_COUNT} C++ source files.")
message(STATUS "Available targets:")
foreach(src IN LISTS CPP_SOURCES)
    get_filename_component(name ${src} NAME_WE)
    message(STATUS "  - ${name}")
endforeach()
