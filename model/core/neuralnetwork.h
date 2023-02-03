#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <QObject>
#include <QList>

#include "layer.h"
#include "synapses.h"
#include "model/dataset/dataset.h"

class NeuralNetwork: public QObject {
    Q_OBJECT
public:
    explicit NeuralNetwork(QObject *parent = nullptr);
    void addLayer(uint count);
    void setLayer(Dataset* dataset, uint layerIndex, uint datasetIndex);
    void activate();
    void fit(Dataset* dataset, uint epochCount);
    void save(QString fileName);
    void load(QString fileName);
    void clear();

    uint layerCount() const { return m_layers.size(); };
    uint synapsesGroupCount() const { return m_synapses.size(); };
    Layer* layer(uint index) const { return m_layers[index]; }
    Synapses* synapses(uint index) const { return m_synapses[index]; }
signals:
    void activated();
private:
    void tensorErrorProduct(Layer* backErrorLayer, Layer* frontErrorLayer, Synapses* synapses);
    void trainWeights(Layer* backLayer, Layer* frontLayer, Layer* frontErrorLayer, Synapses* synapses);
    void backpropagation(float* expected);
    void tensorProduct(Layer* backLayer, Layer* frontLayer, Synapses* synapses);
    Layers m_layers;
    Layers m_errors;
    SynapseGroup m_synapses;
};

#endif // NEURALNETWORK_H
