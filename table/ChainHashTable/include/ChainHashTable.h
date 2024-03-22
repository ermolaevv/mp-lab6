#ifndef _TABLE_CHAINHASHTABLE_
#define _TABLE_CHAINHASHTABLE_

#include <iostream>
#include "HashTable.h"
#include "DatList.h"

/// <summary>
/// Класс хэш-таблиц на методе цепочек.
/// </summary>
template <class Key, class Value>
class ChainHashTable : HashTable<Key, Value> {
protected:
    /// <summary>
    /// Rоличество строк хэш-таблицы.
    /// </summary>
    static const size_t M = 11;

    TDatList<typename Table<Key, Value>::template STableRec<Key, Value>> data[M];
public:
    ChainHashTable(size_t maxSize = 10000) : HashTable<Key, Value>(maxSize) {}

#pragma region Main Methods
    /// <summary>
    /// Поиск записи по ключу.
    /// Если запись найдена, возвращает указатель на значение.
    /// Если запись не найдена, поднимается исключение.
    /// </summary>
    Value* Find(Key key) override;

    /// <summary>
    /// Вставка записи в таблицу.
    /// Если ключ уже существует, его значение будет изменено.
    /// </summary>
    void Insert(Key key, Value value) override;

    /// <summary>
    /// Удаление записи из таблицы.
    /// Если ключа не найдено, поднимается исключение.
    /// </summary>
    void Delete(Key key) override;

#pragma endregion

#pragma region Navigate
    /// <summary>
    /// Устанавливает текущую позицию на первую запись
    /// Возвращает 0
    /// </summary>
    virtual size_t Reset(void) noexcept override;


    /// <summary>
    /// Переход к следующей записи. После применения к последней записи, переходит к первой.
    /// Возвращает новую позицию.
    /// </summary>
    virtual size_t GoNext(void) noexcept override;
#pragma endregion

    // Печать таблицы
    friend std::ostream& operator<<(std::ostream& os, ChainHashTable& tab)
    {
        std::cout << "Table printing" << std::endl;
        for (tab.Reset(); !tab.IsTabEnded(); tab.GoNext())
        {
            os << " Key: " << tab.GetKey() << " Val: " << *tab.GetValuePtr() << std::endl;
        }
        return os;
    }
};

#include "../src/ChainHashTable.hpp"

#endif
