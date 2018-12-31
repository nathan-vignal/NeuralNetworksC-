cmake_minimum_required(VERSION 3.13)
project(NeuralNetworks)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(NeuralNetworks
        include/Layer.h
        include/Network.h
        include/Neuron.h
        src/Layer.cpp
        src/Network.cpp
        src/Neuron.cpp
        main.cpp)
