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

    return 0;



    /*
    vector<vector<float>> input ;
    vector<vector<float>> output ;
    Feeder::createData( input,  output);
     */

    /*
    for(auto truc : input){
        cout << '\n';
        for(auto truc2: truc){
            cout << truc2 << " ";
        }
    }
     */



    /*vector<vector<float>> input = {{0,0.8,0.3,0.9},{1,0.8,0.6,0.4},{0.1,0.2,0.2,0.6},{0.1,0.2,0.2,0.6}};
    vector<vector<float>> output = {{0,1,1,0},{1,0,1,0},{1,1,1,0},{0,0,1,0}};*/
                    //Network(nombre de layer, nombre de neuron par layer, input, output)

    //Network network({4,4}, input, output, 1000,0.0000001 );
    //network.feedforward(0);
    //network.backPropagation(0)



    /*cout << network;
    network.main();
    std::cout<< '\n';
    while(1){
        float first = 0;
        float second = 0;
        float third = 0;
        float four = 0;

        cout << "veuillez entrer un vecteur ";
        cin >> first;
        cin >> second;
        cin >> third;
        cin >> four;
        for(auto neuronResult :network.testFeedforward({first,second,third,four}) ){
            cout<< '\n';
            for( auto data : neuronResult)
                cout<< " "<< data  ;
        }



    }
    cout<< "1110";

    cout<< "\n\n1000";
    for(auto neuronResult :network.testFeedforward({1,0,0,0}) ){
        cout<< '\n';
        for( auto data : neuronResult)
            cout<< " "<< data  ;
    }
    cout<< "0110";
    for(auto neuronResult :network.testFeedforward({0,1,1,0}) ){
        cout<< '\n';
        for( auto data : neuronResult)
            cout<< " "<< data  ;
    }



    return 0;
     */

}
