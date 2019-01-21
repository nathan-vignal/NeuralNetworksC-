#include <iostream>
#include <vector>
#include "Network.h"
#include "Feeder.h"
using namespace std;

int main()
{
    vector<vector<float>> input ;
    vector<vector<float>> output ;
    Feeder::createData( input,  output);/*
    for(auto truc : input){
        cout << '\n';
        for(auto truc2: truc){
            cout << truc2 << " ";
        }
    }*/



   /* vector<vector<float>> input = {{0,0.8,0.3,0.9},{1,0.8,0.6,0.4},{0.1,0.2,0.2,0.6},{0.1,0.2,0.2,0.6}};
    vector<vector<float>> output = {{0,1,1,0},{1,0,1,0},{1,1,1,0},{0,0,1,0}};*/
                    //Network(nombre de layer, nombre de neuron par layer, input, output)

    Network network((unsigned short)4,(unsigned short)3,input,output,4);
    cout << network ;

    network.main();

    for(auto truc :network.testFeedforward({1,1,1,1}) ){
        cout<< "ne va pas afficher un truc grand "<< truc << '\n' ;
    }




    /*cout << network;
    for(auto neuronCost : network.getCost())
        cout << neuronCost<< ' '; */

    //network.getLayers()[network.getLayers().size()-1].get


    return 0;
}
