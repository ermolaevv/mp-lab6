template<class Key, class Value>
size_t TreeTable<Key, Value>::GetDataCount() const noexcept
{
    return this->length;
}

template<class Key, class Value>
bool TreeTable<Key, Value>::IsEmpty() const noexcept
{
    return this->length == 0;
}

template<class Key, class Value>
bool TreeTable<Key, Value>::IsFull() const noexcept
{
    return this->length == this->maxSize;
}

template<class Key, class Value>
size_t TreeTable<Key, Value>::Reset(void) noexcept
{
    this->pActiveNode = this->pRoot;
    while (this->pActiveNode && this->pActiveNode->pLeft != nullptr) {  this->pActiveNode = this->pActiveNode->pLeft; }
    while (this->pActiveNode && this->pActiveNode->key == Key()) this->GoNext();
    this->position = 0;
    return 0;
}

template<class Key, class Value>
bool TreeTable<Key, Value>::IsTabEnded(void) const noexcept
{
    return this->pActiveNode == nullptr || this->position >= this->length;
}

template<class Key, class Value>
size_t TreeTable<Key, Value>::GoNext(void) noexcept
{
    if (this->position == this->length - 1) { return ++this->position; }
    if (this->pActiveNode == nullptr) { return 0; }

    if (this->pActiveNode->pRight != nullptr) {
        this->pActiveNode = this->pActiveNode->pRight;
        while (this->pActiveNode->pLeft != nullptr)
            this->pActiveNode = this->pActiveNode->pLeft;
    }
    else {
        SNode<Key, Value>* pPrevNode = nullptr;
        while (this->pActiveNode->pParent != nullptr) {
            pPrevNode = this->pActiveNode;
            this->pActiveNode = this->pActiveNode->pParent;
            if (this->pActiveNode->pLeft == pPrevNode) { break; }
        }
    }

    if (this->pActiveNode->key == Key()) { return this->GoNext(); }

    this->position++;
    return 0;
}

template<class Key, class Value>
Value* TreeTable<Key, Value>::Find(Key key)
{
    SNode<Key, Value>* currentNode = this->pRoot;
    // добавить исключение
    while (currentNode != nullptr) {
        if (key == currentNode->key) { return &(currentNode->value); }
        else if (key < currentNode->key) { currentNode = currentNode->pLeft; }
        else { currentNode = currentNode->pRight; }
    }
    return nullptr;
}


template <class Key, class Value>
typename TreeTable<Key, Value>::template SNode<Key, Value>* TreeTable<Key, Value>::FindNode(Key key) {
    SNode<Key, Value>* currentNode = pRoot;

    while (currentNode != nullptr) {
        if (currentNode->key == key) {
            return currentNode;
        }
        else if (key < currentNode->key) {
            currentNode = currentNode->pLeft;
        }
        else {
            currentNode = currentNode->pRight;
        }
    }

    auto tmpActiveNode = this->pActiveNode;
    auto tmpPosition = this->position;

    currentNode = nullptr;
    for (this->Reset(); !this->IsTabEnded(); this->GoNext()) {
        if (this->pActiveNode->key == key) {
            currentNode = this->pActiveNode;
            break;
        }
    }

    this->pActiveNode = tmpActiveNode;
    this->position = tmpPosition;

    return currentNode;
}


template<class Key, class Value>
Key TreeTable<Key, Value>::GetKey(void) const
{
    if (this->pActiveNode != nullptr) { return this->pActiveNode->key; }
    else { throw std::runtime_error("ActiveNode is null."); }
}

template<class Key, class Value>
Value* TreeTable<Key, Value>::GetValuePtr(void) const
{
    if (this->pActiveNode != nullptr) { return &(this->pActiveNode->value); }
    else { throw std::runtime_error("Active node is null."); }
}
