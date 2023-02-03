#ifndef DATASETREADER_H
#define DATASETREADER_H

#include <QString>
#include <QFile>

#include "dataset.h"

struct DatasetPath {
    virtual ~DatasetPath() { }
};

class DatasetReader
{
public:
    DatasetReader(DatasetPath* path);
    DatasetReader() = delete;

    static bool identifyFile(QFile* file, int pos, const QByteArray magicBytes);
    static bool identifyFile(QFile* file, int pos, const int magicBytes);

    virtual bool read(Dataset* dataset) = 0;

    const DatasetPath* path() const { return m_path; }
    void setPath(DatasetPath* path) { m_path = path; }
private:
    DatasetPath* m_path;
};

#endif // DATASETREADER_H
