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
    return size_t();
}

template<class Key, class Value>
bool TreeTable<Key, Value>::IsTabEnded(void) const noexcept
{
    return false;
}

template<class Key, class Value>
size_t TreeTable<Key, Value>::GoNext(void) noexcept
{
    return size_t();
}

template<class Key, class Value>
Value* TreeTable<Key, Value>::Find(Key key)
{
    return nullptr;
}

template<class Key, class Value>
Key TreeTable<Key, Value>::GetKey(void) const
{
    return this->pActiveNode->key;
}

template<class Key, class Value>
Value TreeTable<Key, Value>::GetValuePtr(void) const
{
    return this->pActiveNode->value;
}
