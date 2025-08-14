cmake_minimum_required(VERSION 4.1)
project(vehicle_plugin)

include_directories(
    ${CMAKE_PROJ_INCLUDE}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

intergen_generate(${CMAKE_CURRENT_SOURCE_DIR}/simplugin.hpp)

add_library(vehicle_plugin SHARED
    simplugin.cpp
    vehicle_plugin.cpp
)

target_link_libraries(vehicle_plugin comm ot)