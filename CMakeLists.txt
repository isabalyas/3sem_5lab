cmake_minimum_required(VERSION 3.10)
project(PredatorPreySimulation)

set(CMAKE_CXX_STANDARD 17)

add_executable(predator_prey
    main.cpp
    Animal.cpp
    Rabbit.cpp
    Wolf.cpp
    Simulation.cpp
)

target_include_directories(predator_prey PRIVATE .)