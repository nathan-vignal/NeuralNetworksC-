#include <iostream>
#include "Network.h"
#include <math.h>
using namespace std;

const float Network::learningRate = 1;
Network::Network(const std::vector<unsigned short> &hiddenLayers, const std::vector<std::vector<float> > &_entries,
                 const std::vector<std::vector<float> > &_output, const unsigned int &_numberOfEpochs,
                 const double &_regularizationTerm) {



    regularizationTerm = _regularizationTerm;
    numberOfEpochs = _numberOfEpochs;
    //distribution of the entry data on epochs
    for(unsigned i = 1 ; i<=numberOfEpochs; ++i){
        entries.emplace_back( std::vector<std::vector<float> > (&_entries[(_entries.size()/numberOfEpochs)*(i-1)],&_entries[(_entries.size()/numberOfEpochs)*(i)]));
    }

    for(unsigned i = 1 ; i<=numberOfEpochs; ++i){
        output.emplace_back( std::vector<std::vector<float> > (&_output[(_output.size()/numberOfEpochs)*(i-1)],&_output[(_output.size()/numberOfEpochs)*(i)]));
    }
/*
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
    std::cout <<'\n'<<'\n';
    for(auto & first : output){
        cout << "\n";
        for(auto & second : first){
            cout << "[";
            for( auto & data : second){
                cout << data <<" ";
            }
            cout << "]";
        }
    }
    */
    //if there are hidden layers
    if(0< hiddenLayers.size()){
        //creating the first hidden layer
        Layer *  firstLayer = new Layer(hiddenLayers[0],(unsigned short)entries[0][0].size());
        layers.emplace_back(firstLayer );  //emplace_back plus opti que push_back




        //création des layer
        for (unsigned i=1; i<hiddenLayers.size(); ++i){
            auto * layer = new Layer(hiddenLayers[i],hiddenLayers[i-1]);
            layers.emplace_back( layer );  //emplace_back plus opti que push_back
        }

        //output layer
        Layer * lastLayer = new Layer((unsigned short)output[0][0].size(),hiddenLayers[hiddenLayers.size()-1]);
        layers.emplace_back(lastLayer );  //emplace_back plus opti que push_back
    }else{
        //output layer
        Layer * lastLayer = new Layer((unsigned short)output[0][0].size(),(unsigned short)entries[0][0].size());
        layers.emplace_back(lastLayer );  //emplace_back plus opti que push_back
    }

}

Network::~Network() {
    //dtor
}



void Network::feedforward(const unsigned int &numberOfTheEpoch) {
    layers[0]->processMyNeuronsActivations(entries[numberOfTheEpoch]);


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
    vector<vector<float>> result = layers[layers.size()-1]->getMyactivations();
    resetActivations();
    return result;
}


std::ostream& operator<< (std::ostream& stream, Network & network) {
    stream << '\n';
    stream << "\nNETWORK of "<< network.layers.size()<<" layers :" << '\n';
    for (const auto layer : network.layers) {
        stream << " LAYER ";
        stream <<  * layer<<endl;


    }
    stream << '\n';
    return stream;
}

const vector<Layer *> &Network::getLayers() const {
    return layers;
}

/**
 * process network global cost for each feedforward in the given batchNumber
 */
void Network::processCost(const unsigned int &batchNumber) {
    costs.clear();
    std::vector<std::vector<float>> lastLayerActivations = getLayers()[getLayers().size()-1]->getMyactivations();

    for(unsigned neuronNumber = 0; neuronNumber < lastLayerActivations[0].size(); ++neuronNumber ){
        float cost = 0;
        for(unsigned feedForwardNumber = 0; feedForwardNumber < lastLayerActivations.size(); ++feedForwardNumber){//feedForwardNumber is the number of the entry that was used to process this activation
            cost += (output[batchNumber][feedForwardNumber][neuronNumber] * log(lastLayerActivations[feedForwardNumber][neuronNumber])
                     + (1- output[batchNumber][feedForwardNumber][neuronNumber])* log(1- lastLayerActivations[feedForwardNumber][neuronNumber]));
            //  the formula used is cross entropy c = y * ln(a) + (1-y) * ln(1-a)
            //        y = output[feedForwardNumber][neuronNumber]  a= lastLayerActivations[feedForwardNumber][neuronNumber]
        }
        cost *= float(-1)/lastLayerActivations.size();
        this->costs.emplace_back(cost);
    }

}
double Network::processMeanError() {

    long double mean = 0;
    for(auto cost : costs){
        mean += cost;
    }
    mean/= costs.size();
    if(mean != mean){
        std::cout << " ||la fonction cross entropy ne fonctionne pas pour ces résultat|| ";
    }
    return (double)mean;



}



const vector<float> &Network::getCost() const {
    return costs;
}
/*
void Network::vectorResizing(std::vector<std::vector<float>> vector, unsigned rows, unsigned columns) {
    vector.resize(rows);
    for ( auto &it : vector) {
        it.resize(columns);
    }
}*/


void Network::resetActivations() {
    for(Layer * layer : layers){
        layer->resetActivations();
    }
}

void Network::main() {
    for(unsigned int numberOfTheEpoch=0 ; numberOfTheEpoch<numberOfEpochs; ++numberOfTheEpoch){
        if(numberOfTheEpoch%(numberOfEpochs/10) == 0){
            std::cout <<'\n'<< " numberOfTheEpoch " << numberOfTheEpoch <<endl;
        }
        feedforward(numberOfTheEpoch);

        processCost(numberOfTheEpoch);
        std::cout << "\nEpoch : "<< numberOfTheEpoch<< " mean error "<< processMeanError();

        backPropagation(numberOfTheEpoch);

        gradientDescent(numberOfTheEpoch);

        resetActivations();
    }
}

void Network::backPropagation(const unsigned int &numberOfTheEpoch) {
    //process the partial derivative with respect to z for each layer
    //cout << "batch backpropagation"<<endl;

    layers[layers.size()-1]->processLastLayerError(output[numberOfTheEpoch]); //process the partial derivative of c with respect to z for the last layer
    //std::cout << * layers[layers.size()-1];

    for(unsigned i = layers.size()-2 ; i >= 0 && i<999999; --i){ //use the partial derivative c/z of the n+1 layer to process it for n
        //condition i<99999 car 0-1 = 42000000 dans le référentiel des unsigned

        layers[i]->processLayerError(  layers[i+1] );

    }
}

void Network::gradientDescent(unsigned int batchNumber) {

    for(unsigned layerNumber =layers.size()-1; layerNumber>0;--layerNumber  ){
        layers[layerNumber]->layerGradientDescent(layers[layerNumber - 1]->getMyactivations(), regularizationTerm);
    }
    layers[0]->layerGradientDescent(entries[batchNumber], regularizationTerm);

}








