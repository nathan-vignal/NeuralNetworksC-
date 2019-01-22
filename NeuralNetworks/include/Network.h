#ifndef NETWORK_H
#define NETWORK_H

#include <ostream>
#include "Layer.h"

class Network
{

private:
    std::vector<float> cost;
    std::vector<std::vector<std::vector<float> >> entries;
    std::vector<std::vector<std::vector<float> >> output;
    unsigned short numberOfEpochs;
    std::vector<Layer *> layers;





public:
    const static float learningRate ;
    Network(const unsigned short & nbLayers,const unsigned short & nbNeurons,const std::vector<std::vector<float> > & _entries,
            const std::vector<std::vector<float> > & _output, const unsigned short & _numberOfEpochs  );
    virtual ~Network();
    const std::vector<float> &getCost() const;
    const std::vector<Layer *> &getLayers() const;
    void main();
    void feedforward( unsigned short numberOfTheEpoch);
    std::vector<std::vector<float>> testFeedforward(const std::vector<float> &entries);
    void processCost();
    void resetActivations();
    void vectorResizing(std::vector<std::vector<float>> vector, unsigned rows, unsigned columns );
    void backPropagation(unsigned short numberOfTheEpoch);
    void gradientDescent(unsigned short batchNumber);
    friend std::ostream& operator<< (std::ostream& stream, Network & network);
};

#endif // NETWORK_H
