#ifndef _TABLE_TREETABLE_
#define _TABLE_TREETABLE_

#include <iostream>
#include "Table.h"

/// <summary>
/// Базовый класс таблиц на деревьях. Абстрактный класс.
/// </summary>
template <class Key, class Value>
class TreeTable : Table<Key, Value> {
protected:
    /// <summary>
    /// Шаблонная стркутура узла дерева.
    /// </summary>
    template <class Key, class Value>
    struct SNode : Table<Key, Value>::template STableRec<Key, Value> {
        SNode* pLeft = nullptr;
        SNode* pRight = nullptr;
        SNode(Key key, Value value) : STableRec(key, value) {}
    };

    /// <summary>
    /// Корневой узел дерева.
    /// </summary>
    SNode<Key, Value>* pRoot = nullptr;

    /// <summary>
    /// Текущая позиция (в узлах).
    /// </summary>
    SNode<Key, Value>* pActiveNode = nullptr;

    /// <summary>
    /// Длина таблицы.
    /// </summary>
    size_t length = 0;
public:
    TreeTable(size_t maxSize = 10000) : Table<Key, Value>(maxSize) {}

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
    /// Устанавливает текущую позицию на первую запись
    /// Возвращает 0
    /// </summary>
    virtual size_t Reset(void) noexcept override;

    /// <summary>
    /// Проверка окончания таблицы.
    /// Если таблица кончилась, то возращает true.
    /// </summary>
    virtual bool IsTabEnded(void) const noexcept override;

    /// <summary>
    /// Переход к следующей записи. После применения к последней записи, переходит к первой.
    /// Возвращает новую позицию.
    /// </summary>
    virtual size_t GoNext(void) noexcept override;
#pragma endregion

#pragma region Main Methods
    /// <summary>
    /// Поиск записи по ключу.
    /// Если запись найдена, возвращает указатель на значение.
    /// Если запись не найдена, поднимается исключение.
    /// </summary>
    Value* Find(Key key) override;

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
    friend std::ostream& operator<<(std::ostream& os, TreeTable& tab)
    {
        std::cout << "TreeTable printing" << std::endl;
        for (tab.Reset(); !tab.IsTabEnded(); tab.GoNext())
        {
            os << " Key: " << tab.GetKey() << " Val: " << *tab.GetValuePtr() << std::endl;
        }
        return os;
    }
};

#include "../src/TreeTable.hpp"

#endif
