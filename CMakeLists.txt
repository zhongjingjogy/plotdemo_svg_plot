cmake_minimum_required(VERSION 3.0)
project(plotsvg VERSION 2.0.0 LANGUAGES CXX)

find_package(Boost REQUIRED COMPONENTS filesystem system serialization date_time)

add_library(quan INTERFACE)

target_include_directories(quan INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/quan/include/"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/quan/include/boost/"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/quan/include/boost/quan"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/quan/include/boost/quan/impl"
)

target_link_libraries(quan 
    INTERFACE
        Boost::boost
        Boost::filesystem Boost::system Boost::serialization Boost::date_time 
)

add_library(svgplot INTERFACE)

target_include_directories(svgplot INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/svg_plot/include/"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/svg_plot/include/boost/"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/svg_plot/include/boost/svg_plot"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/svg_plot/include/boost/svg_plot/detail"
)

target_link_libraries(svgplot 
    INTERFACE
        quan
)

add_executable(plotprofile demo/profile/test.cpp)

target_link_libraries(plotprofile
    PRIVATE
        utils
        quan
        svgplot
)

add_executable(plotinterd demo/interd/test.cpp)

target_link_libraries(plotinterd
    PRIVATE
        utils
        quan
        svgplot
)

add_subdirectory(./utils)