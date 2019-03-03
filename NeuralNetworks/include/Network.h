#ifndef NETWORK_H
#define NETWORK_H

#include <ostream>
#include "Layer.h"

class Network
{

private:
    double regularizationTerm;
    std::vector<float> costs;
    std::vector<std::vector<std::vector<float> >> entries;
    std::vector<std::vector<std::vector<float> >> output;
    unsigned int numberOfEpochs;
    std::vector<Layer *> layers;





public:
    const static float learningRate ;
    Network(const std::vector<unsigned short> &hiddenLayers, const std::vector<std::vector<float> > &_entries,
            const std::vector<std::vector<float> > &_output, const unsigned int &_numberOfEpochs,
            const double &_regularizationTerm);

    virtual ~Network();
    const std::vector<float> &getCost() const;
    const std::vector<Layer *> &getLayers() const;
    void main();
    void feedforward(const unsigned int &numberOfTheEpoch);
    std::vector<std::vector<float>> testFeedforward(const std::vector<std::vector<float>> &entries);
    void processCost(const unsigned int &batchNumber);
    double processMeanError();
    void resetActivations();

    void vectorResizing(std::vector<std::vector<float>> vector, unsigned rows, unsigned columns );
    void backPropagation(const unsigned int &numberOfTheEpoch);
    void gradientDescent(unsigned int batchNumber);

    //void vectorResizing(std::vector<std::vector<float>> vector, unsigned rows, unsigned columns );
    void backPropagation(const unsigned short &numberOfTheEpoch);
    void gradientDescent(unsigned short batchNumber);

    friend std::ostream& operator<< (std::ostream& stream, Network & network);
};

#endif // NETWORK_H
