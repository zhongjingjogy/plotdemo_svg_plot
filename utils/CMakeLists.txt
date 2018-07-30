cmake_minimum_required(VERSION 3.5)
project(utils VERSION 1.0.0 LANGUAGES CXX)

add_library(utils INTERFACE)

target_include_directories(utils INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
)

target_link_libraries(utils
    INTERFACE
        quan
        svgplot
)