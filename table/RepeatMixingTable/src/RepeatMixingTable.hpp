#include "RepeatMixingTable.h"
template <class Key, class Value>
Value* RepeatMixingTable<Key, Value>::Find(Key key) {
    size_t ind = this->GetHash(key, this->maxSize);

    while (data[ind].key != 0 && data[ind].key != key) {
        ind = (ind + 1) % this->maxSize;
    }

    if (data[ind].key == 0) {
        throw std::runtime_error("Key not found");
    }

    return &this->data[ind].value;
}



template <class Key, class Value>
void RepeatMixingTable<Key, Value>::Insert(Key key, Value value) {
    if (this->length == this->maxSize) {
        throw std::runtime_error("Table is full");
    }

    size_t num = -1;
    size_t ind = this->GetHash(key, this->maxSize);

    while (data[ind].key != 0 && data[ind].key != key) {
        ind = (ind + 1) % this->maxSize;
    }

    if (data[ind].key == 0) {
        num = ind;
    }

    if (num != -1) {
        this->data[num] = Table<Key, Value>::STableRec<Key, Value>(key, value);
        this->length++;
    }
    else {
        this->data[ind].value = value;
    }
}



template <class Key, class Value>
size_t RepeatMixingTable<Key, Value>::Reset(void) noexcept {
    this->position = 0;
    return 0;
}

template <class Key, class Value>
size_t RepeatMixingTable<Key, Value>::GoNext(void) noexcept {
    do {
        this->position = (this->position + 1) % this->maxSize;
    } while (data[this->position].key == 0);
    return this->position;
}

template <class Key, class Value>
void RepeatMixingTable<Key, Value>::Delete(Key key) {
    size_t ind = this->GetHash(key, this->maxSize);

    while (data[ind].key != 0 && data[ind].key != key) {
        ind = (ind + 1) % this->maxSize;
    }

    if (data[ind].key == 0) {
        throw std::runtime_error("Key not found");
    }

    this->data[ind].key = 0;
    this->length--;
}

