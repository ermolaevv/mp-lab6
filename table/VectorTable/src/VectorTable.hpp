template<class Key, class Value>
Value* VectorTable<Key, Value>::Find(Key key)
{
    return new Value();
}

template<class Key, class Value>
void VectorTable<Key, Value>::Insert(Key key, Value value)
{
}

template<class Key, class Value>
void VectorTable<Key, Value>::Delete(Key key)
{
}

template<class Key, class Value>
bool VectorTable<Key, Value>::IsTabEnded(void) const noexcept
{
    return false;
}

template<class Key, class Value>
size_t VectorTable<Key, Value>::GoNext(void) noexcept
{
    return size_t();
}

template<class Key, class Value>
Key VectorTable<Key, Value>::GetKey(void) const
{
    return Key();
}

template<class Key, class Value>
Value VectorTable<Key, Value>::GetValuePtr(void) const
{
    return Value();
}

