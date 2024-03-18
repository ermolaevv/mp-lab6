#ifndef _INTERFACE_TABLECONTROLLER_
#define _INTERFACE_TABLECONTROLLER_

#include <vector>

#include "VectorTable.h"
#include "ListTable.h"
#include "OrderedTable.h"


/// <summary>
/// Менеджер таблиц для интерфейса. 
/// </summary>
template <class Key, class Value>
class TableController {
protected:
    /// <summary>
    /// Вектор всех таблиц с индификаторами (именем)
    /// </summary>
    std::vector<std::pair<std::string, Table<Key, Value>*>> tables;
    std::vector<std::string> names;

    /// <summary>
    /// Указатель на активную таблицу
    /// </summary>
    Table<Key, Value>* activeTable = nullptr;
public:
    /// <summary>
    /// Получить список имен таблиц
    /// </summary>
    std::vector<std::string>& GetNames(void) noexcept { return names; }

#pragma region Record
    /// <summary>
    /// Поиск по ключу в активной таблице.
    /// Если запись найдена, возвращает указатель на значение.
    /// Если запись не найдена, поднимается исключение.
    /// </summary>
    Value* Find(Key key);

    /// <summary>
    /// Вставить запись во все таблицы
    /// </summary>
    void Insert(Key key, Value value);

    /// <summary>
    /// Удалить запись из всех таблиц
    /// </summary>  
    void Remove(Key key);
#pragma endregion

#pragma region Table
    /// <summary>
    /// Задать активную таблицу по индификатору
    /// </summary>
    void SelectActiveTable(std::string name);

    /// <summary>
    /// Добавить таблицу в список таблиц
    /// </summary>
    void AddTable(std::string name, Table<Key, Value>* table);


    /// <summary>
    /// Удалить таблицу из списока таблиц по ключу
    /// </summary>
    void RemoveTable(std::string name);

    // Печать таблицы
    friend std::ostream& operator<<(std::ostream& os, TableController& tab)
    {
        return os << *tab.activeTable;
    }
#pragma endregion
};

#include "../src/TableController.hpp"

#endif
