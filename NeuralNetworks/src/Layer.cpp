#include "Layer.h"

Layer::Layer(const unsigned short &nbNeurons) {
    for(unsigned i = 0; i<nbNeurons;++i){
        Neuron *pointer ;
        Neuron neuron = Neuron(nbNeurons);
        pointer = & neuron;
        neurons.emplace_back( pointer );
    }

}

Layer::~Layer()
{
    //dtor
}

std::vector<std::vector <std::vector<int>>> Layer::getMyactivations() {
    std::vector<std::vector <std::vector<int>>> result;
    for(Neuron * neuron: neurons){
        result.emplace_back(neuron->getActivations());
    }
    return result;
}

std::vector <std::vector<int>> Layer::getTheLastBatchActivation() {
    std::vector <std::vector<int>> result;
    for(Neuron * neuron: neurons){
        result.emplace_back(neuron->getActivations());
    }

    return  result


}

