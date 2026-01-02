# windows 动态库配置
add_library(windows_lib SHARED
    main_window.cc
    page1/page.cc
    page1/btn_open_gray_file.cc
    page1/btn_open_color_file.cc
    page2/page.cc
    page3/page.cc
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

# 设置输出目录
set_target_properties(windows_lib PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/install
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/install
)

# 设置头文件目录
target_include_directories(windows_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GTK4_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}
)

# 链接common动态库
target_link_libraries(windows_lib
    common
    ${GTK4_LIBRARIES}
)

