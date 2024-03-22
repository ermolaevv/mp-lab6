#include "ChainHashTable.h"
template <class Key, class Value>
Value* ChainHashTable<Key, Value>::Find(Key key) {
    size_t index = this->GetHash(key, M);
    auto& list = this->data[index];

    for (list.Reset(); !list.IsListEnded(); list.GoNext()) {
        auto rec = list.GetDatValue();
        if (rec == nullptr)
            break;
        if (rec->key == key) {
            return &rec->value;
        }
    }
    throw std::runtime_error("Key not found");
}

template <class Key, class Value>
void ChainHashTable<Key, Value>::Insert(Key key, Value value) {
    size_t index = this->GetHash(key, M);
    auto& list = this->data[index];

    for (list.Reset(); !list.IsListEnded(); list.GoNext()) {
        auto rec = list.GetDatValue();
        if (rec == nullptr)
            break;
        if (rec->key == key) {
            rec->value = value;
            return;
        }
    }
    list.InsCurrent(new Table<Key, Value>::STableRec<Key, Value>(key, value));
    this->length++;
}

template <class Key, class Value>
void ChainHashTable<Key, Value>::Delete(Key key) {
    size_t index = this->GetHash(key, M);
    auto& list = this->data[index];

    for (list.Reset(); !list.IsListEnded(); list.GoNext()) {
        auto rec = list.GetDatValue();
        if (rec->key == key) {
            list.DelCurrent();
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
    while (this->position < M && this->data[this->position].GetLength() == 0) {
        this->position++;
    }
    if (this->position < M) {
        this->actriveRec = this->data[this->position].GetFirst()->GetDatValue();
        this->position++;
        return this->position - 1;
    }
    this->actriveRec = nullptr;
    return M;
}
