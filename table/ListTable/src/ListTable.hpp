#include "ListTable.h"
template<class Key, class Value>
Value* ListTable<Key, Value>::Find(Key key)
{
    data.Reset();

    while (!data.IsListEnded()) {
        auto* record = data.GetDatValue();
        if (record == nullptr)
            break;

        if (record->key == key)
            return &record->value;

        data.GoNext();
    }

    throw std::runtime_error("Key not found in the table.");
}

template<class Key, class Value>
void ListTable<Key, Value>::Insert(Key key, Value value)
{
    try {
        Value* recValue = Find(key);
        *recValue = value;
    }
    catch (std::runtime_error) {
        if (!IsFull())
            data.InsLast(new Table<Key, Value>::STableRec<Key, Value>(key, value));
        else
            throw std::length_error("Table is overflow");
    }
}

template<class Key, class Value>
void ListTable<Key, Value>::Delete(Key key)
{
    Value* recValue = Find(key);
    data.DelCurrent();
}

template<class Key, class Value>
size_t ListTable<Key, Value>::Reset(void) noexcept
{
    data.Reset();
    return Table<Key, Value>::Reset();
}

template<class Key, class Value>
bool ListTable<Key, Value>::IsTabEnded(void) const noexcept
{
    return data.IsListEnded();
}

template<class Key, class Value>
size_t ListTable<Key, Value>::GoNext(void) noexcept
{
    this->position = data.GoNext();
    return this->position;
}

template<class Key, class Value>
Key ListTable<Key, Value>::GetKey(void) const
{
    auto* rec = data.GetDatValue();
    if (rec == nullptr)
        throw std::runtime_error("Getting key from empty table");
    return rec->key;
}

template<class Key, class Value>
Value ListTable<Key, Value>::GetValuePtr(void) const
{
    auto* rec = data.GetDatValue();
    if (rec == nullptr)
        throw std::runtime_error("Getting value from empty table");
    return rec->value;
}

