cmake_minimum_required(VERSION 3.0)
project(plotsvg VERSION 2.0.0 LANGUAGES CXX)

add_executable(plotprofile demo/profile/test.cpp)

target_link_libraries(plotprofile
    PRIVATE
        quan
        svgplot
)

add_executable(plotinterd demo/interd/test.cpp)

target_link_libraries(plotinterd
    PRIVATE
        quan
        svgplot
)

add_subdirectory(./quan)
add_subdirectory(./svg_plot)