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
        std::vector<float> weights;
        float bias;
    public:
        Neuron(const unsigned short & nbNeurons);
        virtual ~Neuron();
        void processActivation(const std::vector<float>& previousLayerActivations);
        float sigmoid(float x);
        static std::vector<float> hadamardProduct(const std::vector<float> & vector1 ,const std::vector<float> & vector2 );



        //accesseurs
        const std::vector<float> & getActivations() const;
        const float & getLastActivations() const;

    friend std::ostream &operator<<(std::ostream &os, const Neuron &neuron);
};



#endif // NEURON_H
