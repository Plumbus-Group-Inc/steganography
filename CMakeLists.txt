cmake_minimum_required(VERSION 3.16.3)
project(SGG)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(sgg-settings INTERFACE)
target_include_directories(sgg-settings INTERFACE ${CMAKE_SOURCE_DIR}/include)
target_compile_features(sgg-settings INTERFACE cxx_std_20)

add_subdirectory(src)
add_subdirectory(tools)
add_subdirectory(test)
