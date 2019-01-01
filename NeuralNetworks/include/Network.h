#ifndef NETWORK_H
#define NETWORK_H

#include <ostream>
#include "Layer.h"

class Network
{
    private:
    std::vector<std::vector<float> > cost;    //essayer de passer en array pour gagner en perf
    std::vector<std::vector<float> > entries;
    std::vector<std::vector<float> > output;
    std::vector<Layer *> layers;
public:
    const std::vector<Layer *> &getLayers() const;


public:
        Network(const unsigned short & nbLayers,const unsigned short & nbNeurons,const std::vector<std::vector<float> > & _entries,
                const std::vector<std::vector<float> > & _output  );
        virtual ~Network();

        void feedforward();
        void processCost();
        friend std::ostream& operator<< (std::ostream& stream, Network & network);
};

#endif // NETWORK_H
