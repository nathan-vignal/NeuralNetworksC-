#ifndef NEURON_H
#define NEURON_H
#include <vector>
#include <ostream>
#include <random>

class Neuron
{
public:
    static unsigned short maxWeight;
    static unsigned short minWeight;
    static std::random_device rd;  //Will be used to obtain a seed for the random number engine
    static std::mt19937 gen;
    static std::uniform_real_distribution<> dis;

    private:


        std::vector <std::vector<float>> activations;
        std::vector<float> weights;
        float bias;
    public:
        Neuron(const unsigned short & nbNeurons);
        virtual ~Neuron();
        void processActivation();
        void sigmoid();



        //accesseurs
        const std::vector<std::vector<float>> & getActivations() const;

    friend std::ostream &operator<<(std::ostream &os, const Neuron &neuron);
};



#endif // NEURON_H
