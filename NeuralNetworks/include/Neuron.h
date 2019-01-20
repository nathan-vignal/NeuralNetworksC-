#ifndef NEURON_H
#define NEURON_H
#include <vector>
#include <ostream>
#include <random>

class Neuron
{
public:
    static unsigned short maxWeight;
    static unsigned short maxBias;

    private:


        std::vector<float> activations;
        std::vector<float> preActivation;
        std::vector<float> weights;
        std::vector<float> error;
        float bias;
    public:
        Neuron( const unsigned short & nbWeights );
        virtual ~Neuron();
        void processActivations(const std::vector<std::vector<float>>& previousLayerActivations);
        float sigmoid(float x);
        static std::vector<float> hadamardProduct(const std::vector<float> & vector1 ,const std::vector<float> & vector2 );
        float sigmoidPrime(float x);


        //accesseurs
        const std::vector<float> & getActivations() const;
        const float & getActivation(const unsigned short adress );


        void resetActivations();
        void processLastNeuronError(std::vector<float> activationBP);

    friend std::ostream &operator<<(std::ostream &os, const Neuron &neuron);
};



#endif // NEURON_H
