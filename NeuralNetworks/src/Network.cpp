#include <iostream>
#include "Network.h"
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