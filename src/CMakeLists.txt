add_library(steganography echo.cpp lsb.cpp phase.cpp)
target_link_libraries(steganography PRIVATE mmht-settings)

add_library(wav wav.cpp)
target_link_libraries(wav PRIVATE mmht-settings AudioFile)
