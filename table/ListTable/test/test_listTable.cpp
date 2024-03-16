#include <gtest.h>
#include "ListTable.h"
using namespace std;

TEST(ListTable, Get_size) {
    ListTable<string, int> table;
    ASSERT_EQ(0, table.GetDataCount());
    ASSERT_NO_THROW(table.Insert("r1", 1234));
    ASSERT_EQ(1, table.GetDataCount());
}

TEST(ListTable, Is_empty) {
    ListTable<string, int> table;
    ASSERT_EQ(true, table.IsEmpty());
    ASSERT_NO_THROW(table.Insert("r1", 1234));
    ASSERT_EQ(false, table.IsEmpty());
}

TEST(ListTable, Is_full) {
    ListTable<string, int> table(1);
    ASSERT_EQ(false, table.IsFull());
    ASSERT_NO_THROW(table.Insert("r1", 1234));
    ASSERT_EQ(true, table.IsFull());
}

TEST(ListTable, Insert) {
    ListTable<string, int> table;
    ASSERT_NO_THROW(table.Insert("r1", 1234));
    ASSERT_EQ(1, table.GetDataCount());
}

TEST(ListTable, Delete_exist_record) {
    ListTable<string, int> table;
    ASSERT_NO_THROW(table.Insert("r1", 1234));
    ASSERT_NO_THROW(table.Delete("r1"));
    ASSERT_EQ(0, table.GetDataCount());
}

TEST(ListTable, Delete_not_exist_record) {
    ListTable<string, int> table;
    ASSERT_THROW(table.Delete("r1"), std::runtime_error);
}

TEST(ListTable, Find_exist_record) {
    ListTable<string, int> table;
    ASSERT_NO_THROW(table.Insert("r1", 1234));

    int* val;
    ASSERT_NO_THROW(val = table.Find("r1"));
    ASSERT_EQ(1234, *val);
}

TEST(ListTable, Find_not_exist_record) {
    ListTable<string, int> table;
    ASSERT_THROW(table.Find("r1"), std::runtime_error);
}

TEST(ListTable, Reset) {
    ListTable<string, int> table;
    ASSERT_EQ(0, table.Reset());
}

TEST(ListTable, Is_table_ended) {
    ListTable<string, int> table;
    ASSERT_NO_THROW(table.Insert("r1", 1234));
    ASSERT_EQ(false, table.IsTabEnded());
    ASSERT_NO_THROW(table.GoNext());
    ASSERT_EQ(true, table.IsTabEnded());
}

TEST(ListTable, Go_next) {
    ListTable<string, int> table;
    ASSERT_NO_THROW(table.Insert("r1", 1234));
    ASSERT_NO_THROW(table.Insert("r2", 1234));
    ASSERT_EQ(1, table.GoNext());
    ASSERT_EQ(0, table.GoNext());
}

TEST(ListTable, Get_key) {
    ListTable<string, int> table;
    ASSERT_NO_THROW(table.Insert("r1", 1234));
    ASSERT_EQ("r1", table.GetKey());
}

TEST(ListTable, Get_key_from_empty_table) {
    ListTable<string, int> table;
    ASSERT_THROW(table.GetKey(), std::runtime_error);
}

TEST(ListTable, Get_value) {
    ListTable<string, int> table;
    ASSERT_NO_THROW(table.Insert("r1", 1234));
    ASSERT_EQ(1234, table.GetValuePtr());
}

TEST(ListTable, Get_value_from_empty_table) {
    ListTable<string, int> table;
    ASSERT_THROW(table.GetValuePtr(), std::runtime_error);
}
