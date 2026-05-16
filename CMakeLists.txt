cmake_minimum_required(VERSION 3.16)

project(BilateralFilterLibrary
        VERSION 1.0.0
        DESCRIPTION "Custom C++17 bilateral filter library with OpenCV demo application"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

add_library(bilateral_filter
    src/bilateral_filter.cpp
)

target_include_directories(bilateral_filter
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(bilateral_filter
    PUBLIC
        ${OpenCV_LIBS}
)

add_executable(bilateral_filter_app
    apps/bilateral_filter_cli.cpp
)

target_link_libraries(bilateral_filter_app
    PRIVATE
        bilateral_filter
)

install(TARGETS bilateral_filter bilateral_filter_app
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(DIRECTORY include/
        DESTINATION include)
