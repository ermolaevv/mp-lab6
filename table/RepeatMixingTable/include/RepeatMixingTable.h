#ifndef _TABLE_REPEATMIXINGTABLE_
#define _TABLE_REPEATMIXINGTABLE_

#include <iostream>
#include "HashTable.h"

/// <summary>
/// Класс хэш-таблиц на методе повторного перемешивания.
/// </summary>
template <class Key, class Value>
class RepeatMixingTable : HashTable<Key, Value> {
protected:
    typename Table<Key, Value>::STableRec<Key, Value>* data;
public:
    RepeatMixingTable(size_t maxSize = 10000) : HashTable<Key, Value>(maxSize) {
        this->data = new typename Table<Key, Value>::template STableRec<Key, Value>[this->maxSize];
    }
    ~RepeatMixingTable() { delete[] data; }

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
    friend std::ostream& operator<<(std::ostream& os, RepeatMixingTable& tab)
    {
        std::cout << "Table printing" << std::endl;
        for (tab.Reset(); !tab.IsTabEnded(); tab.GoNext())
        {
            os << " Key: " << tab.GetKey() << " Val: " << *tab.GetValuePtr() << std::endl;
        }
        return os;
    }
};

#include "../src/RepeatMixingTable.hpp"

#endif
