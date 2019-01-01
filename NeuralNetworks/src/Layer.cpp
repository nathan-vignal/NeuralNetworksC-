#include "Layer.h"

Layer::Layer(const unsigned short &nbNeurons) {
    for(unsigned i = 0; i<nbNeurons;++i){
        Neuron * pointer ;
        Neuron neuron = Neuron(nbNeurons);
        pointer = & neuron;
        neurons.emplace_back( pointer );
    }

}

Layer::~Layer()
{
    //dtor
}

std::vector <std::vector<float>> Layer::getMyactivations() {
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

