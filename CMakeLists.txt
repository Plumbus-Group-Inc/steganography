cmake_minimum_required(VERSION 3.16.3)
project(MMHT)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(mmht-settings INTERFACE)
target_include_directories(mmht-settings INTERFACE ${CMAKE_SOURCE_DIR}/include)
target_compile_features(mmht-settings INTERFACE cxx_std_20)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(tools)
add_subdirectory(thirdparty)
