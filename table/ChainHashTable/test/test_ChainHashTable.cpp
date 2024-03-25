    #include <gtest/gtest.h>
    #include "ChainHashTable.h"
    using namespace std;

    TEST(ChainHashTable, InsertAndFind) {
        ChainHashTable<string, int> hashTable;
        string key = "test";
        int value = 1;
        hashTable.Insert(key, value);
        ASSERT_EQ(*hashTable.Find(key), value);
    }

    TEST(ChainHashTable, Delete) {
        ChainHashTable<string, int> hashTable;
        hashTable.Insert("test5", 5);
        hashTable.Delete("test5");
        ASSERT_THROW(hashTable.Find("test5"), runtime_error);
    }

    TEST(ChainHashTable, FindNonExistentKey) {
        ChainHashTable<string, int> hashTable;
        ASSERT_THROW(hashTable.Find("one"), runtime_error);
    }
