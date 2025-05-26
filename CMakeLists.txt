cmake_minimum_required(VERSION 3.15)
project(jffah VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable testing
enable_testing()

# Add compiler warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add library target
add_library(jffah INTERFACE)
target_include_directories(jffah INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Add subdirectories
add_subdirectory(tests)
add_subdirectory(examples)

# Installation rules
install(TARGETS jffah
    EXPORT jffahTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY include/jffah
    DESTINATION include
    FILES_MATCHING PATTERN "*.hpp"
)

# Export targets
install(EXPORT jffahTargets
    FILE jffahTargets.cmake
    NAMESPACE jffah::
    DESTINATION lib/cmake/jffah
) 