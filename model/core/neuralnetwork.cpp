#include "neuralnetwork.h"

#include <QDebug>
#include <QFile>

void NeuralNetwork::tensorProduct(Layer* backLayer, Layer* frontLayer, Synapses* synapses) {
    frontLayer->fillWithZeros();
    for (uint frontId = 0; frontId < frontLayer->count(); frontId++) {
        for (uint backId = 0; backId < backLayer->count(); backId++) {
            float frontNeuron = frontLayer->neuron(frontId);
            float backNeuron = backLayer->neuron(backId);
            frontLayer->setNeuron(
                frontId,
                frontNeuron + backNeuron * synapses->weight(backId, frontId)
            );
        }
        frontLayer->activateSigmoid(frontId);
    }
}

void NeuralNetwork::trainWeights(Layer* backLayer, Layer* frontLayer,
    Layer* frontErrorLayer, Synapses* synapses)
{
    for (uint frontId = 0; frontId < frontLayer->count(); frontId++) {
        float gradientError = frontErrorLayer->neuron(frontId);
        float frontNeuronValue = frontLayer->neuron(frontId);
        // Derivative  Sigmoid
        gradientError *= frontNeuronValue*(1-frontNeuronValue);
        gradientError *= 0.01f; //Learning rate
        for (uint backId = 0; backId < backLayer->count(); backId++) {
            float weight = synapses->weight(backId, frontId);
            synapses->setWeight(
                backId,
                frontId,
                weight + gradientError*backLayer->neuron(backId)
            );
        }
    }
}

void NeuralNetwork::tensorErrorProduct(Layer* backErrorLayer,
    Layer* frontErrorLayer, Synapses* synapses)
{
    backErrorLayer->fillWithZeros();
    for (uint backId = 0; backId < backErrorLayer->count(); backId++) {
        for (uint frontId = 0; frontId < frontErrorLayer->count(); frontId++) {
            float frontError = frontErrorLayer->neuron(frontId);
            float backError = backErrorLayer->neuron(backId);
            backErrorLayer->setNeuron(
                backId,
                backError + frontError * synapses->weight(backId, frontId)
            );
        }
    }
}

void NeuralNetwork::backpropagation(float* expected) {
    // Calculating actual - expected (error)
    float MSE = 0;
    Layer* lastErrorLayer = m_errors.last();
    Layer* lastLayer = m_layers.last();
    for (uint i = 0; i < lastErrorLayer->count(); i++) {
        float error = expected[i]-lastLayer->neuron(i);
        lastErrorLayer->setNeuron(i, error);
        MSE += error * error;
    }
    MSE /= float(lastErrorLayer->count());
    qInfo() << "[Training] loss:" << MSE;

    // Error propagation
    for (int i = m_synapses.count(); i > 0; i--) {
        tensorErrorProduct(m_errors[i-1], m_errors[i], m_synapses[i-1]);
    }

    // Changing weights
    for (int i = 0; i < m_synapses.count(); i++) {
        trainWeights(m_layers[i], m_layers[i+1],
            m_errors[i+1], m_synapses[i]
        );
    }
}

void NeuralNetwork::activate() {
    for (int i = 0; i < m_synapses.count(); i++) {
        tensorProduct(m_layers[i], m_layers[i+1], m_synapses[i]);
    }
    emit activated();
}

void NeuralNetwork::fit(Dataset* dataset, uint epochCount) {
    // Creating error-layers
    for (int i = 0; i < m_errors.count(); i++) {
        delete m_errors[i];
    }
    for (int i = 0; i < m_layers.count(); i++) {
        Layer* errorLayer = new Layer(m_layers[i]->count());
        m_errors.push_back(errorLayer);
    }

    // Train
    for (uint epoch = 0; epoch < epochCount; epoch++) {
        qInfo() << "[Training] epoch:" << epoch+1 << "/" << epochCount;
        for (int datasetId = 0; datasetId < dataset->count(); datasetId++) {
            setLayer(dataset, 0, datasetId);
            activate();
            backpropagation(dataset->get(datasetId)->output);
        }
    }
}

void NeuralNetwork::save(QString fileName) {
    QFile nnFile(fileName);
    if (!nnFile.open(QIODevice::WriteOnly))
        return;
    nnFile.resize(0);
    QDataStream stream(&nnFile);
    stream << (qint32)m_layers.count();
    for (uint i = 0; i < m_layers.count(); i++) {
        stream << (qint32)m_layers[i]->count();
    }
    for (uint i = 0; i < m_synapses.count(); i++) {
        for (uint k = 0; k < m_synapses[i]->count(); k++) {
            stream << m_synapses[i]->weight(k);
        }
    }
    nnFile.close();
}

void NeuralNetwork::load(QString fileName) {
    clear();
    QFile nnFile(fileName);
    if (!nnFile.open(QIODevice::ReadOnly))
        return;
    QDataStream stream(&nnFile);
    uint layerCount;
    stream >> layerCount;
    for (uint i = 0; i < layerCount; i++) {
        uint neuronCount;
        stream >> neuronCount;
        addLayer(neuronCount);
    }
    for (uint i = 0; i < m_synapses.count(); i++) {
        for (uint k = 0; k < m_synapses[i]->count(); k++) {
            float weight;
            stream >> weight;
            m_synapses[i]->setWeight(k, weight);
        }
    }
    nnFile.close();
}

void NeuralNetwork::clear() {
    for (Layer* layer: m_layers)
        delete layer;
    for (Synapses* synapses: m_synapses)
        delete synapses;
    m_layers.clear();
    m_synapses.clear();
}

void NeuralNetwork::setLayer(Dataset* dataset, uint layerIndex, uint datasetIndex) {
    if (datasetIndex >= dataset->count())
        return;
    if (layerIndex >= m_layers.count())
        return;
    Layer* layer = m_layers[layerIndex];
    const DatasetItem* item = dataset->get(datasetIndex);
    if (item->inputCount != layer->count())
        return;
    for (uint i = 0; i < layer->count(); i++) {
        layer->setNeuron(i, item->input[item->inputCount-i-1]);
    }
}

void NeuralNetwork::addLayer(uint count) {
    Layer* newLayer = new Layer(count);
    m_layers.push_back(newLayer);
    if (m_layers.count() >= 2) {
        Layer* backLayer = m_layers[m_layers.count()-2];
        Synapses* newSynapses = new Synapses(backLayer, newLayer);
        m_synapses.push_back(newSynapses);
    }
}


NeuralNetwork::NeuralNetwork(QObject *parent) : QObject(parent)
{

}
