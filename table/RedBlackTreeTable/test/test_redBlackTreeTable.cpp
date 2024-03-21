#include <gtest/gtest.h>
#include "RedBlackTreeTable.h"
using namespace std;

TEST(RedBlackTreeTableTest, InsertAndFind) {
    RedBlackTreeTable<int, std::string> table;

    table.Insert(1, "One");
    table.Insert(2, "Two");
    table.Insert(3, "Three");

    EXPECT_TRUE(table.FindNode(1) != nullptr);
    EXPECT_TRUE(table.FindNode(2) != nullptr);
    EXPECT_TRUE(table.FindNode(3) != nullptr);

    EXPECT_EQ(table.FindNode(1)->key, 1);
    EXPECT_EQ(table.FindNode(2)->key, 2);
    EXPECT_EQ(table.FindNode(3)->key, 3);

    EXPECT_EQ(table.FindNode(1)->value, "One");
    EXPECT_EQ(table.FindNode(2)->value, "Two");
    EXPECT_EQ(table.FindNode(3)->value, "Three");

    EXPECT_TRUE(table.FindNode(4) == nullptr);
}
