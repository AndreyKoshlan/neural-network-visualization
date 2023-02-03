#include "neuralnetworkvisual.h"

QVector3D NeuralNetworkVisual::getLayerScale(const uint index) {
    if (index < m_preferences.layerScale.count()) {
        return m_preferences.layerScale[index];
    }
    // default scale
    return QVector3D(100, 100, 100);
}

void NeuralNetworkVisual::destroy() {
    for (auto visualLayer: m_visualLayers) {
        delete visualLayer;
    }
    for (auto visualSynapses: m_visualSynapses) {
        delete visualSynapses;
    }
    m_visualLayers.clear();
    m_visualSynapses.clear();
}

void NeuralNetworkVisual::build() {
    // Build neural network layout parameters,
    // e.g., VisualLayer & VisualSynapses
    destroy();
    for (uint i = 0; i < layerCount(); i++) {
        QVector3D layerScale = getLayerScale(i);
        QSize layerSize;
        // Get the number of neuron rows and columns
        if (i < m_preferences.layerSize.count()) {
            layerSize = m_preferences.layerSize[i];
        } else {
            // In cases where an integer square number cannot be obtained,
            // the remainder of the neurons are not shown
            uint layerSquareSize = (uint)sqrt(layer(i)->count());
            layerSize = QSize(layerSquareSize, layerSquareSize);
        }
        VisualLayer* visualLayer = new VisualLayer(this, i, layerSize.width(),
            layerSize.height(), layerScale, layerCount());
        m_visualLayers.push_back(visualLayer);
        if (i > 0) {
            VisualSynapses* visualSynapses =
                    new VisualSynapses(this, *m_visualLayers[i-1], *m_visualLayers[i], i-1);
            m_visualSynapses.push_back(visualSynapses);
        }
    }
}

void NeuralNetworkVisual::highlight() {
    for (VisualLayer* visualLayer: m_visualLayers) {
        visualLayer->highlightNeurons();
    }
}

void NeuralNetworkVisual::setPreferences(NeuralNetworkPreferences preferences) {
    clear();
    for (uint i = 0; i < preferences.layerSize.count(); i++) {
        auto layerSize = preferences.layerSize[i];
        addLayer(layerSize.width()*layerSize.height());
    }
    m_preferences = preferences;
    build();
}

NeuralNetworkVisual::NeuralNetworkVisual(QObject *parent): NeuralNetwork(parent)
{

}
