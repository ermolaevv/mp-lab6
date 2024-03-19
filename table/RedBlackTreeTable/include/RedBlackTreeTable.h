#ifndef _TABLE_REDBLACKTREETABLE_
#define _TABLE_REDBLACKTREETABLE_

#include <iostream>
#include "TreeTable.h"

/// <summary>
/// Класс таблиц на красно-черном дереве.
/// </summary>
template <class Key, class Value>
class RedBlackTreeTable : TreeTable<Key, Value> {
protected:
    /// <summary>
    /// Перечисление цветов узлов
    /// </summary>
    enum Color {
        RED,
        BLACK
    };

    /// <summary>
    /// Шаблонная стркутура узла дерева.
    /// </summary>
    template <class Key, class Value>
    struct SRBNode : TreeTable<Key, Value>::template SNode<Key, Value> {
        Color color;
        SRBNode(Key key, Value value) : SNode(key, value) {}
    };
public:
    RedBlackTreeTable(size_t maxSize = 10000) : TreeTable<Key, Value>(maxSize) {}

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
    friend std::ostream& operator<<(std::ostream& os, RedBlackTreeTable& tab)
    {
        std::cout << "RedBlack printing" << std::endl;
        for (tab.Reset(); !tab.IsTabEnded(); tab.GoNext())
        {
            os << " Key: " << tab.GetKey() << " Val: " << *tab.GetValuePtr() << std::endl;
        }
        return os;
    }
private:
#pragma region Auxiliary Methods

    /// <summary>
    /// Балансировка дерева после вставки нового узла.
    /// </summary>
    /// <param name="node">Новый узел.</param>
    void BalanceInsertion(SRBNode<Key, Value>* node);

    /// <summary>
    /// Балансировка дерева после удаления узла.
    /// </summary>
    /// <param name="node">Удаленный узел.</param>
    void BalanceDeletion(SRBNode<Key, Value>* node);

    /// <summary>
    /// Левый поворот вокруг узла.
    /// </summary>
    /// <param name="node">Узел, вокруг которого происходит поворот.</param>
    void LeftRotate(SRBNode<Key, Value>* node);

    /// <summary>
    /// Правый поворот вокруг узла.
    /// </summary>
    /// <param name="node">Узел, вокруг которого происходит поворот.</param>
    void RightRotate(SRBNode<Key, Value>* node);

#pragma endregion
};

#include "../src/RedBlackTreeTable.hpp"

#endif
