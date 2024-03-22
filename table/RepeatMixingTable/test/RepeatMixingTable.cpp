#include <gtest/gtest.h>
#include "RepeatMixingTable.h"
using namespace std;

TEST(RepeatMixingTable, InsertAndFind) {
    RepeatMixingTable<int, string> table;
    table.Insert(1, "one");
    ASSERT_EQ(*table.Find(1), "one");
}

TEST(RepeatMixingTable, Delete) {
    RepeatMixingTable<int, string> table;
    table.Insert(2, "two");
    table.Delete(2);
    ASSERT_THROW(table.Find(2), std::runtime_error);
}

TEST(RepeatMixingTable, FindNonExistentKey) {
    RepeatMixingTable<int, string> table;
    ASSERT_THROW(table.Find(100), std::runtime_error);
}

TEST(RepeatMixingTable, InsertFullTable) {
    RepeatMixingTable<int, string> table(3);
    table.Insert(1, "one");
    table.Insert(2, "two");
    table.Insert(3, "three");
    ASSERT_THROW(table.Insert(4, "four"), std::runtime_error);
}
