#ifndef NETWORK_H
#define NETWORK_H

#include <ostream>
#include "Layer.h"

class Network
{
    private:
    std::vector<float> cost;
public:
    const std::vector<float> &getCost() const;

private:
    //essayer de passer en array pour gagner en perf
    std::vector<std::vector<float> > entries;
    std::vector<std::vector<float> > output;
    float tauxApprentissage = 0.15;
    std::vector<Layer *> layers;
public:
    const std::vector<Layer *> &getLayers() const;


public:
        Network(const unsigned short & nbLayers,const unsigned short & nbNeurons,const std::vector<std::vector<float> > & _entries,
                const std::vector<std::vector<float> > & _output  );
        virtual ~Network();

        void feedforward();
        void processCost();
        void vectorResizing(std::vector<std::vector<float>> vector, unsigned rows, unsigned columns );

        friend std::ostream& operator<< (std::ostream& stream, Network & network);
};

#endif // NETWORK_H
