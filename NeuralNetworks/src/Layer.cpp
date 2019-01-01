#include <iostream>
#include "Layer.h"
Layer::Layer(const unsigned short &nbNeurons, const unsigned short &nbNeuronsInPreviousLayer) {

    std::cout << "\nnew layer";
    for(unsigned i = 0; i<nbNeurons;++i){
        std::cout <<"  nb weights    " <<nbNeuronsInPreviousLayer<< "   ";
        auto * neuron = new Neuron(nbNeuronsInPreviousLayer);
        std::cout << neuron;
        neurons.emplace_back( neuron );
    }

}

Layer::~Layer()
{
    //dtor
}

 std::vector <std::vector<float>>  Layer::getMyactivations() {
    std::vector <std::vector<float>> result;
    for(Neuron * neuron: neurons){
        result.emplace_back(neuron->getActivations());
    }
    return result;
}

std::vector<float> Layer::getTheLastBatchActivation() {
    std::vector<float> result;
    for(Neuron * neuron: neurons){
        result.emplace_back(neuron->getLastActivations());
    }

    return  result;


}


void Layer::processMyNeuronsActivations(const std::vector<std::vector<float>> &previousLayerActivations) {
    for(auto neuron: neurons){
        neuron->processActivations(previousLayerActivations);
    }

}


std::ostream& operator<<(std::ostream &stream, Layer &layer) {
    std::cout << "neuron";
    for (Neuron *neuron : layer.neurons) {

        stream << neuron;
    }


    return stream;
}

