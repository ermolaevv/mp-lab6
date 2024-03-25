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
    auto rec = new Table<Key, Value>::template STableRec<Key, Value>(key, value);
    if (list.GetCurrentPos() != 0)
        list.SetCurrentPos(list.GetCurrentPos() - 1);
    list.InsCurrent(rec);

    if (this->actriveRec == nullptr) {
        this->actriveRec = rec;
    }

    this->length++;
}

template <class Key, class Value>
void ChainHashTable<Key, Value>::Delete(Key key) {
    size_t index = this->GetHash(key, M);
    auto& list = this->data[index];

    for (list.Reset(); !list.IsListEnded(); list.GoNext()) {
        auto rec = list.GetDatValue();
        auto recKey = rec->key;
        if (rec->key == key) {
            list.DelCurrent();
            this->length--;

            if (recKey == this->actriveRec->key)
                this->GoNext();
            return;
        }
    }
    throw std::runtime_error("Key not found");
}

template <class Key, class Value>
size_t ChainHashTable<Key, Value>::Reset(void) noexcept {
    this->positionInData = 0;
    data[this->positionInData].Reset();
    this->GoNext();
    return this->position = 0;
}

template <class Key, class Value>
size_t ChainHashTable<Key, Value>::GoNext(void) noexcept {
    if (this->length == 0)
        return 0;

    if (!this->data[this->positionInData].IsListEnded()) {
        this->actriveRec = this->data[this->positionInData].GetDatValue();
        this->data[this->positionInData].GoNext();
        return ++this->position;
    }
    else {
        do {
            this->positionInData++;
        } while (this->positionInData < M && this->data[this->positionInData].GetLength() == 0);

        if (this->positionInData < M) {
            this->data[this->positionInData].Reset();
            return this->GoNext();
        }
    }

    this->positionInData = 0;
    this->data[this->positionInData].Reset();
    return this->GoNext();
}
