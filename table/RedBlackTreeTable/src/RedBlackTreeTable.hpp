template<class Key, class Value>
void RedBlackTreeTable<Key, Value>::Insert(Key key, Value value)
{
    SRBNode<Key, Value>* new_Node = new SRBNode<Key, Value>(key, value);
    new_Node->color = RED; // Новый узел всегда красный

    if (this->pRoot == nullptr) {
        // Если дерево пустое, новый узел черный корень 1
        this->pRoot = new_Node;
        new_Node->color = BLACK;
    }
    else {
        // Если нет, то ищем место для вставки и добавляем узел как в обычное бинарное дерево поиска
        auto current = this->pRoot;
        auto parent = this->pRoot;

        while (current != nullptr) {
            parent = current;
            if (key < current->key) { current = current->pLeft; }
            else { current = current->pRight; }
        }

        new_Node->pParent = static_cast<SRBNode<Key, Value>*>(parent);

        // новый узел или как левый, или правый потомок в зависимости от значения ключа
        if (key < parent->key) { parent->pLeft = new_Node; }
        else { parent->pRight = new_Node; }
    }
    BalanceInsertion(new_Node);
}


template<class Key, class Value>
void AVLTreeTable<Key, Value>::Delete(Key key)
{
    // Находим узел для удаления
    SAVLNode<Key, Value>* deleteNode = static_cast<SAVLNode<Key, Value>*>(this->FindNode(key));

    // Если узел не найден, просто возвращаемся
    if (!deleteNode) return;

    // Реализация удаления узла и балансировки дерева

    // Если у удаляемого узла нет детей или только один ребенок
    if (!deleteNode->pLeft || !deleteNode->pRight) {
        SAVLNode<Key, Value>* child = deleteNode->pLeft ? deleteNode->pLeft : deleteNode->pRight;

        // Обработка случая, когда у удаляемого узла нет родителя (удаляемый узел - корень)
        if (!deleteNode->pParent) {
            this->pRoot = child;
            if (child) child->pParent = nullptr;
            delete deleteNode;
            this->length--;
            return;
        }

        // Обработка случая, когда у удаляемого узла есть родитель
        if (deleteNode == deleteNode->pParent->pLeft) {
            deleteNode->pParent->pLeft = child;
        }
        else {
            deleteNode->pParent->pRight = child;
        }

        if (child) child->pParent = deleteNode->pParent;
        delete deleteNode;
        this->length--;
    }
    else {
        // Если у удаляемого узла есть оба ребенка

        // Находим преемника (следующий по значению узел)
        SAVLNode<Key, Value>* successor = static_cast<SAVLNode<Key, Value>*>(this->Successor(deleteNode));

        // Копируем данные преемника в удаляемый узел
        deleteNode->key = successor->key;
        deleteNode->value = successor->value;

        // Рекурсивно вызываем удаление для преемника
        this->Delete(successor->key);
    }

    // Вызываем функцию для балансировки дерева после удаления
    BalanceTreeAfterDeletion(deleteNode);
}

template<class Key, class Value>
void AVLTreeTable<Key, Value>::BalanceTreeAfterDeletion(SAVLNode<Key, Value>* node)
{
    SAVLNode<Key, Value>* parent = nullptr;

    // Балансируем дерево от удаленного узла к корню
    while (node != nullptr) {
        parent = static_cast<SAVLNode<Key, Value>*>(node->pParent);

        if (parent == nullptr) break; // Достигли корня

        // Обновляем баланс родителя
        if (node == parent->pLeft) {
            parent->balance--;
        }
        else {
            parent->balance++;
        }

        // Если баланс стал -1 или 1, значит, высота поддерева уменьшилась, и может понадобиться дополнительная балансировка
        if (parent->balance == -1 || parent->balance == 1) {
            node = parent;
            continue;
        }

        // Если баланс стал 0, значит, высота поддерева не изменилась, и дальнейшая балансировка не требуется
        if (parent->balance == 0) {
            break;
        }

        // Если баланс стал -2 или 2, значит, высота поддерева увеличилась и требуется балансировка
        if (parent->balance == -2 || parent->balance == 2) {
            SAVLNode<Key, Value>* grandparent = static_cast<SAVLNode<Key, Value>*>(parent->pParent);

            if (parent->balance == -2) {
                // У родителя сбалансированность -2, значит, правое поддерево увеличилось
                // Нужно определить, куда именно добавился узел, чтобы правильно выполнить повороты

                if (node == parent->pLeft) {
                    // Удаляемый узел был слева от родителя
                    // Сбалансированность правого поддерева родителя увеличилась, нужен поворот LL
                    RotateRight(grandparent);
                }
                else {
                    // Удаляемый узел был справа от родителя
                    // Сбалансированность правого поддерева родителя не изменилась, нужен поворот LR
                    RotateLeft(parent);
                    RotateRight(grandparent);
                }
            }
            else {
                // Аналогично, только сбалансированность равна 2, значит, левое поддерево увеличилось

                if (node == parent->pRight) {
                    // Удаляемый узел был справа от родителя
                    // Сбалансированность левого поддерева родителя увеличилась, нужен поворот RR
                    RotateLeft(grandparent);
                }
                else {
                    // Удаляемый узел был слева от родителя
                    // Сбалансированность левого поддерева родителя не изменилась, нужен поворот RL
                    RotateRight(parent);
                    RotateLeft(grandparent);
                }
            }

            // Балансировка завершена
            break;
        }
    }
}


