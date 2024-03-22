#include "HashTable.h"
template <class Key, class Value>
bool HashTable<Key, Value>::IsEmpty() const noexcept
{
    return this->length == 0;
}

template <class Key, class Value>
bool HashTable<Key, Value>::IsFull() const noexcept
{
    return this->length == this->maxSize;
}

template <class Key, class Value>
bool HashTable<Key, Value>::IsTabEnded(void) const noexcept
{
    return this->position >= length;
}

template <class Key, class Value>
Key HashTable<Key, Value>::GetKey(void) const
{
    if (this->actriveRec == nullptr) {
        throw std::runtime_error("No active record");
    }
    return this->actriveRec->key;
}

template <class Key, class Value>
Value* HashTable<Key, Value>::GetValuePtr(void) const
{
    if (this->actriveRec == nullptr) {
        throw std::runtime_error("No active record");
    }
    return &this->actriveRec->value;
}
