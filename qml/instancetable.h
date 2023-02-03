#ifndef INSTANCETABLE_H
#define INSTANCETABLE_H

#include <QtQuick3D/qquick3dinstancing.h>
#include <QObject>

#include "model/visualization/visuallayer.h"

class InstanceTable : public QQuick3DInstancing
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit InstanceTable(QQuick3DObject *parent = nullptr);
    ~InstanceTable() override;
    void setInstanceBuffer(QList<VisualLayer*> visualLayers, QList<VisualSynapses*> visualSynapses);
protected:
    QByteArray getInstanceBuffer(int *instanceCount) override;
    QByteArray m_instanceData;
    int m_instanceCount;
};

#endif // INSTANCETABLE_H
