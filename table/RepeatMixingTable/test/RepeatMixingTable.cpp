#include <gtest/gtest.h>
#include "RepeatMixingTable.h"
using namespace std;

TEST(RepeatMixingTable, InsertAndFind) {
    RepeatMixingTable<string, int> table;
    table.Insert("one", 1);
    ASSERT_EQ(*table.Find("one"), 1);
}

TEST(RepeatMixingTable, Delete) {
    RepeatMixingTable<string, int> table;
    table.Insert("two", 2);
    table.Delete("two");
    ASSERT_THROW(table.Find("two"), std::runtime_error);
}

TEST(RepeatMixingTable, FindNonExistentKey) {
    RepeatMixingTable<string, int> table;
    ASSERT_THROW(table.Find("one"), std::runtime_error);
}

TEST(RepeatMixingTable, InsertFullTable) {
    RepeatMixingTable<string, int> table(3);
    table.Insert("one", 1);
    table.Insert("two", 2);
    table.Insert("three", 3);
    ASSERT_THROW(table.Insert("four", 4), std::runtime_error);
}
