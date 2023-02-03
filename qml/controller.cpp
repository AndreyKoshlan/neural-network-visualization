#include "controller.h"

#include <QDebug>
#include <QThread>
#include <model/dataset/dataset.h>
#include <model/dataset/datasetreader.h>
#include <model/dataset/datasetreadermnist.h>

void Controller::nextInstance() {
    // TODO: make QThread as member
    QThread *thread = QThread::create([=]{
        if (m_instanceTable != nullptr) {
            m_neuralNetwork->setLayer(m_dataset, 0, m_datasetId++);
            if (m_datasetId >= m_dataset->count())
                m_datasetId = 0;

            m_neuralNetwork->activate();
            m_neuralNetwork->highlight();
            m_instanceTable->setInstanceBuffer(
                m_neuralNetwork->visualLayers(),
                m_neuralNetwork->visualSynapses()
            );
        }
    });
    thread->start();
}

void Controller::setInstanceTable(InstanceTable* instanceTable) {
    m_instanceTable = instanceTable;
}

void Controller::setNeuralNetworkSize(LayerSize values) {
    m_preferences.layerSize = values;
    m_neuralNetwork->setPreferences(m_preferences);
}

void Controller::setLayerScale(LayerScale values) {
    m_preferences.layerScale = values;
    m_neuralNetwork->setPreferences(m_preferences);
    m_neuralNetwork->load("./model/mnist.nnv"); //TODO: put this to constructor, rework preferences system
    m_neuralNetwork->build();
}

Controller::Controller(QObject* parent) : QObject(parent)
{
    m_instanceTable = nullptr;
    m_neuralNetwork = new NeuralNetworkVisual(this);
    m_datasetId = 0;
    m_dataset = new Dataset();
    DatasetPathMNIST path(
        "./data/train-images.idx3-ubyte", "./data/train-labels.idx1-ubyte"
    );
    DatasetReaderMNIST reader(&path);
    reader.read(m_dataset);
}
