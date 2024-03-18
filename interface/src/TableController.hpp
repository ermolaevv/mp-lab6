#include "TableController.h"
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
