#include <iostream>
#include <vector>
#include "include/mnist/mnist_reader.hpp"
#include "include/mnist/mnist_utils.hpp"
#include "include/Network.h"
#include "include/Feeder.h"

using namespace std;

int main()
{

    std::cout << std::endl << "MNIST DATA DIRECTORY : " << MNIST_DATA_LOCATION << std::endl;
    std::cout << "MNIST DIR DIRECTORY : " <<  MNIST_DIR_LOCATION << std::endl;

    // Load MNIST data
    mnist::MNIST_dataset<std::vector, std::vector<uint8_t>, uint8_t> dataset =
            mnist::read_dataset<std::vector, std::vector, uint8_t, uint8_t>(MNIST_DATA_LOCATION);




    std::cout << "Nbr of training images = " << dataset.training_images.size() << std::endl; // 60k
    std::cout << "Nbr of training labels = " << dataset.training_labels.size() << std::endl; // 60k
    std::cout << "Nbr of test images = " << dataset.test_images.size() << std::endl;         // 10k
    std::cout << "Nbr of test labels = " << dataset.test_labels.size() << std::endl;         // 10k



    //vector<vector<float>> input = dataset.training_images ;
    //vector<vector<float>> outputs = dataset.training_labels;
    vector<vector<float>> inputs;
    for(const auto & datasetImage : dataset.training_images){
        vector<float> image;
        for(const auto  & pixel: datasetImage){
            image.emplace_back(static_cast<float>(pixel)/255);//255
        }
        inputs.emplace_back(image);
    }


    vector<vector<float>> outputs;
    for(const auto & datasetOutput : dataset.training_labels ){
        vector<float> output(10,0);
        unsigned objective =  static_cast<unsigned>(datasetOutput);
        output[objective] = 1;
        outputs.emplace_back(output);
    }




    Network network({150,50}, inputs, outputs, 400,0.1 );
    cout << network;
    network.main();






    //getting the test images ready for test
    vector<vector<float>> testImages;
    for(const auto & datasetImage : dataset.test_images){
        vector<float> image;
        for(const auto  & pixel: datasetImage){
            image.emplace_back(static_cast<float>(pixel)/255);//255
        }
        testImages.emplace_back(image);
    }

    //getting the test labels ready for test
    vector<float> expectedOutput;
    for(const auto & datasetOutput : dataset.test_labels ){
        expectedOutput.emplace_back(static_cast<unsigned>(datasetOutput));
    }

    // testing, reading the outputs of the network and comparing to what was expected
    //ffActivation means feedforward Activation
    vector<vector<float>> testResult = network.testFeedforward(testImages);
    unsigned testResultSize = testResult.size();
    unsigned success = 0;
    for(unsigned i = 0; i< testResultSize;++i){
        const vector<float> ffResult = testResult[i];
        float max = -1;
        unsigned indexOfMax = 20;

        for(unsigned j =0; j< ffResult.size(); ++j){
            if(ffResult[j]>max){
                max =ffResult[j];
                indexOfMax = j;
            }
        }
        //std::cout << "\n guess : "<< indexOfMax << " expected :" << expectedOutput[i];
        if( indexOfMax == expectedOutput[i]){
            ++success;
        }
    }

    std::cout << "ratio right answer : " << float(success)/float(expectedOutput.size()) ;






    return 0;

}

