#include "dataset.h"

DatasetItem::DatasetItem(float* input, float* output, uint inputCount, uint outputCount) {
    this->input = input;
    this->output = output;
    this->inputCount = inputCount;
    this->outputCount = outputCount;
}

DatasetItem::~DatasetItem() {
    delete[] input;
    delete[] output;
}

void Dataset::replace(qsizetype index, DatasetItem* value) {
    m_items.replace(index, value);
}

void Dataset::resize(qsizetype size) {
    qsizetype oldSize = m_items.size();
    m_items.resize(size);
    for (int i = oldSize; i < size; i++)
        m_items[i] = nullptr;
}

void Dataset::add(DatasetItem* item) {
    m_items.push_back(item);
}

qsizetype Dataset::count() const {
    return m_items.count();
}

const DatasetItem* Dataset::get(qsizetype i) {
    return m_items.at(i);
}

void Dataset::clear() {
    for (auto item: m_items) {
        delete item;
    }
    m_items.clear();
}

Dataset::Dataset() {

}

Dataset::~Dataset() {
    clear();
}
