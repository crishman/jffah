# Add example executables
add_executable(tree_example tree_example.cpp)
add_executable(sort_example sort_example.cpp)

# Link examples with our library
target_link_libraries(tree_example PRIVATE jffah)
target_link_libraries(sort_example PRIVATE jffah)

# Set output directory for examples
set_target_properties(tree_example sort_example
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
) 