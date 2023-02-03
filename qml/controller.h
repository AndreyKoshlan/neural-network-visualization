#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QVector3D>
#include <QThread>
#include <QtQml/qqmlregistration.h>

#include "instancetable.h"
#include "model/visualization/neuralnetworkvisual.h"

class Controller : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(InstanceTable* instanceTable READ instanceTable WRITE setInstanceTable)
    Q_PROPERTY(LayerSize neuralNetworkSize READ neuralNetworkSize WRITE setNeuralNetworkSize)
    Q_PROPERTY(LayerScale layerScale READ layerScale WRITE setLayerScale )
public:
    explicit Controller(QObject *parent = nullptr);

    InstanceTable* instanceTable() const { return m_instanceTable; }
    void setInstanceTable(InstanceTable* instanceTable);

    LayerSize neuralNetworkSize() const { return m_preferences.layerSize; }
    void setNeuralNetworkSize(LayerSize values);

    LayerScale layerScale() const { return m_preferences.layerScale; }
    void setLayerScale(LayerScale values);

    void nextInstanceProc();
    void updateStatus(const uint datasetId);
    Q_INVOKABLE void nextInstance();
    Q_INVOKABLE QString status() const { return m_status; };
private:
    NeuralNetworkVisual* m_neuralNetwork;
    Dataset* m_dataset;
    NeuralNetworkPreferences m_preferences;
    uint m_datasetId;
    QString m_status;

    // QtQuick3D instanced rendering
    InstanceTable* m_instanceTable;
};

#endif // CONTROLLER_H
