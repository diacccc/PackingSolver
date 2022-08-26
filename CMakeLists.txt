# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

project ("PackingSolver")

# aux_source_directory(. DIR_SRCS)
# 包含子项目。

include_directories("${PROJECT_SOURCE_DIR}/PackingSolver")

aux_source_directory (PackingSolver SRC_LIST)

add_executable(PackingSolver main.cpp ${SRC_LIST})
# add_subdirectory ("PackingSolver")

# add_executable(PackingSolver "main.cpp")

# target_link_libraries(PackingSolver Instance)

set_property(TARGET PackingSolver PROPERTY CXX_STANDARD 20)