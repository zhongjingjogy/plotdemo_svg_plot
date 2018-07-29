cmake_minimum_required(VERSION 3.5)
project(svgplot VERSION 1.0.0 LANGUAGES CXX)

add_library(svgplot INTERFACE)

target_include_directories(svgplot INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/boost/"
    "${CMAKE_CURRENT_SOURCE_DIR}/boost/svg_plot"
    "${CMAKE_CURRENT_SOURCE_DIR}/boost/svg_plot/detail"
)

target_link_libraries(svgplot 
    INTERFACE
        quan
)