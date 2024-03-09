#include "TableController.h"
template<class Key, class Value>
inline Value* TableController<Key, Value>::Find(Key key)
{
    return nullptr;
}

template<class Key, class Value>
void TableController<Key, Value>::Insert(Key key, Value value)
{
}

template<class Key, class Value>
void TableController<Key, Value>::Remove(Key key)
{
}

template<class Key, class Value>
void TableController<Key, Value>::SelectActiveTable(std::string name)
{
}

template<class Key, class Value>
void TableController<Key, Value>::AddTable(std::string name, Table<Key, Value>& table)
{
}

template<class Key, class Value>
void TableController<Key, Value>::RemoveTable(std::string name)
{
}
