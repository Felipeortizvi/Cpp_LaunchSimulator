cmake_minimum_required(VERSION 3.10)  # or higher
project(RocketSimulation)

# Use C++17 (or whichever version you prefer)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SOURCES
    "src/*.cpp"
    "main.cpp"
)

add_executable(rocketSim ${SOURCES})
