#include "TableController.h"
template<class Key, class Value>
std::string TableController<Key, Value>::GetActiveName(void) noexcept
{
    for (auto& table : tables)
        if (table.second == activeTable)
            return table.first;
    return std::string();
}

template<class Key, class Value>
inline size_t TableController<Key, Value>::GetRecCount(void)
{
    return this->activeTable->GetDataCount();
}

template<class Key, class Value>
Value* TableController<Key, Value>::Find(Key key)
{
    if (this->activeTable == nullptr)
        throw std::runtime_error("Table Controller is empty. Add a table");

    return this->activeTable->Find(key);
}

template<class Key, class Value>
void TableController<Key, Value>::Insert(Key key, Value value)
{
    if (this->tables.size() == 0)
        throw std::runtime_error("Table Controller is empty. Add a table");

    for (auto table : this->tables) {
        table.second->Insert(key, value);
    }
}

template<class Key, class Value>
void TableController<Key, Value>::Remove(Key key)
{
    if (this->activeTable == nullptr)
        throw std::runtime_error("Table Controller is empty. Add a table");

    for (auto table : this->tables) {
        table.second->Delete(key);
    }
}

template<class Key, class Value>
void TableController<Key, Value>::SelectActiveTable(std::string name)
{
    auto found = std::find_if(
        tables.begin(), tables.end(),
        [name](const auto& record) { return record.first == name; }
    );

    if (found == std::end(tables))
        throw std::runtime_error("Wrong table name");
    else
        this->activeTable = found->second;
}

template<class Key, class Value>
void TableController<Key, Value>::AddTable(std::string name, Table<Key, Value>* table)
{
    auto found = std::find_if(
        tables.begin(), tables.end(),
        [name](const auto& record) { return record.first == name; }
    );

    if (found == std::end(tables)) {
        this->tables.push_back(std::pair<std::string, Table<Key, Value>*>(name, table));
        this->names.push_back(name);
    }
    else 
        found->second = table;

    if (this->activeTable == nullptr) {
        this->activeTable = table;
    }
}

template<class Key, class Value>
void TableController<Key, Value>::RemoveTable(std::string name)
{
    auto erased = std::erase_if(
        tables.begin(), tables.end(),
        [name](const auto& record) { return record.first == name; }
    );

    if (erased == 0)
        throw std::runtime_error("Wrong table name");
    else {
        names.erase(name);
    }

    if (tables.size() == 0)
        this->activeTable = nullptr;
}

template<class Key, class Value>
size_t TableController<Key, Value>::Reset(void) noexcept
{
    return this->activeTable->Reset();
}

template<class Key, class Value>
bool TableController<Key, Value>::IsTabEnded(void) const noexcept
{
    if (this->activeTable->GetDataCount() == 0) return 0;
    return this->activeTable->IsTabEnded();
}

template<class Key, class Value>
size_t TableController<Key, Value>::GoNext(void) noexcept
{
    return this->activeTable->GoNext();
}

template<class Key, class Value>
Key TableController<Key, Value>::GetKey(void) const
{
    return this->activeTable->GetKey();
}

template<class Key, class Value>
Value* TableController<Key, Value>::GetValuePtr(void) const
{
    return this->activeTable->GetValuePtr();
}
