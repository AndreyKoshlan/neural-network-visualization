#include <QRandomGenerator>
#include <QDebug>

#include "synapses.h"

void Synapses::fillWithRandom() {
    for (uint i = 0; i < count(); i++) {
        m_weights[i] = QRandomGenerator::global()->bounded(-1000, 1001)/1000.0f;
    }
}

void Synapses::resize() {
    if (m_backLayer == nullptr)
        return;
    if (m_frontLayer == nullptr)
        return;
    delete m_weights;
    m_backLayerNeuronCount = m_backLayer->count();
    m_frontLayerNeuronCount = m_frontLayer->count();
    m_weights = new float[m_backLayerNeuronCount * m_frontLayerNeuronCount];
}

void Synapses::setLayers(Layer* backLayer, Layer* frontLayer) {
    m_backLayer = backLayer;
    m_frontLayer = frontLayer;
    resize();
}

float Synapses::weight(uint backLayerIndex, uint frontLayerIndex) {
    return m_weights[frontLayerIndex + m_frontLayerNeuronCount * backLayerIndex];
}

float Synapses::weight(uint index) {
    return m_weights[index];
}

void Synapses::setWeight(uint backLayerIndex, uint frontLayerIndex, float value) {
    m_weights[frontLayerIndex + m_frontLayerNeuronCount * backLayerIndex] = value;
}

void Synapses::setWeight(uint index, float value) {
    m_weights[index] = value;
}

Synapses::Synapses(Layer* backLayer, Layer* frontLayer) {
    setLayers(backLayer, frontLayer);
    fillWithRandom();
}

Synapses::~Synapses() {
    delete m_weights;
}
