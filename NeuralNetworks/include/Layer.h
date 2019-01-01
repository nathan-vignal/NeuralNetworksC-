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
        std::vector <std::vector<float>> getMyactivations();
        std::vector<float> getTheLastBatchActivation();
        void processMyNeuronsActivations(const std::vector <std::vector<float>> & previousLayerActivation);

};

#endif // LAYER_H
