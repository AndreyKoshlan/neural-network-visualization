#ifndef DATASET_H
#define DATASET_H

#include <QString>
#include <QList>
#include <QByteArray>

struct DatasetItem {
    DatasetItem(float* input, float* output, uint inputCount, uint outputCount);
    ~DatasetItem();
    float* input;
    float* output;
    uint inputCount;
    uint outputCount;
};

typedef QList<DatasetItem*> DatasetItemList;

class Dataset
{
public: 
    Dataset();
    ~Dataset();
    void replace(qsizetype index, DatasetItem* value);
    void resize(qsizetype size);
    void add(DatasetItem* item);
    const DatasetItem* get(qsizetype i);
    qsizetype count() const;
    void clear();
private:
    DatasetItemList m_items;
};

#endif // DATASET_H
