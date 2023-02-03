#ifndef SYNAPSES_H
#define SYNAPSES_H

#include <QObject>

#include "layer.h"

class Synapses {
public:
    Synapses(Layer* backLayer, Layer* frontLayer);
    ~Synapses();
    float weight(uint backLayerIndex, uint frontLayerIndex);
    float weight(uint index);
    void setWeight(uint backLayerIndex, uint frontLayerIndex, float value);
    void setWeight(uint index, float value);
    void setLayers(Layer* backLayer, Layer* frontLayer);
    void fillWithRandom();
    uint count() const { return m_backLayerNeuronCount * m_frontLayerNeuronCount; }
protected:
    void resize();
private:
    float* m_weights = nullptr;
    Layer* m_backLayer = nullptr;
    Layer* m_frontLayer = nullptr;
    uint m_backLayerNeuronCount = 0;
    uint m_frontLayerNeuronCount = 0;
};

typedef QList<Synapses*> SynapseGroup;

#endif // SYNAPSES_H
