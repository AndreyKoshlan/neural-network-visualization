#ifndef VISUALLAYER_H
#define VISUALLAYER_H

#include "neuralnetworkvisual.h"

#include <QVector3D>
#include <QColor>

struct NeuralNetworkVisualNeuronData {
   QVector3D position;
   QVector3D scale;
   QColor color;
   uint x;
   uint y;
   uint layerIndex;
};

class NeuralNetworkVisual;

class VisualLayer {
public:
    VisualLayer(NeuralNetworkVisual* NeuralNetwork, const uint index, const uint width,
        const uint height, const QVector3D layerScale, const uint layerCount);

    void highlightNeurons();

    static float getCubeSize(const uint width, const uint height,
        const QVector3D layerScale, const uint layerCount);
    static QVector3D getCubePosition(const uint x, const uint y, const uint index,
        const float cubeSize, const uint width, const uint height, const uint layerCount);
    static QColor getCubeColor(const float neuronValue);
    float getNeuronValue(const uint layerIndex, const uint x, const uint y);

    NeuralNetworkVisualNeuronData neuron(uint index) const { return m_neurons[index]; }
    uint count() const { return m_count; }
private:
    uint m_count;
    uint m_width;
    uint m_height;
    NeuralNetworkVisual* m_neuralNetwork;
    QList<NeuralNetworkVisualNeuronData> m_neurons;
};

#endif // VISUALLAYER_H
