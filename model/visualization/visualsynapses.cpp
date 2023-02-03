#include "visualsynapses.h"

#include <QtMath>
#include <QDebug>
#include <QRandomGenerator>

QColor VisualSynapses::getSynapseColor(const uint layerIndex, const float synapseValue) {
    float randomRemove = QRandomGenerator::global()->bounded(0.5f);
    const float threshold = qMin(1.0f, qMax(0.0f, synapseValue));
        return QColor::fromHslF(
            0.88f,
            0.0f,
            threshold*0.6f,
            threshold+(0.05*layerIndex)-randomRemove >= 0.9f ? 1 : 0
        );
}

float VisualSynapses::getSynapseValue(const uint index, const uint backNeuronId, const uint frontNeuronId) {
    return m_neuralNetwork->synapses(index)->weight(backNeuronId, frontNeuronId);
}

void VisualSynapses::highlightSynapses() {
    for (int i = 0; i < m_synapse.count(); i++) {
        NeuralNetworkVisualSynapseData* synapse = &m_synapse[i];
        float value = getSynapseValue(synapse->backLayer, synapse->backNeuronId, synapse->frontNeuronId);
        synapse->color = getSynapseColor(synapse->backLayer, value);
    }
}

float VisualSynapses::getSynapseLength(QVector3D neuronPos1, QVector3D neuronPos2) {
    return neuronPos1.distanceToPoint(neuronPos2) / 100;
}

QVector3D VisualSynapses::getSynapseRotation(QVector3D neuronPos1, QVector3D neuronPos2) {
    float rotationXZ = qAtan2(
        neuronPos1.z() - neuronPos2.z(),
        neuronPos1.x() - neuronPos2.x()
    ) * 180 / M_PI;
    float lengthXZ = sqrt(qPow(neuronPos1.z() - neuronPos2.z(), 2) + qPow(neuronPos1.x() - neuronPos2.x(), 2));
    float rotationY  = qAtan2(
        lengthXZ,
        neuronPos1.y() - neuronPos2.y()
    ) * 180 / M_PI;
    return QVector3D(0, -rotationXZ, -rotationY-90);
}

QVector3D VisualSynapses::getSynapseCenter(QVector3D neuronPos1, QVector3D neuronPos2) {
    return (neuronPos1 + neuronPos2) / 2;
}

VisualSynapses::VisualSynapses(NeuralNetworkVisual* NeuralNetwork, VisualLayer& backLayer, VisualLayer& frontLayer, uint index)
{
    m_neuralNetwork = NeuralNetwork;
    m_count = backLayer.count()*frontLayer.count();
    for (uint backId = 0; backId < backLayer.count(); backId++) {
        auto backNeuron = backLayer.neuron(backId);
        for (uint frontId = 0; frontId < frontLayer.count(); frontId++) {
            auto frontNeuron = frontLayer.neuron(frontId);
            float length = getSynapseLength(backNeuron.position, frontNeuron.position);
            NeuralNetworkVisualSynapseData data;
            data.position = getSynapseCenter(backNeuron.position, frontNeuron.position);
            data.scale = QVector3D(length, 0.008, 0.008);
            data.rotation = getSynapseRotation(backNeuron.position, frontNeuron.position);
            if ((frontId == 4) && backId == 0)
                qDebug() << data.rotation << frontNeuron.layerIndex;
            data.backLayer = index;
            data.frontLayer = index+1;
            data.backNeuronId = backId;
            data.frontNeuronId = frontId;
            m_synapse.push_back(data);
        }
    }
    highlightSynapses();
}
