#include "visuallayer.h"

#include <QDebug>

float VisualLayer::getCubeSize(const uint width, const uint height,
    const QVector3D layerScale, const uint layerCount)
{
    float sizeX = layerScale.x() / width;
    float sizeY = layerScale.y() / height;
    float sizeZ = layerScale.z() / layerCount;
    return qMin(qMin(sizeX, sizeY), sizeZ) / 2;
}

QVector3D VisualLayer::getCubePosition(const uint x, const uint y, const uint index,
    const float cubeSize, const uint width, const uint height, const uint layerCount)
{
    const float distanceNeuronFactor = 200.0f;
    const float distanceLayerFactor = 125.0f;
    QVector3D normalizedSizes = {
        cubeSize * distanceNeuronFactor,
        cubeSize * distanceNeuronFactor,
        distanceLayerFactor
    };
    QVector3D cubePos = {
        (x * normalizedSizes.x()),
        (y * normalizedSizes.y()),
        index * normalizedSizes.z()
    };
    QVector3D cubeCenterPos = {
        cubePos.x() - ((width-1) * normalizedSizes.x() / 2),
        cubePos.y() - ((height-1) * normalizedSizes.y() / 2),
        cubePos.z() - ((layerCount-1) * normalizedSizes.z() / 2)
    };
    return cubeCenterPos;
}

float VisualLayer::getNeuronValue(const uint layerIndex, const uint x, const uint y) {
    return m_neuralNetwork->layer(layerIndex)->neuron(y * m_width + x);
}

QColor VisualLayer::getCubeColor(const float neuronValue) {
    const float threshold = qMin(1.0f, qMax(0.25f, neuronValue));
        return QColor::fromHslF(
            0.88f,
            0.0f,
            threshold
        );
}

void VisualLayer::highlightNeurons() {
    for (int i = 0; i < m_neurons.count(); i++) {
        NeuralNetworkVisualNeuronData* neuron = &m_neurons[i];
        float value = getNeuronValue(neuron->layerIndex, neuron->x, neuron->y);
        neuron->color = getCubeColor(value);
    }
}

VisualLayer::VisualLayer(NeuralNetworkVisual* NeuralNetwork, const uint index, const uint width,
    const uint height, const QVector3D layerScale, const uint layerCount)
{
    m_neuralNetwork = NeuralNetwork;
    //TODO: make it more beautiful

    // set layer size
    m_count = width*height;
    m_width = width;
    m_height = height;

    // get visual cube size & scale
    float cubeSize = getCubeSize(width, height, layerScale, layerCount);
    QVector3D cubeScale = { cubeSize, cubeSize, cubeSize };

    for (uint x = 0; x < width; x++) {
        for (uint y = 0; y < height; y++) {
            QVector3D cubeCenterPos = getCubePosition(x, y, index, cubeSize, width, height, layerCount);
            NeuralNetworkVisualNeuronData data;
            data.position = cubeCenterPos;
            data.scale = cubeScale;
            data.color = QColorConstants::White;
            data.x = x;
            data.y = y;
            data.layerIndex = index;
            m_neurons.push_back(data);
        }
    }
}

