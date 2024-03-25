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
        if (key < parent->key) {
            parent->pLeft = new_Node;
            parent->pLeft->pParent = parent;
        }
        else {
            parent->pRight = new_Node;
            parent->pRight->pParent = parent;
        }
    }
    BalanceInsertion(new_Node);
    this->length++;
}


template<class Key, class Value>
void RedBlackTreeTable<Key, Value>::Delete(Key key)
{
    auto delete_Node = static_cast<SRBNode<Key, Value>*>(this->FindNode(key));


    if (!delete_Node) { throw std::runtime_error("Key not found."); }

    Color delete_Node_Color = delete_Node->color;

    delete_Node->key = Key{};
    delete_Node->value = Value{};
    delete_Node->color = BLACK; 

    this->length--;
    if (delete_Node_Color == RED) { return; }
    BalanceDeletion(delete_Node);
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
void RedBlackTreeTable<Key, Value>::BalanceDeletion(SRBNode<Key, Value>* node)
{
    while (node != this->pRoot && (node == nullptr || node->color == BLACK)) {
        if (node == node->pParent->pLeft) {
            SRBNode<Key, Value>* brother = node->pParent->pRight;

            if (brother->color == RED) {
                // Случай 1: брат - узла красный
                brother->color = BLACK;
                node->pParent->color = RED;
                LeftRotate(node->pParent);
                brother = node->pParent->pRight;
            }

            if ((brother->pLeft == nullptr || brother->pLeft->color == BLACK) &&
                (brother->pRight == nullptr || brother->pRight->color == BLACK)) {
                // Случай 2: оба ребенка брата черные
                brother->color = RED;
                node = node->pParent;
            }
            else {
                if (brother->pRight == nullptr || brother->pRight->color == BLACK) {
                    // Случай 3: правый ребенок брата черный
                    brother->pLeft->color = BLACK;
                    brother->color = RED;
                    RightRotate(brother);
                    brother = node->pParent->pRight;
                }

                // Случай 4: правый ребенок брата красный
                brother->color = node->pParent->color;
                node->pParent->color = BLACK;
                brother->pRight->color = BLACK;
                LeftRotate(node->pParent);
                node = static_cast<SRBNode<Key, Value>*>(this->pRoot);
            }
        }
        else {
            SRBNode<Key, Value>* brother = node->pParent->pLeft;

            if (brother->color == RED) {
                brother->color = BLACK;
                node->pParent->color = RED;
                RightRotate(node->pParent);
                brother = node->pParent->pLeft;
            }

            if ((brother->pRight == nullptr || brother->pRight->color == BLACK) &&
                (brother->pLeft == nullptr || brother->pLeft->color == BLACK)) {
                brother->color = RED;
                node = node->pParent;
            }
            else {
                if (brother->pLeft == nullptr || brother->pLeft->color == BLACK) {
                    // Случай 3: левый ребенок брата черный
                    brother->pRight->color = BLACK;
                    brother->color = RED;
                    LeftRotate(brother);
                    brother = node->pParent->pLeft;
                }

                // Случай 4: левый ребенок брата красный
                brother->color = node->pParent->color;
                node->pParent->color = BLACK;
                brother->pLeft->color = BLACK;
                RightRotate(node->pParent);
                node = static_cast<SRBNode<Key, Value>*>(this->pRoot);
            }
        }
    }

    // узел всегда черный - важное свойство!!!
    if (node != nullptr) {
        node->color = BLACK;
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





