add_executable(encoder main.cpp)
target_link_libraries(encoder PRIVATE mmht-tool-settings steganography wav)
set_target_properties(encoder PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
