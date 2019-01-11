#ifndef NETWORK_H
#define NETWORK_H

#include <ostream>
#include "Layer.h"

class Network
{
private:
    std::vector<float> cost;
    //essayer de passer en array pour gagner en perf
    std::vector<std::vector<std::vector<float> >> entries;
    std::vector<std::vector<float> > output;
    float tauxApprentissage = 0.15;
    unsigned short numberOfEpochs;
    std::vector<Layer *> layers;





public:
    Network(const unsigned short & nbLayers,const unsigned short & nbNeurons,const std::vector<std::vector<float> > & _entries,
            const std::vector<std::vector<float> > & _output, const unsigned short & _numberOfEpochs  );
    virtual ~Network();
    const std::vector<float> &getCost() const;
    const std::vector<Layer *> &getLayers() const;
    void main();
    void feedforward( unsigned short numberOfTheEpoch);
    void processCost();
    void resetActivations();
    void vectorResizing(std::vector<std::vector<float>> vector, unsigned rows, unsigned columns );
    void backPropagation();
    friend std::ostream& operator<< (std::ostream& stream, Network & network);
};

#endif // NETWORK_H
