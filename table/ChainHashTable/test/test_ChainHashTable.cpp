    #include <gtest/gtest.h>
    #include "ChainHashTable.h"
    using namespace std;

    TEST(ChainHashTable, InsertAndFind) {
        ChainHashTable<int, string> hashTable;
        int key = 1;
        string value = "test";
        hashTable.Insert(key, value);
        ASSERT_EQ(*hashTable.Find(key), value);
    }

    TEST(ChainHashTable, Delete) {
        ChainHashTable<int, string> hashTable;
        hashTable.Insert(5, "test5");
        hashTable.Delete(5);
        ASSERT_THROW(hashTable.Find(5), runtime_error);
    }

    TEST(ChainHashTable, FindNonExistentKey) {
        ChainHashTable<int, string> hashTable;
        ASSERT_THROW(hashTable.Find(100), runtime_error);
    }
