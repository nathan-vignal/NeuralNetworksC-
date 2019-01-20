#include <iostream>
#include "Layer.h"
Layer::Layer(const unsigned short &nbNeurons, const unsigned short &nbNeuronsInPreviousLayer) {

    for(unsigned i = 0; i<nbNeurons;++i){
        auto * neuron = new Neuron(nbNeuronsInPreviousLayer);
        neurons.emplace_back( neuron );
    }

}

Layer::~Layer()
{
    //dtor
}

 std::vector <std::vector<float>>  Layer::getMyactivations() {
    std::vector <std::vector<float>> result(neurons[0]->getActivations().size());
    for(unsigned short i = 0; i< neurons[0]->getActivations().size(); ++i){
        for(Neuron * neuron: neurons){
            result[i].emplace_back(neuron->getActivation(i));

        }
    }
    return result;
}



void Layer::processMyNeuronsActivations(const std::vector<std::vector<float>> &previousLayerActivations) {
    for(auto neuron: neurons){

        neuron->processActivations(previousLayerActivations);
    }

}


std::ostream& operator<<(std::ostream &stream, Layer &layer) {

    for (Neuron *neuron : layer.neurons) {
        stream <<  * neuron;
    }


    return stream;
}

unsigned short Layer::getNumberOfNeurons() {
    return (unsigned short)neurons.size();

}
void Layer::resetActivations() {
    for(auto neuron : neurons ){
        neuron->resetActivations();
    }
}
/**
 * process the derivative of c with respect to z for each neuron and for each feedforward
 * @param output expected output of the feedforward
 */
void Layer::processLastLayerError(std::vector<std::vector<float>> output){


    for(unsigned neuronNumber=0; neuronNumber<neurons.size()-1;++neuronNumber){
        std::vector<float> outputForTheNeuronN;
        //modèle le vecteur des valeurs attendu pour ce neuron, à partir du vecteur output
        for(unsigned feedForwardNumber=0; feedForwardNumber<output.size()-1; ++feedForwardNumber){
            outputForTheNeuronN.emplace_back(output[feedForwardNumber][neuronNumber]);
        }
        //donne au neuron le vecteur des valeurs attendu pour qu'il calcule son erreur
        neurons[neuronNumber]->processLastNeuronError(outputForTheNeuronN);
        outputForTheNeuronN.clear();


    }

}
void Layer::layerGradientDescent(Layer *nextLayer) {

    for (auto neuron : neurons){
    }
}
void Layer::processLayerError() {


}


