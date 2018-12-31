#ifndef LAYER_H
#define LAYER_H
#include "Neuron.h"
#include <vector>


class Layer
{

    private:
        std::vector<Neuron *> neurons;

    public:
        Layer(const unsigned short & nbNeurons);
        virtual ~Layer();
        std::vector<std::vector <std::vector<int>>> getMyactivations();
        std::vector <std::vector<int>> getTheLastBatchActivation();
        void processMyNeuronsActivations(std::vector <std::vector<int>> * previousLayerActivation);

};

#endif // LAYER_H
