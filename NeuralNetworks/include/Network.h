#ifndef NETWORK_H
#define NETWORK_H

#include <ostream>
#include "Layer.h"

class Network
{
    private:
    std::vector<std::vector<int> > cost;    //essayer de passer en array pour gagner en perf
    std::vector<std::vector<int> > entries;
    std::vector<std::vector<int> > output;
    std::vector<Layer> layers;


    public:
        Network(const unsigned short & nbLayers,const unsigned short & nbNeurons,const std::vector<std::vector<int> > & _entries,
                const std::vector<std::vector<int> > & _output  );
        virtual ~Network();

        void feedforward();
        void processCost();
        friend std::ostream& operator<< (std::ostream& stream, Network & network);
};

#endif // NETWORK_H
