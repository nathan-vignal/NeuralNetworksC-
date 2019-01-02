#include <iostream>
#include "Network.h"
#include <math.h>
using namespace std;
Network::Network(const unsigned short &nbLayer, const unsigned short &nbNeuron,
                 const std::vector<std::vector<float> > &_entries, const std::vector<std::vector<float> > &_output) {
    entries = _entries;
    output = _output;
    //Layer(number of neurons, number of Neurons In the Previous Layer );

    Layer *  firstLayer = new Layer(nbNeuron,(unsigned short)entries[0].size());
    layers.emplace_back(firstLayer );  //emplace_back plus opti que push_back

    for (unsigned i=1; i<nbLayer-1; ++i){
        auto * layer = new Layer(nbNeuron,nbNeuron);
        layers.emplace_back( layer );  //emplace_back plus opti que push_back
    }
    Layer * lastLayer = new Layer((unsigned short)output[0].size(),nbNeuron);
    layers.emplace_back(lastLayer );  //emplace_back plus opti que push_back
}

Network::~Network() {
    //dtor
}



void Network::feedforward() {
    layers[0]->processMyNeuronsActivations(entries);
    for(unsigned i=1; i < layers.size(); ++i){
        std::cout << i;
        layers[i]->processMyNeuronsActivations(layers[i-1]->getMyactivations());
    }
}

std::ostream& operator<< (std::ostream& stream, Network & network) {
    cout << "\nnetwork : "<< network.layers.size() << '\n';
    for (const auto layer : network.layers) {
        stream << " layer ";
        stream <<  * layer<<endl;

    }
    return stream;
}

const vector<Layer *> &Network::getLayers() const {
    return layers;
}

void Network::processCost() {
    std::vector<std::vector<float>> lastLayerActivations = getLayers()[getLayers().size()-1]->getMyactivations();

    for(unsigned neuronNumber = 0; neuronNumber < lastLayerActivations[0].size(); ++neuronNumber ){
        float cost = 0;
        for(unsigned feedForwardNumber = 0; feedForwardNumber < lastLayerActivations.size(); ++feedForwardNumber){//feedForwardNumber is the number of the entry that was used to process this activation
            cout << "feed forward = " << feedForwardNumber << " neuron Number = " << neuronNumber <<endl;
            cost += (output[feedForwardNumber][neuronNumber] * log(lastLayerActivations[feedForwardNumber][neuronNumber])
                        + (1- output[feedForwardNumber][neuronNumber])* log(1- lastLayerActivations[feedForwardNumber][neuronNumber]));
            //  the formula used is cross entropy c = y * ln(a) + (1-y) * ln(1-a)
                            //        y = output[feedForwardNumber][neuronNumber]  a= lastLayerActivations[feedForwardNumber][neuronNumber]
        }
        cost *= float(-1)/lastLayerActivations.size();
        this->cost.emplace_back(cost);
    }

}

const vector<float> &Network::getCost() const {
    return cost;
}
