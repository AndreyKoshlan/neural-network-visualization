#include "layer.h"

void Layer::fillWithZeros() {
    for (uint i = 0; i < count(); i++) {
        m_neurons[i] = 0;
    }
}

void Layer::activateSigmoid(const uint neuronIndex) {
    m_neurons[neuronIndex] = 1.0f / (1.0f + exp(-m_neurons[neuronIndex]));
}

void Layer::setCount(uint count) {
    if (m_count != count) {
        delete[] m_neurons;
        m_neurons = new float[count]();
        m_count = count;
    }
}

Layer::Layer(uint count) {
    setCount(count);
}

Layer::~Layer() {
    delete[] m_neurons;
}
