# common 动态库配置
add_library(common SHARED
    common.cc
    common.h
)

# 设置输出目录
set_target_properties(common PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/install
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/install
)

# 设置头文件目录
target_include_directories(common PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

