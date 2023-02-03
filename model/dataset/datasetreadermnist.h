#ifndef DATASETREADERMNIST_H
#define DATASETREADERMNIST_H

#include <QByteArray>
#include <QList>

#include "datasetreader.h"
#include "dataset.h"

struct DatasetItemMNIST: public DatasetItem {
    DatasetItemMNIST(float* input, float* output,
        uint inputCount, uint outputCount, int rows = -1, int cols = -1);
    int rows;
    int cols;
};

struct DatasetPathMNIST: public DatasetPath {
    DatasetPathMNIST(QString imagePath, QString labelPath);
    QString imagePath;
    QString labelPath;
};

enum FileTypeMNIST {
    LabelFile = 0x0801,
    ImageFile = 0x0803
};

struct MetadataMNIST {
    int imageCount;
    int imageRows;
    int imageColumns;
    int labelCount;
};

class DatasetReaderMNIST : public DatasetReader
{
public:
    bool read(Dataset* dataset);

    DatasetReaderMNIST(DatasetPathMNIST* path);
private:
    bool identifyFilesMNIST(QFile* imageFile, QFile* labelFile);
    bool readMetadata(QFile* imageFile, QFile* labelFile, MetadataMNIST& metadata);
    bool readImages(QFile* imageFile, QList<float*>* buffer, MetadataMNIST metadata);
    bool readLabels(QFile* labelFile, QList<float*>* buffer, MetadataMNIST metadata);
};

#endif // DATASETREADERMNIST_H
