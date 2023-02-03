#include "datasetreader.h"

#include <QDebug>
#include <QDataStream>
#include <QIODevice>

bool DatasetReader::identifyFile(QFile* file, int pos, const QByteArray magicBytes) {
    if (file->seek(pos)) {
        QByteArray buffer = file->read(magicBytes.count());
        return buffer == magicBytes;
    }
    return false;
}

bool DatasetReader::identifyFile(QFile* file, int pos, const int magicBytes) {
    QByteArray buffer;
    QDataStream dataStream(&buffer, QIODevice::WriteOnly);
    dataStream << magicBytes;
    return identifyFile(file, pos, buffer);
}

DatasetReader::DatasetReader(DatasetPath* path)
{
    setPath(path);
}
