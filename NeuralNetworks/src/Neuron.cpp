#include "Neuron.h"
#include <random>
#include <iostream>
#include <Network.h>
//int Exemple::compteur = 0;

unsigned short Neuron::maxWeight = 3;
unsigned short Neuron::maxBias = 3;

Neuron::Neuron( const unsigned short & nbWeights )
{
    /* initialisation des poids est des biais*/
    for(unsigned i =0;i<nbWeights;++i){
        if(rand()%2)
            weights.emplace_back( -1 *rand() % maxWeight);
        else{
            weights.emplace_back( rand() % maxWeight);}


    }

    bias = rand()% maxBias;
    if(rand()%2)
        bias *= -1;
    //ctor
}

Neuron::~Neuron  ()
{
    //dtor
}

float Neuron::sigmoid(float x) {
    return( 1/(1+float(exp(-x))));
}

float Neuron::sigmoidPrime(float x) {
    return( sigmoid(x)*(1-sigmoid(x)));
}



void Neuron::processActivations(const std::vector<std::vector<float>> &previousLayerActivations) {

    for(const std::vector<float> & layerActivation : previousLayerActivations){
        float sum=0;
        for(auto preActivation : hadamardProduct(layerActivation,weights))
            sum += preActivation;
        sum += bias;
        preActivation.emplace_back(sum);
        activations.emplace_back(sigmoid(sum)) ;
    }
}




std::vector<float> Neuron::hadamardProduct(const std::vector<float> & vector1, const std::vector<float> & vector2) {
    std::vector<float> result;
    try {
        if ( vector1.size() != vector2.size()){
            std::cout <<vector1.size() << " les vecteurs ne sont pas de la même taille "<<vector2.size() <<std::endl ;
            throw "les vecteurs ne sont pas de la même taille";}
    }
    catch(const std::string & message) {
        std::cout << message;
    }
    for(unsigned i =0 ; i<vector1.size() ; ++i )
        result.emplace_back(vector1[i] * vector2[i])  ;
    return result;

}


const std::vector<float> & Neuron::getActivations() const {
    return activations;
}




const float& Neuron::getActivation(const unsigned short adress) {
    return activations[adress];
}

std::vector<float> Neuron::getError() {
    return error;
}

std::ostream &operator<<(std::ostream &os, const Neuron &neuron) {
    for (auto activation : neuron.error) {// mettre activations

        os << activation;
        os << "  ";
    }

    return os;

}

void Neuron::resetActivations() {
    activations.clear();
    error.clear();
    preActivation.clear();
}

void Neuron::processLastNeuronError(std::vector<float> activationBP) {

    for ( unsigned i = 0; i < activationBP.size() ; ++i ) {
        this->error.emplace_back(this->getActivation(i) - activationBP[i]);
    }
}
/**
 * process the changes on the weights and biaises
 * - learningRate * (1/numberOfFeedForwards) * (partials derivatives of the costs with respect to this neuron summed up)
 */
void Neuron::gradientDescent(std::vector<std::vector<float>> previousLayerActivations) {
    //bias update
    float meanError = 0;
    for(auto feedforwardError : error){
        meanError += feedforwardError;
    }
    meanError  /= error.size();
    bias -= - (Network::learningRate) * meanError;

    //weights update
    for(unsigned weightNumber = 0 ; weightNumber< weights.size()-1; ++weightNumber){
        float weightChangesSummed = 0;
        for(unsigned feedforwarNumber =0; feedforwarNumber< previousLayerActivations[weightNumber].size()-1; ++feedforwarNumber){
            weightChangesSummed += previousLayerActivations[weightNumber][feedforwarNumber] * error[feedforwarNumber];
        }

        weights[weightNumber]  += - (Network::learningRate/error.size()) *  (weightChangesSummed/error.size())   ;
    }
}


std::vector<float> Neuron::getWeights() {
    return weights;
}

const std::vector<float> &Neuron::getPreActivation() const {
    return preActivation;
}

void Neuron::addError(float _error) {
    error.emplace_back(_error);
}

