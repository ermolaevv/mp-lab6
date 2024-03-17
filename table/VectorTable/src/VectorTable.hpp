template<class Key, class Value>
Value* VectorTable<Key, Value>::Find(Key key)
{
    auto it = std::find_if(data.begin(), data.end(), [key](const auto& record) { return record.key == key; });
    if (it != data.end()) {
        return &it->value;
    }
    throw std::runtime_error("Key not found in the table.");
}

template<class Key, class Value>
void VectorTable<Key, Value>::Insert(Key key, Value value)
{
    try {
        Value* existingValue = Find(key);
        *existingValue = value;
    }
    catch (const std::runtime_error&) {
        data.push_back({ key, value });
    }
}

template<class Key, class Value>
void VectorTable<Key, Value>::Delete(Key key)
{
    try
    {
        Value* value = Find(key);
        data.erase(std::remove_if(data.begin(), data.end(), [key](const auto& record) {
            return record.key == key;
            }), data.end());
    }
    catch (const std::runtime_error&)
    {
        throw std::runtime_error("Key not found in the table.");
    }
}

template<class Key, class Value>
bool VectorTable<Key, Value>::IsTabEnded(void) const noexcept
{
    return position >= data.size();
}

template<class Key, class Value>
size_t VectorTable<Key, Value>::GoNext(void) noexcept
{
    if (position < data.size()) {
        position++;
    }
    else {
        position = 0;
    }
    return position;
}

template<class Key, class Value>
Key VectorTable<Key, Value>::GetKey(void) const
{
    if (position >= data.size()) {
        throw std::runtime_error("End of table reached.");
    }
    return data[position].key;
}

template<class Key, class Value>
Value VectorTable<Key, Value>::GetValuePtr(void) const
{
    if (position >= data.size()) {
        throw std::runtime_error("End of table reached.");
    }
    return data[position].value;
}
