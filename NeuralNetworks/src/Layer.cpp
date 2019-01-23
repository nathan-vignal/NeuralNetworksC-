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


    for(unsigned neuronNumber=0; neuronNumber<neurons.size();++neuronNumber){
        std::vector<float> outputForTheNeuronN;
        //modèle le vecteur des valeurs attendu pour ce neuron, à partir du vecteur output
        for(unsigned feedForwardNumber=0; feedForwardNumber<output[0].size()-1; ++feedForwardNumber){
            outputForTheNeuronN.emplace_back(output[feedForwardNumber][neuronNumber]);

        }

        //donne au neuron le vecteur des valeurs attendu pour qu'il calcule son erreur
        neurons[neuronNumber]->processLastNeuronError(outputForTheNeuronN);
        outputForTheNeuronN.clear();
    }

}

/**
 *
 * @param nextLayer
 */
void Layer::processLayerError(const Layer &nextLayer)  {
    //use to debug
    /*std::cout << " PROCESS layer error" <<std::endl;
    for(auto neuron : nextLayer.getNeurons()){
        std::cout << * neuron;
        std::cout << '\n' <<std::endl;
    }*/

    for(auto neuron : neurons){ // for each of my neurons
        float sum = 0;
        for(unsigned feedforwardNumber=0 ; feedforwardNumber < nextLayer.getNeuronErrors().size()-1; ++feedforwardNumber){ //for each of the feeforwards

            for(auto nextLayerNeuron : nextLayer.getNeurons()){ // for each of the nextLayer neurons
                //std::cout << "ha" << nextLayerNeuron->getError()[feedforwardNumber] ;
                sum +=  nextLayerNeuron->getError()[feedforwardNumber] * nextLayerNeuron->getWeights()[feedforwardNumber];

                //sum += weights(to the next neuron)* error(in the linked neuron)
            }
            sum /= nextLayer.getNeurons().size();
            neuron->addError(Neuron::sigmoidPrime( neuron->getPreActivation()[feedforwardNumber])* sum);
            sum = 0;


        }

    }
}










void Layer::layerGradientDescent(const std::vector<std::vector<float>> &previousLayerActivation) {
    for(auto neuron : neurons){
        //std::cout << *neuron;
        neuron->gradientDescent( previousLayerActivation);
    }


}


std::vector<std::vector<float>> Layer::getNeuronErrors()const{
    std::vector<std::vector<float>> neuronsError;
    for(auto neuron : neurons){
        neuronsError.emplace_back(neuron->getError());
    }
    return neuronsError;

}

const std::vector<Neuron *> &Layer::getNeurons() const {
    return neurons;
}
