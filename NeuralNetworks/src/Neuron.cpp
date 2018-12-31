#include "Neuron.h"
#include <random>
//int Exemple::compteur = 0;

unsigned short Neuron::maxWeight = 2;
unsigned short Neuron::minWeight = 2;
std::random_device Neuron::rd;
std::mt19937 Neuron::gen(Neuron::rd()); //Standard mersenne_twister_engine seeded with rd()
std::uniform_real_distribution<> Neuron::dis(Neuron::maxWeight, Neuron::minWeight);

Neuron::Neuron(const unsigned short & nbNeurons)
{
    for(unsigned i =0;i<nbNeurons;++i){
        weights.emplace_back(Neuron::dis(gen));
    }
    //ctor
}

Neuron::~Neuron()
{
    //dtor
}

const std::vector<std::vector<float>> & Neuron::getActivations() const {
    return activations;
}

