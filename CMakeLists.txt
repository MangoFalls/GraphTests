cmake_minimum_required(VERSION 3.20)
project(GraphTests)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(/W4 /WX)

# Add the executable target for your project
add_executable(GraphTests
    DirectedGraph.c++
    main.c++
)

# Include the header directory
target_include_directories(GraphTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
