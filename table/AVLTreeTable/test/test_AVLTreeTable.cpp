#include <gtest/gtest.h>
#include "AVLTreeTable.h"
using namespace std;


TEST(AVLTreeTableTest, InsertionTest) {
    AVLTreeTable<int, std::string> avlTree;

    avlTree.Insert(10, "value10");
    avlTree.Insert(5, "value5");
    avlTree.Insert(15, "value15");
    avlTree.Insert(3, "value3");
    avlTree.Insert(7, "value7");

    EXPECT_NE(avlTree.FindNode(10), nullptr);
    EXPECT_NE(avlTree.FindNode(5), nullptr);
    EXPECT_NE(avlTree.FindNode(15), nullptr);
    EXPECT_NE(avlTree.FindNode(3), nullptr);
    EXPECT_NE(avlTree.FindNode(7), nullptr);

    EXPECT_EQ(*avlTree.Find(10), "value10");
    EXPECT_EQ(*avlTree.Find(5), "value5");
    EXPECT_EQ(*avlTree.Find(15), "value15");
    EXPECT_EQ(*avlTree.Find(3), "value3");
    EXPECT_EQ(*avlTree.Find(7), "value7");
}



//TEST(AVLTreeTableTest, DeletionTest) {
//    AVLTreeTable<int, string> avlTree;
//
//    avlTree.Insert(10, "Value 10");
//    avlTree.Insert(5, "Value 5");
//    avlTree.Insert(15, "Value 15");
//    avlTree.Insert(3, "Value 3");
//    avlTree.Insert(7, "Value 7");
//    avlTree.Insert(12, "Value 12");
//    avlTree.Insert(17, "Value 17");
//
//    avlTree.Delete(3);
//    avlTree.Delete(12);
//    avlTree.Delete(15);
//
//    EXPECT_EQ(avlTree.Find(3), nullptr);
//    EXPECT_EQ(avlTree.Find(12), nullptr);
//    EXPECT_EQ(avlTree.Find(15), nullptr);
//}
