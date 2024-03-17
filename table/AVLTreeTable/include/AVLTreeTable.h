#ifndef _TABLE_AVLTREETABLE_
#define _TABLE_AVLTREETABLE_

#include <iostream>
#include "TreeTable.h"

/// <summary>
/// Класс таблиц на АВЛ дереве.
/// </summary>
template <class Key, class Value>
class AVLTreeTable : TreeTable<Key, Value> {
protected:
    /// <summary>
    /// Шаблонная стркутура узла дерева.
    /// </summary>
    template <class Key, class Value>
    struct SAVLNode : TreeTable<Key, Value>::template SNode<Key, Value> {
        int balance = 0;
        SAVLNode(Key key, Value value) : SNode(key, value) {}
    };

public:
    AVLTreeTable(size_t maxSize = 10000) : TreeTable(maxSize) {}

#pragma region Main Methods

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

    // Печать таблицы
    friend std::ostream& operator<<(std::ostream& os, AVLTreeTable& tab)
    {
        std::cout << "Table printing" << std::endl;
        for (tab.Reset(); !tab.IsTabEnded(); tab.GoNext())
        {
            os << " Key: " << tab.GetKey() << " Val: " << *tab.GetValuePtr() << std::endl;
        }
        return os;
    }
};

#include "../src/AVLTreeTable.hpp"

#endif
