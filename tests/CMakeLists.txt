include(FetchContent)

# Fetch GoogleTest
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Enable testing for this directory
enable_testing()

# Add test executables
add_executable(test_trees test_trees.cpp)
add_executable(test_sorts test_sorts.cpp)

# Link test executables with GTest and our library
target_link_libraries(test_trees PRIVATE gtest_main jffah)
target_link_libraries(test_sorts PRIVATE gtest_main jffah)

# Register tests
add_test(NAME test_trees COMMAND test_trees)
add_test(NAME test_sorts COMMAND test_sorts) 