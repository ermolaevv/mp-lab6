#ifndef _TABLE_HASHTABLE_
#define _TABLE_HASHTABLE_

#include <iostream>
#include "Table.h"

/// <summary>
/// Базовый класс хэш-таблиц. Абстрактный класс.
/// </summary>
template <class Key, class Value>
class HashTable : Table<Key, Value> {
protected:
    /// <summary>
    /// Длина таблицы (количество элементов).
    /// </summary>
    size_t length = 0;

    /// <summary>
    /// Указатель на активную запись.
    /// Перемещается вместе с полем position в методе GoNext
    /// При добавлении первой записи в таблицу, ссылается на эту запись
    /// При удалении последней записи, ссылается на nullptr
    /// </summary>
    typename Table<Key, Value>::template STableRec<Key, Value>* actriveRec = nullptr;

    /// <summary>
    /// Получить хеш по ключу.
    /// </summary>
    size_t GetHash(Key key, int mod) {
        size_t sum = 0;
        for (char ch: std::to_string(key))
            sum += ch;
        return sum % mod;
    }
public:
    HashTable(size_t maxSize = 10000) : Table<Key, Value>(maxSize) {}

#pragma region Info Methods
    /// <summary>
    /// Возращает количество записей (длину таблицы).
    /// </summary>
    size_t GetDataCount() const noexcept override;

    /// <summary>
    /// Проверка таблицы на пустоту.
    /// Если длина таблицы равна нулю, возвращает true.
    /// </summary>
    bool IsEmpty() const noexcept override;

    /// <summary>
    /// Проверка таблицы на заполненность.
    /// Если длина таблицы равна maxSize, возвращает true.
    /// </summary>
    bool IsFull() const noexcept override;

#pragma region Navigate
    /// <summary>
    /// Проверка окончания таблицы.
    /// Если таблица кончилась, то возращает true.
    /// </summary>
    virtual bool IsTabEnded(void) const noexcept override;
#pragma endregion

#pragma region Access
    /// <summary>
    /// Получить ключ активной записи.
    /// Если ключ не найден, поднимается исключение.
    /// </summary>
    virtual Key GetKey(void) const override;

    /// <summary>
    /// Получить значение активной записи.
    /// Если ключ не найден, поднимается исключение.
    /// </summary>
    virtual Value* GetValuePtr(void) const override;
#pragma endregion

    // Печать таблицы
    friend std::ostream& operator<<(std::ostream& os, HashTable& tab)
    {
        std::cout << "HashTable printing" << std::endl;
        for (tab.Reset(); !tab.IsTabEnded(); tab.GoNext())
        {
            os << " Key: " << tab.GetKey() << " Val: " << *tab.GetValuePtr() << std::endl;
        }
        return os;
    }
};

#include "../src/HashTable.hpp"

#endif
