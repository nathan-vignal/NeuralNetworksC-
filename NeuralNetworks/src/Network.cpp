#include <iostream>
#include "Network.h"
#include <math.h>
using namespace std;

const float Network::learningRate = 0.15;
Network::Network(const unsigned short &nbLayer, const unsigned short &nbNeuron,
                 const std::vector<std::vector<float> > &_entries, const std::vector<std::vector<float> > &_output
        , const unsigned short & _numberOfEpochs) {

    //output = _output;
    numberOfEpochs = _numberOfEpochs;
    //distribution of the entry data on epochs
    for(unsigned i = 1 ; i<=numberOfEpochs; ++i){
        entries.emplace_back( std::vector<std::vector<float> > (&_entries[(_entries.size()/numberOfEpochs)*(i-1)],&_entries[(_entries.size()/numberOfEpochs)*(i)]));
    }

    for(unsigned i = 1 ; i<=numberOfEpochs; ++i){
        output.emplace_back( std::vector<std::vector<float> > (&_output[(_output.size()/numberOfEpochs)*(i-1)],&_output[(_output.size()/numberOfEpochs)*(i)]));
    }

    for(auto & first : entries){
        cout << "\n";
        for(auto & second : first){
            cout << "[";
            for( auto & data : second){
                cout << data <<" ";
            }
            cout << "]";
        }
    }


    Layer *  firstLayer = new Layer(nbNeuron,(unsigned short)entries[0][0].size());
    layers.emplace_back(firstLayer );  //emplace_back plus opti que push_back

    for (unsigned i=1; i<nbLayer-1; ++i){
        auto * layer = new Layer(nbNeuron,nbNeuron);
        layers.emplace_back( layer );  //emplace_back plus opti que push_back
    }
    Layer * lastLayer = new Layer((unsigned short)output[0][0].size(),nbNeuron);
    layers.emplace_back(lastLayer );  //emplace_back plus opti que push_back
}

Network::~Network() {
    //dtor
}



void Network::feedforward(const unsigned short numberOfTheEpoch) {
    layers[0]->processMyNeuronsActivations(entries[numberOfTheEpoch]);
    std::cout << "numberOfTheEpoch " << numberOfTheEpoch <<endl;
    for(unsigned i=1; i < layers.size(); ++i){
        layers[i]->processMyNeuronsActivations(layers[i-1]->getMyactivations());
    }
}

vector<vector<float>> Network::testFeedforward(const std::vector<float> &entries) {
    //pour les test
    /*for(auto neuron : this->layers[this->layers.size()-1]->getNeurons()){
        neuron->debugSetBias(10);
    }*/
    //fin pour les test
    layers[0]->processMyNeuronsActivations({entries});
    for(unsigned i=1; i < layers.size(); ++i){
        layers[i]->processMyNeuronsActivations(layers[i-1]->getMyactivations());
    }
    //std::cout << * layers[layers.size()-1];
    return layers[layers.size()-1]->getMyactivations();
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
 *//*
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
*/
const vector<float> &Network::getCost() const {
    return cost;
}

void Network::vectorResizing(std::vector<std::vector<float>> vector, unsigned rows, unsigned columns) {
    vector.resize(rows);
    for ( auto &it : vector) {
        it.resize(columns);
    }
}


void Network::resetActivations() {
    for(Layer * layer : layers){
        layer->resetActivations();
    }
}

void Network::main() {
    for(unsigned short i=0 ; i<numberOfEpochs; ++i){
        feedforward(i);
        //processCost(); inutile
        backPropagation(i);
        std::cout << *this;
        std::cout<< '\n';
        gradientDescent(i);

        resetActivations();
    }
}

void Network::backPropagation(unsigned short numberOfTheEpoch) {
    //process the partial derivative with respect to z for each layer
    cout << "batch backpropagation"<<endl;

    layers[layers.size()-1]->processLastLayerError(output[numberOfTheEpoch]); //process the partial derivative of c with respect to z for the last layer
    std::cout << * layers[layers.size()-1];
    for(unsigned i = (unsigned)layers.size()-2 ; i >= 0 && i<9999; --i){ //use the partial derivative c/z of the n+1 layer to process it for n
                //condition i<99999 car 0-1 = 42000000 dans le référentiel des unsigned
        layers[i]->processLayerError(*layers[i+1]);

    }
}

void Network::gradientDescent(unsigned short batchNumber) {
    for(unsigned layerNumber =layers.size()-1; layerNumber>0;--layerNumber  ){
        layers[layerNumber]->layerGradientDescent(layers[layerNumber-1]->getMyactivations());
    }
    for (auto t : entries[batchNumber]){
        std::cout << "lastLayer[";
        for( auto y : t)
        std::cout << y;
        std::cout << "] \n";
    }
    layers[0]->layerGradientDescent(entries[batchNumber]);

}








