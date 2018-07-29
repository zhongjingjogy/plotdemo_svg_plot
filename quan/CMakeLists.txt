cmake_minimum_required(VERSION 3.5)
project(svgplot VERSION 1.0.0 LANGUAGES CXX)

find_package(Boost REQUIRED COMPONENTS filesystem system serialization date_time)

add_library(quan INTERFACE)

target_include_directories(quan INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/boost/"
    "${CMAKE_CURRENT_SOURCE_DIR}/boost/quan"
    "${CMAKE_CURRENT_SOURCE_DIR}/boost/quan/impl"
)

target_link_libraries(quan 
    INTERFACE
        Boost::boost
        Boost::filesystem Boost::system Boost::serialization Boost::date_time 
)