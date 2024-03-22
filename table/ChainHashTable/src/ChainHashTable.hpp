#include "ChainHashTable.h"
template <class Key, class Value>
Value* ChainHashTable<Key, Value>::Find(Key key) {
    size_t index = this->GetHash(key, M);
    auto& list = this->data[index];
    for (auto& rec : list) {
        if (rec.key == key) {
            return &rec.value;
        }
    }
    throw std::runtime_error("Key not found");
}

template <class Key, class Value>
void ChainHashTable<Key, Value>::Insert(Key key, Value value) {
    if (this->length == M) {
        TDatList<STableRec>* newData = new TDatList<STableRec>[2 * M];
        for (size_t i = 0; i < M; ++i) {
            for (auto& rec : this->data[i]) {
                size_t newIndex = this->GetHash(rec.key, 2 * M);
                newData[newIndex].push_back(rec);
            }
        }
        delete[] this->data;
        this->data = newData;
        M *= 2;
    }

    size_t index = this->GetHash(key, M);
    auto& list = this->data[index];
    for (auto& rec : list) {
        if (rec.key == key) {
            rec.value = value;
            return;
        }
    }
    list.push_back({ key, value });
    this->length++;
}

template <class Key, class Value>
void ChainHashTable<Key, Value>::Delete(Key key) {
    size_t index = this->GetHash(key, M);
    auto& list = this->data[index];
    for (auto it = list.begin(); it != list.end(); ++it) {
        if (it->key == key) {
            list.erase(it);
            this->length--;
            return;
        }
    }
    throw std::runtime_error("Key not found");
}

template <class Key, class Value>
size_t ChainHashTable<Key, Value>::Reset(void) noexcept {
    this->position = 0;
    this->actriveRec = nullptr;
    return 0;
}

template <class Key, class Value>
size_t ChainHashTable<Key, Value>::GoNext(void) noexcept {
    while (this->position < M && this->data[this->position].empty()) {
        this->position++;
    }
    if (this->position < M) {
        this->actriveRec = &this->data[this->position].front();
        this->position++;
        return this->position - 1;
    }
    this->actriveRec = nullptr;
    return M;
}
