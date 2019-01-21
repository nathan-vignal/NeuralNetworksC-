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

void Layer::processLayerError(Layer nextlayer ) {
    float err;

    // Tous les neurones du layer
    for (unsigned i(0); this->neurons.size() -1; ++i) {

        // Tous les neurones du layer l+1
        for (unsigned j(0); nextlayer.neurons.size() -1; ++j) {

            //     Toutes les erreurs k du vecteur d'erreur du neurone i du layer l
            for (auto k : neurons[i]->getError()) {

                // Toutes les erreurs l du vecteur d'erreur du neurone j du layer l+1
                for (auto l : nextlayer.neurons[j]->getError()) {

                    for (auto w : nextlayer.neurons[j]->getWeights()) {

                        // vecteur erreur         ->poids w du neurone J du layer l+1 * erreur w du neurone J du layer l+1
                        //                                       w1 * E1
                        err = nextlayer.neurons[j]->getWeights()[w] * nextlayer.neurons[j]->getError()[w];

                        // on somme tout w1 * E1 + .. + wn * En
                        err =+ err;
                    }

                }
            }
        }
        // on multiple donc la somme par sigmoidPrime
        neurons[i]->getError().emplace_back(err * Neuron::sigmoidPrime((neurons[i]->getActivation(i))));
    }










}


