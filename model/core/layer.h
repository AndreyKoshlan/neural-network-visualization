#ifndef LAYER_H
#define LAYER_H

#include <QObject>

class Layer
{
public:
    Layer(uint count);
    ~Layer();

    float neuron(const uint index) { return m_neurons[index]; }
    void setNeuron(const uint index, const float value) { m_neurons[index] = value; }
    void activateSigmoid(const uint neuronIndex);

    void setCount(uint count);
    uint count() const { return m_count; }

    void fillWithZeros();
private:
    float* m_neurons = nullptr;
    uint m_count = 0;
};

typedef QList<Layer*> Layers;

#endif // LAYER_H
