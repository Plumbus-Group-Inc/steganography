add_library(mmht-tool-settings INTERFACE)
target_link_libraries(mmht-tool-settings INTERFACE mmht-settings CLI11::CLI11)

add_subdirectory(decoder)
add_subdirectory(encoder)
