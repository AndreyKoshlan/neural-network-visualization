#ifndef VISUALSYNAPSES_H
#define VISUALSYNAPSES_H

#include <QVector3D>
#include <QColor>

#include "visuallayer.h"

struct NeuralNetworkVisualSynapseData {
   QVector3D position;
   QVector3D rotation;
   QVector3D scale;
   QColor color;
   uint backLayer;
   uint frontLayer;
   uint backNeuronId;
   uint frontNeuronId;
   bool ignorable;
};

class VisualLayer;
class NeuralNetworkVisual;

class VisualSynapses
{
public:
    VisualSynapses(NeuralNetworkVisual* NeuralNetwork, VisualLayer& backLayer, VisualLayer& frontLayer, uint index);
    static float getSynapseLength(QVector3D neuronPos1, QVector3D neuronPos2);
    static QVector3D getSynapseRotation(QVector3D neuronPos1, QVector3D neuronPos2);
    static QVector3D getSynapseCenter(QVector3D neuronPos1, QVector3D neuronPos2);
    static QColor getSynapseColor(const uint layerIndex, const float synapseValue);

    float getSynapseValue(const uint index, const uint backNeuronId, const uint frontNeuronId);
    void highlightSynapses();
    NeuralNetworkVisualSynapseData synapse(uint index) const { return m_synapse[index]; }
    uint count() const { return m_count; }
private:
    uint m_count;
    NeuralNetworkVisual* m_neuralNetwork;
    QList<NeuralNetworkVisualSynapseData> m_synapse;
};

#endif // VISUALSYNAPSES_H
