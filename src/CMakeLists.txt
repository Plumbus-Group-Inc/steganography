add_library(steganography echo.cpp lsb.cpp phase.cpp)
target_include_directories(steganography PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(wav wav.cpp)
target_include_directories(wav PUBLIC ${CMAKE_SOURCE_DIR}/include)