template<class Key, class Value>
void RedBlackTreeTable<Key, Value>::BalanceInsertion(SRBNode<Key, Value>* node)
{
    while (node != this->pRoot && node->pParent->color == RED) {

        // Если новый вставленный узел является левым потомком
        if (node->pParent == node->pParent->pParent->pLeft) {
            SRBNode<Key, Value>* uncle = node->pParent->pParent->pRight;

            // Случай 1: дядя узла красный
            if (uncle && uncle->color == RED) {
                node->pParent->color = BLACK;
                uncle->color = BLACK;
                node->pParent->pParent->color = RED;
                node = node->pParent->pParent;
            }
            else {
                // Случай 2: в этом случае дядя узла является черным, и узел находится справа от родителя, то есть он является правым потомком (и последним)
                if (node == node->pParent->pRight) {
                    node = node->pParent;
                    LeftRotate(node);
                }
                // Случай 3: когда дядя черный, а узел является левым потомком, выполняется правило красно-черного дерева, что оба ребенка красного узла должны быть черными
                node->pParent->color = BLACK;
                node->pParent->pParent->color = RED;
                RightRotate(node->pParent->pParent);
            }
        }
        else {
            SRBNode<Key, Value>* uncle = node->pParent->pParent->pLeft;
            if (uncle && uncle->color == RED) {
                node->pParent->color = BLACK;
                uncle->color = BLACK;
                node->pParent->pParent->color = RED;
                node = node->pParent->pParent;
            }
            else {
                if (node == node->pParent->pLeft) {
                    node = node->pParent;
                    RightRotate(node);
                }
                node->pParent->color = BLACK;
                node->pParent->pParent->color = RED;
                LeftRotate(node->pParent->pParent);
            }
        }
    }
}



template<class Key, class Value>
void RedBlackTreeTable<Key, Value>::LeftRotate(TreeTable<Key, Value>::template SNode<Key, Value>* node)
{
    // Левый поворот вокруг узла
    auto rightChild = node->pRight;
    node->pRight = rightChild->pLeft;

    if (rightChild->pLeft != nullptr) { rightChild->pLeft->pParent = node; }

    rightChild->pParent = node->pParent;

    if (node->pParent == nullptr) { this->pRoot = rightChild; }
    else if (node == node->pParent->pLeft) { node->pParent->pLeft = rightChild; }
    else { node->pParent->pRight = rightChild; }

    rightChild->pLeft = node;
    node->pParent = rightChild;
}

template<class Key, class Value>
void RedBlackTreeTable<Key, Value>::RightRotate(TreeTable<Key, Value>::template SNode<Key, Value>* node)
{
    // Правый поворот вокруг узла
    auto leftChild = node->pLeft;
    node->pLeft = leftChild->pRight;

    if (leftChild->pRight != nullptr) { leftChild->pRight->pParent = node; }

    leftChild->pParent = node->pParent;

    if (node->pParent == nullptr) { this->pRoot = leftChild; }
    else if (node == node->pParent->pRight) { node->pParent->pRight = leftChild; }
    else { node->pParent->pLeft = leftChild; }

    leftChild->pRight = node;
    node->pParent = leftChild;
}





