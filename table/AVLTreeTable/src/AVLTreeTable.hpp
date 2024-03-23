template<class Key, class Value>
void AVLTreeTable<Key, Value>::Insert(Key key, Value value)
{
    if (this->IsFull()) { throw std::runtime_error("Table is full."); }

    if (this->pRoot == nullptr) {
        this->pRoot = new SAVLNode<Key, Value>(key, value);
        this->length++;
        return;
    }

    SAVLNode<Key, Value>* parent = nullptr;
    SAVLNode<Key, Value>* current = static_cast<SAVLNode<Key, Value>*>(this->pRoot);

    while (current != nullptr) {
        parent = current;
        if (key < current->key) current = static_cast<SAVLNode<Key, Value>*>(current->pLeft);
        else if (key > current->key) current = static_cast<SAVLNode<Key, Value>*>(current->pRight);
        else {
            current->value = value;
            return;
        }
    }

    SAVLNode<Key, Value>* newNode = new SAVLNode<Key, Value>(key, value);

    if (key < parent->key) parent->pLeft = newNode;
    else parent->pRight = newNode;

    newNode->pParent = parent;
    this->length++;

    BalanceTreeAfterInsertion(newNode);
}

template<class Key, class Value>
void AVLTreeTable<Key, Value>::BalanceTreeAfterInsertion(SAVLNode<Key, Value>* node)
{
    SAVLNode<Key, Value>* parent = nullptr;
    SAVLNode<Key, Value>* grandparent = nullptr;

    while (node != nullptr) {
        parent = static_cast<SAVLNode<Key, Value>*>(node->pParent);

        if (node == parent->pLeft)  parent->balance++;
        else parent->balance--;

        if (std::abs(parent->balance) <= 1) return;  
        else if (std::abs(parent->balance) > 1) {
            grandparent = static_cast<SAVLNode<Key, Value>*>(parent->pParent);

            if (parent->balance == 2) {
                if (node == parent->pLeft) {
                    // (LL)
                    RotateRight(grandparent);
                }
                else {
                    // (LR)
                    RotateLeft(parent);
                    RotateRight(grandparent);
                }
            }
            else {
                if (node == parent->pRight) {
                    // (RR)
                    RotateLeft(grandparent);
                }
                else {
                    // (RL)
                    RotateRight(parent);
                    RotateLeft(grandparent);
                }
            }
            return; 
        }
        node = parent; 
    }
}


template<class Key, class Value>
void AVLTreeTable<Key, Value>::RotateRight(SAVLNode<Key, Value>* pivot)
{
    SAVLNode<Key, Value>* parent = static_cast<SAVLNode<Key, Value>*>(pivot->pParent);
    SAVLNode<Key, Value>* leftChild = static_cast<SAVLNode<Key, Value>*>(pivot->pLeft);

    pivot->pLeft = leftChild->pRight;
    if (pivot->pLeft != nullptr) pivot->pLeft->pParent = pivot;

    leftChild->pRight = pivot;
    leftChild->pParent = parent;
    pivot->pParent = leftChild;

    if (parent != nullptr) {
        if (parent->pLeft == pivot) parent->pLeft = leftChild;
        else parent->pRight = leftChild;
    }
    else { this->pRoot = leftChild; }
    pivot->balance = 0;
    leftChild->balance = 0;
}

template<class Key, class Value>
void AVLTreeTable<Key, Value>::RotateLeft(SAVLNode<Key, Value>* pivot)
{
    SAVLNode<Key, Value>* parent = static_cast<SAVLNode<Key, Value>*>(pivot->pParent);
    SAVLNode<Key, Value>* rightChild = static_cast<SAVLNode<Key, Value>*>(pivot->pRight);

    pivot->pRight = rightChild->pLeft;
    if (pivot->pRight != nullptr) pivot->pRight->pParent = pivot;

    rightChild->pLeft = pivot;
    rightChild->pParent = parent;
    pivot->pParent = rightChild;

    if (parent != nullptr) {
        if (parent->pLeft == pivot) parent->pLeft = rightChild;
        else parent->pRight = rightChild;
    }
    else { this->pRoot = rightChild; }
    pivot->balance = 0;
    rightChild->balance = 0;
}

template<class Key, class Value>
void AVLTreeTable<Key, Value>::Delete(Key key)
{
    return;
}
