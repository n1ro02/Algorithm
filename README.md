下面是一份从零开始、在 CLion 中构造并管理你自己的算法学习 GitHub 仓库的详细指南。全程分为 八 个步骤：
--- ---
# 1. 在 GitHub 上创建空仓库
登录 github.com，点击右上角的 “+” → New repository。

填写：

Repository name: algorithm-learning-repo（或你喜欢的名字）

Description: “My personal algorithm practice repo in C++”

勾选 Add a README file（也可以不勾，后面本地添加）

可选：选择 MIT/Apache2/… 许可协议

点击 Create repository，得到一个空仓库 URL，比如：

`https://github.com/your-username/algorithm-learning-repo.git`

# 2. 本地克隆并在 CLion 打开

```bash
# 你可以在命令行中：
git clone https://github.com/your-username/algorithm-learning-repo.git
cd algorithm-learning-repo
```

也可以直接在 CLion 中：

File → Get from Version Control…

填入上面仓库 URL，选择本地路径

点击 Clone → CLion 会自动打开该项目

# 3. 搭建基础目录结构
   在仓库根目录下创建以下目录／文件（CLion 右键 New → Directory / File）：

```objectivec
algorithm-learning-repo/
├── .gitignore
├── README.md
├── CMakeLists.txt
├── src/
│   ├── 01_sorting/
│   │   ├── CMakeLists.txt
│   │   ├── bubble_sort.cpp
│   │   └── merge_sort.cpp
│   └── 02_searching/
│       ├── CMakeLists.txt
│       └── binary_search.cpp
├── test/
│   ├── CMakeLists.txt
│   └── sorting_tests.cpp
└── .github/
└── workflows/
└── ci.yml
```

`.gitignore` 示例
```gitignore
# CMake
CMakeFiles/
CMakeCache.txt
cmake_install.cmake
Makefile

# CLion
.idea/
*.iml

# 编译输出
build/
*.o
*.exe
```
# 4. 编写顶层 CMakeLists.txt
   在 `algorithm-learning-repo/CMakeLists.txt` 中写入：

```cmake
cmake_minimum_required(VERSION 3.15)
project(algorithm_learning LANGUAGES CXX)

# 全局设置
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 子目录
add_subdirectory(src)
enable_testing()
add_subdirectory(test)
enable_testing() #开启 CTest，以后可在 CLion “Run” 下看到 Tests。
```

# 5. 按模块拆分:src 子目录
src/CMakeLists.txt
```cmake
# 遍历所有模块
add_subdirectory(01_sorting)
add_subdirectory(02_searching)
# … 如有更多模块，继续添加
```

`src/01_sorting/CMakeLists.txt`
```cmake
# 自动收集本目录下的 .cpp
file(GLOB SORT_SOURCES "*.cpp")

# 为每个源文件生成一个可执行 target
foreach(src ${SORT_SOURCES})
    get_filename_component(name ${src} NAME_WE)
    add_executable(${name} ${src})
endforeach()
```
* 这样 CLion 会自动生成 Run Configurations：bubble_sort、merge_sort…

其余模块（如 02_searching) 只需同理复制此 CMakeLists。

# 6. 配置测试：test 子目录

`test/CMakeLists.txt`
```cmake
# 假设你要把 sorting 算法做成 library，也可以直接编译 .cpp
add_executable(sorting_tests sorting_tests.cpp)

# 如果 sorting 算法编译为库，链接它：
# target_link_libraries(sorting_tests PRIVATE bubble_sort merge_sort)

add_test(NAME SortingTest COMMAND sorting_tests)
```

* 在 `sorting_tests.cpp` 中，用 assert 或者简单输出验证算法正确性。

* CLion “Run Configurations” 的 “All Tests” 就能跑起 ctest。

# 7. 配合 Git / GitHub

1. 首次提交
```bash
git add .
git commit -m "初始化算法学习仓库结构和 CMake 配置"
git push -u origin main
```
2. 后续开发流程

* 每新增一个算法模块或题目，都在对应目录里 git add → commit → push。
* 建议用分支：

```bash
git checkout -b feature/dp-knapsack
# 开发完
git commit -am "feat: add knapsack DP example"
git push --set-upstream origin feature/dp-knapsack
# 在 GitHub 发起 PR → 合并到 main
```
3. README.md

在根目录 `README.md` 补充：
*项目简介
*如何编译：
```bash
mkdir build && cd build
cmake ..
cmake --build .
```
* 如何运行某个算法：

```bash
./bubble_sort
```
* 进度徽章（badge）、模块列表、联系邮箱等。

# 8. 持续集成（GitHub Actions）
在 `·github/workflows/ci.yml` 写入一个简单 CI，自动编译并执行测试：

```yaml

name: CI

on:
push:
branches: [ main ]
pull_request:

jobs:
build-and-test:
runs-on: ubuntu-latest
steps:
- uses: actions/checkout@v3

      - name: Install dependencies
        run: sudo apt-get update && sudo apt-get install -y cmake g++

      - name: Configure
        run: |
          mkdir build
          cd build
          cmake ..

      - name: Build
        run: |
          cd build
          cmake --build .

      - name: Run tests
        run: |
          cd build
          ctest --output-on-failure
```
* 效果：每次 push/PR 自动触发，保证你的算法示例始终能编译并通过测试。

# 小结
1. 仓库初始化：GitHub 上建空库 → 本地克隆 → CLion 打开。

2. 目录与 CMake：顶层 CMakeLists → src、test 子 CMakeLists → 代码模块化。

3. 版本控制：规范分支、PR 流程、完善 README/.gitignore。

4. CI 保驾护航：GitHub Actions 自动编译+测试。

按此流程，你的算法学习仓库将具备：

* 模块清晰（按专题组织代码）

* 易于调试（CLion Run Configs、Debug）

*高效管理（Git + 分支 + CI）

祝你在 CLion 中算法之路越走越远！