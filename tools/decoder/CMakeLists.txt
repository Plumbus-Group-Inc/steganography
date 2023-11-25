add_executable(decoder main.cpp)
target_link_libraries(decoder PRIVATE mmht-tool-settings steganography wav)
set_target_properties(decoder PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
