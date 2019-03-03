cmake_minimum_required(VERSION 3.13)
project(NeuralNetworks)
set(CMAKE_CXX_STANDARD 14)




find_package(MNIST PATHS ..)




include_directories(${MNIST_INCLUDE_DIR})




add_executable(NeuralNetworks
        include/Layer.h
        include/Network.h
        include/Neuron.h
        include/Feeder.h
        include/mnist/mnist_reader.hpp
        include/mnist/mnist_reader_common.hpp
        include/mnist/mnist_reader_less.hpp
        include/mnist/mnist_utils.hpp
        src/Feeder.cpp
        src/Layer.cpp
        src/Network.cpp
        src/Neuron.cpp
        main.cpp)


include_directories(${MNIST_INCLUDE_DIR})
target_compile_features(NeuralNetworks PRIVATE cxx_range_for)

# Pass MNIST data directory to main.cpp
target_compile_definitions(NeuralNetworks PRIVATE MNIST_DATA_LOCATION="../data")
target_compile_definitions(NeuralNetworks PRIVATE MNIST_DIR_LOCATION="..")