# common 动态库配置
add_library(common SHARED
  logger.cc
  main.cc
)

# OpenCV 路径配置
set(OpenCV_INCLUDE_DIRS "D:/Projects/opencv/build_mingw64/install/include")
set(OpenCV_LIB_DIR "D:/Projects/opencv/build_mingw64/install/x64/mingw/lib")
set(OpenCV_BIN_DIR "D:/Projects/opencv/build_mingw64/install/x64/mingw/bin")

# 设置头文件目录
target_include_directories(common PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${OpenCV_INCLUDE_DIRS}
)

# 链接 OpenCV 库文件
target_link_directories(common PUBLIC ${OpenCV_LIB_DIR})
target_link_libraries(common PUBLIC opencv_world4130)

# 设置运行时库路径（用于找到 .dll 文件）
set_target_properties(common PROPERTIES
    INSTALL_RPATH "${OpenCV_BIN_DIR}"
    BUILD_WITH_INSTALL_RPATH TRUE
)

# 设置输出目录
set_target_properties(common PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/install
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/install
)

# 设置头文件目录（基础目录）
target_include_directories(common PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
)

