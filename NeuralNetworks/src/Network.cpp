#include <iostream>
#include "Network.h"
#include <math.h>
using namespace std;

const float Network::learningRate = 0.15;
Network::Network(const unsigned short &nbLayer, const unsigned short &nbNeuron,
                 const std::vector<std::vector<float> > &_entries, const std::vector<std::vector<float> > &_output
        , const unsigned short & _numberOfEpochs) {

    output = _output;
    numberOfEpochs = _numberOfEpochs;
    //distribution of the entry data on epochs
    for(unsigned i = 1 ; i<=numberOfEpochs; ++i){
        entries.emplace_back( std::vector<std::vector<float> > (&_entries[(_entries.size()/numberOfEpochs)*(i-1)],&_entries[(_entries.size()/numberOfEpochs)*(i)]));
    }

    //sub(&data[100000],&data[101000]);
    //Layer(number of neurons, number of Neurons In the Previous Layer );

    Layer *  firstLayer = new Layer(nbNeuron,(unsigned short)entries[0][0].size());
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



void Network::feedforward(const unsigned short numberOfTheEpoch) {
    /* std::vector<int>   data();
     // Load Z elements into data so that Z > Y > X

     std::vector<int>   sub(&data[100000],&data[101000]);*/
    layers[0]->processMyNeuronsActivations(entries[numberOfTheEpoch]);
    for(unsigned i=1; i < layers.size(); ++i){
        layers[i]->processMyNeuronsActivations(layers[i-1]->getMyactivations());
    }
}

std::ostream& operator<< (std::ostream& stream, Network & network) {
    cout << "\nnetwork of "<< network.layers.size()<<" layers :" << '\n';
    for (const auto layer : network.layers) {
        stream << " layer ";
        stream <<  * layer<<endl;

    }
    return stream;
}

const vector<Layer *> &Network::getLayers() const {
    return layers;
}
/**
 * process network global cost for each feedforward
 */
void Network::processCost() {
    cost.clear();
    std::vector<std::vector<float>> lastLayerActivations = getLayers()[getLayers().size()-1]->getMyactivations();

    for(unsigned neuronNumber = 0; neuronNumber < lastLayerActivations[0].size(); ++neuronNumber ){
        float cost = 0;
        for(unsigned feedForwardNumber = 0; feedForwardNumber < lastLayerActivations.size(); ++feedForwardNumber){//feedForwardNumber is the number of the entry that was used to process this activation
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

void Network::vectorResizing(std::vector<std::vector<float>> vector, unsigned rows, unsigned columns) {
    vector.resize(rows);
    for ( auto &it : vector) {
        it.resize(columns);
    }
}

std::vector<std::vector<float>> functionSquare(std::vector<std::vector<float>> entree) {
    std::vector<std::vector<float>> attendu = entree;
    for (unsigned i(0); i < attendu.size(); ++i) {
        for(unsigned j(0); j < attendu[i].size(); ++j) {
            attendu[i][j] = attendu[i][j] * attendu[i][j];
        }
    }
    return attendu;
}

void Network::resetActivations() {
    for(Layer * layer : layers){
        layer->resetActivations();
    }
}

void Network::main() {
    for(unsigned short i=0 ; i<numberOfEpochs; ++i){
        feedforward(i);
        processCost();
        backPropagation();
        gradientDescent();
        resetActivations();
    }
}

void Network::backPropagation(){
    //process the partial derivative with respect to z for each layer

    layers[layers.size()-1]->processLastLayerError(output); //process the partial derivative of c with respect to z for the last layer
    for(unsigned i = layers.size()-2 ; i > 0; --i){ //use the partial derivative c/z of the n+1 layer to process it for n
        cout << "hi";
        // *layers[i]->processLayerError();

    }
}

void Network::gradientDescent() {

}








