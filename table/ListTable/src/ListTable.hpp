template<class Key, class Value>
Value* ListTable<Key, Value>::Find(Key key)
{
    return new Value();
}

template<class Key, class Value>
void ListTable<Key, Value>::Insert(Key key, Value value)
{
}

template<class Key, class Value>
void ListTable<Key, Value>::Delete(Key key)
{
}

template<class Key, class Value>
bool ListTable<Key, Value>::IsTabEnded(void) const noexcept
{
    return false;
}

template<class Key, class Value>
size_t ListTable<Key, Value>::GoNext(void) noexcept
{
    return size_t();
}

template<class Key, class Value>
Key ListTable<Key, Value>::GetKey(void) const
{
    return Key();
}

template<class Key, class Value>
Value ListTable<Key, Value>::GetValuePtr(void) const
{
    return Value();
}

