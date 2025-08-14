cmake_minimum_required(VERSION 4.1)
project(igc_plugin)

include_directories(
    ${CMAKE_PROJ_INCLUDE}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

intergen_generate(plugin.hpp)

message(STATUS "IGC_PLUGIN_INTERGEN_FILES: ${plugin_INTERGEN_FILES}")
add_library(igc_plugin SHARED
    plugin.cpp
    ${plugin_INTERGEN_FILES}
)

target_link_libraries(igc_plugin comm ot)