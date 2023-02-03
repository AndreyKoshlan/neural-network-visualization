#include "instancetable.h"

#include <QDebug>

void InstanceTable::setInstanceBuffer(QList<VisualLayer*> visualLayers, QList<VisualSynapses*> visualSynapses) {
    m_instanceData.clear();
    m_instanceCount = 0;
    for (VisualLayer* visualLayer: visualLayers) {
        for (uint neuronIndex = 0; neuronIndex < visualLayer->count(); neuronIndex++) {
            auto neuronData = visualLayer->neuron(neuronIndex);
            QVector3D position = neuronData.position;
            QVector3D scale = neuronData.scale;
            QColor color = neuronData.color;
            auto entry = calculateTableEntry(position, scale, QVector3D(0, 0, 0), color);
            m_instanceData.append(reinterpret_cast<const char *>(&entry), sizeof(entry));
            m_instanceCount++;
        }
    }
    for (VisualSynapses* visualSynapse: visualSynapses) {
        for (uint synapseIndex = 0; synapseIndex < visualSynapse->count(); synapseIndex++) {
            auto synapseData = visualSynapse->synapse(synapseIndex);
            if (synapseData.color.alpha() < 254)
                continue;
            QVector3D position = synapseData.position;
            QVector3D scale = synapseData.scale;
            QVector3D rotation = synapseData.rotation;
            QColor color = synapseData.color;
            auto entry = calculateTableEntry(position, scale, rotation, color);
            m_instanceData.append(reinterpret_cast<const char *>(&entry), sizeof(entry));
            m_instanceCount++;
        }
    }
    markDirty();
}

QByteArray InstanceTable::getInstanceBuffer(int *instanceCount) {
    *instanceCount = m_instanceCount;
    return m_instanceData;
}

InstanceTable::InstanceTable(QQuick3DObject *parent): QQuick3DInstancing(parent)  {
    m_instanceCount = 0;
    m_instanceData = nullptr;
}

InstanceTable::~InstanceTable() {
}
