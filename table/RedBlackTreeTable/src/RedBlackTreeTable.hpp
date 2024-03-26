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
    else if (Value* val = this->Find(key)) {
        *val = value;
        delete new_Node;
        return;
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

        new_Node->SetParent(static_cast<SRBNode<Key, Value>*>(parent));

        // новый узел или как левый, или правый потомок в зависимости от значения ключа
        
        auto rbParent = static_cast<SRBNode<Key, Value>*>(parent);
        if (key < parent->key) {
            rbParent->SetLeft(new_Node);
            rbParent->pRBLeft->SetParent(rbParent);
        }
        else {
            rbParent->SetRight(new_Node);
            rbParent->pRBRight->SetParent(rbParent);
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
    while (node != this->pRoot && node->pRBParent->color == RED) {

        // Если новый вставленный узел является левым потомком
        if (node->pRBParent == node->pRBParent->pRBParent->pRBLeft) {
            SRBNode<Key, Value>* uncle = node->pRBParent->pRBParent->pRBRight;

            // Случай 1: дядя узла красный
            if (uncle && uncle->color == RED) {
                node->pRBParent->color = BLACK;
                uncle->color = BLACK;
                node->pRBParent->pRBParent->color = RED;
                node = node->pRBParent->pRBParent;
            }
            else {
                // Случай 2: в этом случае дядя узла является черным, и узел находится справа от родителя, то есть он является правым потомком (и последним)
                if (node == node->pRBParent->pRBRight) {
                    node = node->pRBParent;
                    LeftRotate(node);
                }
                // Случай 3: когда дядя черный, а узел является левым потомком, выполняется правило красно-черного дерева, что оба ребенка красного узла должны быть черными
                node->pRBParent->color = BLACK;
                node->pRBParent->pRBParent->color = RED;
                RightRotate(node->pRBParent->pRBParent);
            }
        }
        else {
            SRBNode<Key, Value>* uncle = node->pRBParent->pRBParent->pRBLeft;
            if (uncle && uncle->color == RED) {
                node->pRBParent->color = BLACK;
                uncle->color = BLACK;
                node->pRBParent->pRBParent->color = RED;
                node = node->pRBParent->pRBParent;
            }
            else {
                if (node == node->pRBParent->pLeft) {
                    node = node->pRBParent;
                    RightRotate(node);
                }
                node->pRBParent->color = BLACK;
                node->pRBParent->pRBParent->color = RED;
                LeftRotate(node->pRBParent->pRBParent);
            }
        }
    }
}

template<class Key, class Value>
void RedBlackTreeTable<Key, Value>::BalanceDeletion(SRBNode<Key, Value>* node)
{
    while (node != this->pRoot && (node == nullptr || node->color == BLACK)) {
        if (node == node->pParent->pLeft) {
            SRBNode<Key, Value>* brother = node->pRBParent->pRBRight;

            if (brother->color == RED) {
                // Случай 1: брат - узла красный
                brother->color = BLACK;
                node->pRBParent->color = RED;
                LeftRotate(node->pRBParent);
                brother = node->pRBParent->pRBRight;
            }

            if ((brother->pRBLeft == nullptr || brother->pRBLeft->color == BLACK) &&
                (brother->pRBRight == nullptr || brother->pRBRight->color == BLACK)) {
                // Случай 2: оба ребенка брата черные
                brother->color = RED;
                node = node->pRBParent;
            }
            else {
                if (brother->pRBRight == nullptr || brother->pRBRight->color == BLACK) {
                    // Случай 3: правый ребенок брата черный
                    brother->pRBLeft->color = BLACK;
                    brother->color = RED;
                    RightRotate(brother);
                    brother = node->pRBParent->pRBRight;
                }

                // Случай 4: правый ребенок брата красный
                brother->color = node->pRBParent->color;
                node->pRBParent->color = BLACK;
                brother->pRBRight->color = BLACK;
                LeftRotate(node->pRBParent);
                node = static_cast<SRBNode<Key, Value>*>(this->pRoot);
            }
        }
        else {
            SRBNode<Key, Value>* brother = node->pRBParent->pRBLeft;

            if (brother->color == RED) {
                brother->color = BLACK;
                node->pRBParent->color = RED;
                RightRotate(node->pRBParent);
                brother = node->pRBParent->pRBLeft;
            }

            if ((brother->pRBRight == nullptr || brother->pRBRight->color == BLACK) &&
                (brother->pRBLeft == nullptr || brother->pRBLeft->color == BLACK)) {
                brother->color = RED;
                node = node->pRBParent;
            }
            else {
                if (brother->pRBLeft == nullptr || brother->pRBLeft->color == BLACK) {
                    // Случай 3: левый ребенок брата черный
                    brother->pRBRight->color = BLACK;
                    brother->color = RED;
                    LeftRotate(brother);
                    brother = node->pRBParent->pRBLeft;
                }

                // Случай 4: левый ребенок брата красный
                brother->color = node->pRBParent->color;
                node->pRBParent->color = BLACK;
                brother->pRBLeft->color = BLACK;
                RightRotate(node->pRBParent);
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
void RedBlackTreeTable<Key, Value>::LeftRotate(SRBNode<Key, Value>* node)
{
    // Левый поворот вокруг узла
    auto rightChild = node->pRBRight;
    node->SetRight(rightChild->pRBLeft);

    if (rightChild->pRBLeft != nullptr) { rightChild->pRBLeft->SetParent(node); }

    rightChild->SetParent(node->pRBParent);

    if (node->pRBParent == nullptr) { this->pRoot = rightChild; }
    else if (node == node->pRBParent->pRBLeft) { node->pRBParent->SetLeft(rightChild); }
    else { node->pRBParent->SetRight(rightChild); }

    rightChild->SetLeft(node);
    node->SetParent(rightChild);
}

template<class Key, class Value>
void RedBlackTreeTable<Key, Value>::RightRotate(SRBNode<Key, Value>* node)
{
    // Правый поворот вокруг узла
    auto leftChild = node->pRBLeft;
    node->SetLeft(leftChild->pRBRight);

    if (leftChild->pRBRight != nullptr) { leftChild->pRBRight->SetParent(node); }

    leftChild->SetParent(node->pRBParent);

    if (node->pRBParent == nullptr) { this->pRoot = leftChild; }
    else if (node == node->pRBParent->pRBRight) { node->pRBParent->SetRight(leftChild); }
    else { node->pRBParent->SetLeft(leftChild); }

    leftChild->pRBRight = node;
    node->pRBParent = leftChild;
}





