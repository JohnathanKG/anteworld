cmake_minimum_required(VERSION 4.1)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD d0edc3af-4c50-42ea-a356-e2862fe7a444)
set(CMAKE_CXX_MODULE_STD ON)

project(anteworld)
set(CMAKE_PROJ ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_PROJ_INCLUDE ${CMAKE_CURRENT_LIST_DIR}/include)
set(CMAKE_PROJ_LIB ${CMAKE_CURRENT_LIST_DIR}/lib)

include_directories(
    ${CMAKE_PROJ_INCLUDE}
)

add_definitions(-DGLM_ENABLE_EXPERIMENTAL)


subdirs(include/ot include/comm include/comm/intergen)
macro(intergen_generate header_file)
    link_libraries(${CMAKE_PROJ_LIB}/c5e_lib.dll.lib)
    cmake_path(SET header_path ${CMAKE_CURRENT_LIST_DIR}/${header_file})
    cmake_path(GET header_path STEM filename)
    message(STATUS "Hello ${INTERGEN_EXECUTABLE_PATH} ${header_path} ${INTERGEN_TEMPLATES_PATH} ${CMAKE_CURRENT_BINARY_DIR}")
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${filename}.intergen.js.cpp ${CMAKE_CURRENT_BINARY_DIR}/${filename}.intergen.cpp
        COMMAND ${INTERGEN_EXECUTABLE_PATH} ${header_path} ${INTERGEN_TEMPLATES_PATH} ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}
    )
    set(${filename}_INTERGEN_FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${filename}.intergen.js.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/${filename}.intergen.cpp
    )
endmacro()

subdirs(example/vehicle_plugin example/igc_plugin)