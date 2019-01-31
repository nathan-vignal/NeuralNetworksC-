cmake_minimum_required(VERSION 3.13)
project(NeuralNetworks)
find_package( OpenCV REQUIRED )
set(CMAKE_CXX_STANDARD 14)

include_directories(include ${OpenCV_INCLUDE_DIRS})

add_executable(NeuralNetworks
        include/Layer.h
        include/Network.h
        include/Neuron.h
        include/Feeder.h
        src/ImageReader.hpp
        src/mnist_reader.hpp
        src/mnist_reader_common.hpp
        src/Feeder.cpp
        src/Layer.cpp
        src/Network.cpp
        src/Neuron.cpp
        main.cpp)
target_link_libraries( NeuralNetworks ${OpenCV_LIBS} )