#ifndef LAYER_H
#define LAYER_H
#include "Neuron.h"
#include <vector>


class Layer
{

private:
    std::vector<Neuron *> neurons;
public:

    Layer(const unsigned short & nbNeurons,const unsigned short & nbNeuronsInPreviousLayer);
    virtual ~Layer();
    unsigned short getNumberOfNeurons();
    std::vector <std::vector<float>>  getMyactivations();
    void processMyNeuronsActivations(const std::vector <std::vector<float>> & previousLayerActivations);
    void resetActivations();
    void processLastLayerError(std::vector<std::vector<float>> output);
    std::vector<std::vector<float>> getNeuronErrors(){
        std::vector<std::vector<float>> neuronsError;
        for(auto neuron : neurons){
            neuronsError.emplace_back(neuron->getError());
        }
    }
    void processLayerError();
    void layerGradientDescent(Layer *nextLayer);

    friend std::ostream& operator<< (std::ostream& stream, Layer & layer);

};

#endif // LAYER_H
