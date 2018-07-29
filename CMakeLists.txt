cmake_minimum_required(VERSION 3.0)
project(plotsvg VERSION 2.0.0 LANGUAGES CXX)

add_executable(demo demo/test.cpp)

target_link_libraries(demo
    PRIVATE
        quan
        svgplot
)

add_subdirectory(./quan)
add_subdirectory(./svg_plot)