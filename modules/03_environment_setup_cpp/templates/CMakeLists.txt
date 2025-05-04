# modules/03_environment_setup_cpp/templates/CMakeLists.txt

# 把当前目录下的 template.cpp 编译成可执行文件 template_cpp
add_executable(template_cpp template.cpp)

# （可选）如果你的代码里要包含项目根目录的头文件
#target_include_directories(template_cpp PRIVATE ${CMAKE_SOURCE_DIR})
