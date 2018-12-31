#include "Network.h"
using namespace std;
Network::Network(const unsigned short &nbLayer, const unsigned short &nbNeuron,
                 const std::vector<std::vector<int> > &_entries, const std::vector<std::vector<int> > &_output) {
    entries = _entries;
    output = _output;
    for (unsigned i=0; i<nbLayer; ++i){
        layers.emplace_back( Layer(nbNeuron));  //emplace_back plus opti que push_back
    }
}

Network::~Network() {
    //dtor
}

std::ostream& operator<< (std::ostream& stream, Network & network){
    for ( const auto & batchOutput : network.output )
        for ( const auto & neuronOutput : batchOutput )
        stream << neuronOutput << endl;
    return stream;
}


