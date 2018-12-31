#include "Neuron.h"
#include <random>
#include <iostream>
//int Exemple::compteur = 0;

unsigned short Neuron::maxWeight = 10;
unsigned short Neuron::maxBias = 10;

Neuron::Neuron(const unsigned short & nbNeurons)
{
    for(unsigned i =0;i<nbNeurons;++i){
        if(rand()%2)
            weights.emplace_back( -1 *rand() % maxWeight);
        else{
            weights.emplace_back( rand() % maxWeight);}


    }
    bias = rand()% maxBias;



    //ctor
}

Neuron::~Neuron  ()
{
    //dtor
}

float Neuron::sigmoid(float x) {
    return( 1/(1+float(exp(-x))));
}

void Neuron::processActivation(const std::vector<float> &previousLayerActivations) {
    float myActivation = 0;
    for(const float & activation: hadamardProduct(weights,previousLayerActivations)){
        myActivation += activation;
    }
    activations.emplace_back(myActivation) ;

}


std::vector<float> Neuron::hadamardProduct(const std::vector<float> & vector1, const std::vector<float> & vector2) {
    std::vector<float> result;
    try {
        if (vector1.size() != vector2.size())
            throw "les vecteurs ne sont pas de la même taille";
    }
    catch(const std::string & message) {
            std::cout << message;
        }
    for(unsigned i =0 ; i<vector1.size() ; ++i )
        result[i] = vector1[i] * vector2[i];
    return result;

}


const std::vector<float> & Neuron::getActivations() const {
    return activations;
}
const float & Neuron::getLastActivations() const {
    return activations[activations.size()];

}

std::ostream &operator<<(std::ostream &os, const Neuron &neuron){
    for (auto activation : neuron.weights ) // mettre activations
        os << activation << ' ';


    return os;

}
