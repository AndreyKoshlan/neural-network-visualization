#include "datasetreadermnist.h"

#include <QDebug>

DatasetItemMNIST::DatasetItemMNIST(float* input, float* output,
    uint inputCount, uint outputCount, int rows, int cols)
    : DatasetItem(input, output, inputCount, outputCount)
{
    this->rows = rows;
    this->cols = cols;
}

DatasetPathMNIST::DatasetPathMNIST(QString imagePath, QString labelPath)
    : DatasetPath()
{
    this->imagePath = imagePath;
    this->labelPath= labelPath;
}

bool DatasetReaderMNIST::readImages(QFile* imageFile,
    QList<float*>* buffer, MetadataMNIST metadata)
{
    imageFile->seek(0);
    QDataStream imageDataStream(imageFile);
    if (imageDataStream.skipRawData(12) < 0)
        return false;
    buffer->resize(metadata.imageCount);
    int pixelCount = metadata.imageColumns * metadata.imageRows;
    for (int imageIndex = 0; imageIndex < metadata.imageCount; imageIndex++) {
        (*buffer)[imageIndex] = new float[pixelCount];
        for (int pixel = 0; pixel < pixelCount; pixel++) {
            if (imageDataStream.atEnd())
                return false;
            unsigned char color;
            imageDataStream >> color;
            (*buffer)[imageIndex][pixel] = color/255.0f;
        }
    }
    return true;
}

bool DatasetReaderMNIST::readLabels(QFile* labelFile,
    QList<float*>* buffer, MetadataMNIST metadata)
{
    labelFile->seek(0);
    QDataStream labelDataStream(labelFile);
    if (labelDataStream.skipRawData(8) < 0)
        return false;
    buffer->resize(metadata.labelCount);
    for (int labelIndex = 0; labelIndex < metadata.labelCount; labelIndex++) {
        if (labelDataStream.atEnd())
            return false;
        (*buffer)[labelIndex] = new float[10]();
        unsigned char label;
        labelDataStream >> label;
        if (label >= 10)
            return false;
        (*buffer)[labelIndex][label] = 1.0f;
    }
    return true;
}

bool DatasetReaderMNIST::readMetadata(QFile* imageFile,
    QFile* labelFile, MetadataMNIST& metadata)
{
    // Read image metadata
    imageFile->seek(0);
    QDataStream imageDataStream(imageFile);
    if (imageDataStream.skipRawData(4) < 0)
        return false;
    imageDataStream >> metadata.imageCount >> metadata.imageRows >> metadata.imageColumns;

    // Read label metadata
    labelFile->seek(0);
    QDataStream labelDataStream(labelFile);
    if (labelDataStream.skipRawData(4) < 0)
        return false;
    labelDataStream >> metadata.labelCount;
    return true;
}

bool DatasetReaderMNIST::identifyFilesMNIST(QFile* imageFile, QFile* labelFile) {
    return (
        identifyFile(imageFile, 0, FileTypeMNIST::ImageFile) &&
        identifyFile(labelFile, 0, FileTypeMNIST::LabelFile)
    );
}

bool DatasetReaderMNIST::read(Dataset* dataset) {
    dataset->clear();
    auto datasetPath = dynamic_cast<const DatasetPathMNIST*>(path());
    if (datasetPath == nullptr)
        return false;

    QFile imageFile(datasetPath->imagePath);
    QFile labelFile(datasetPath->labelPath);

    if (!imageFile.open(QIODevice::ReadOnly))
        return false;
    if (!labelFile.open(QIODevice::ReadOnly))
        return false;

    if (!identifyFilesMNIST(&imageFile, &labelFile))
        return false;
    MetadataMNIST metadata;
    if (!readMetadata(&imageFile, &labelFile, metadata))
        return false;
    if (metadata.labelCount != metadata.imageCount)
        return false;

    // TODO: cleanup floats, when return false
    QList<float*> input;
    QList<float*> output;
    if (!readImages(&imageFile, &input, metadata))
        return false;
    if (!readLabels(&labelFile, &output, metadata))
        return false;

    //TODO: check if input/output is smaller then imageCount
    //TODO: replace inputCount/outputCount to list
    for (int i = 0; i < metadata.imageCount; i++) {
        dataset->add(new DatasetItemMNIST(
            input[i],
            output[i],
            metadata.imageRows*metadata.imageColumns,
            10,
            metadata.imageRows,
            metadata.imageColumns
        ));
    }
    return true;
}

DatasetReaderMNIST::DatasetReaderMNIST(DatasetPathMNIST* path)
    : DatasetReader(path)
{

}
