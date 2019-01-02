#include <iostream>
#include <vector>
#include "Network.h"

using namespace std;

int main()
{

    vector<vector<float>> input = {{0,0,0,0},{2,3,4,5}};
    vector<vector<float>> output = {{0,1,1,0},{5,4,3,2}};
                    //Network(nombre de layer, nombre de neuron par layer, input, output)
    Network network((unsigned short)4,(unsigned short)4,input,output);
    network.feedforward();
    //cout << network;
    network.processCost();
    for(auto neuronCost : network.getCost())
        cout << neuronCost<< ' ';


    return 0;
}
