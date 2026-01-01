cmake_minimum_required(VERSION 3.20)
project(image-analysis)

set(CMAKE_C_STANDARD 11)

# 设置可执行文件和库文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/install)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/install)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

# 添加common动态库子目录
add_subdirectory(common)

# 添加windows动态库子目录
add_subdirectory(windows)

# 添加可执行文件（WIN32选项隐藏控制台窗口）
add_executable(${PROJECT_NAME} WIN32 main.cc)

# 链接动态库
target_link_libraries(${PROJECT_NAME}
    common
    windows_lib
    ${GTK4_LIBRARIES}
)

# 设置头文件目录
target_include_directories(${PROJECT_NAME} PRIVATE
    ${GTK4_INCLUDE_DIRS}
)
