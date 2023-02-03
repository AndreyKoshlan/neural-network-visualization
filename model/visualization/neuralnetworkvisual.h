#ifndef NEURALNETWORKVISUAL_H
#define NEURALNETWORKVISUAL_H

#include "model/core/neuralnetwork.h"
#include "visuallayer.h"
#include "visualsynapses.h"

#include <QVector3D>
#include <QColor>
#include <QObject>

typedef QList<QSize> LayerSize;
typedef QList<QVector3D> LayerScale;

struct NeuralNetworkPreferences {
    LayerSize layerSize;
    LayerScale layerScale;
};

class VisualLayer;
class VisualSynapses;

class NeuralNetworkVisual : public NeuralNetwork
{
    Q_OBJECT
public:
    explicit NeuralNetworkVisual(QObject *parent = nullptr);

    void build();
    void destroy();
    void highlight();

    QVector3D getLayerScale(const uint index);

    NeuralNetworkPreferences preferences() const { return m_preferences; }
    void setPreferences(NeuralNetworkPreferences preferences);

    QList<VisualLayer*> visualLayers() const { return m_visualLayers; }
    QList<VisualSynapses*> visualSynapses() const { return m_visualSynapses; }
private:
    NeuralNetworkPreferences m_preferences;
    QList<VisualLayer*> m_visualLayers;
    QList<VisualSynapses*> m_visualSynapses;
};

#endif // NEURALNETWORKVISUAL_H
