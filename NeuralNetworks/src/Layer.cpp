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

