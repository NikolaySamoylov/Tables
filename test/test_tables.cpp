#pragma once
#include "tables.h"
#include <gtest.h>


TEST(UnorderedTable, can_create_empty_unordered_table)
{
  ASSERT_NO_THROW(UnorderedTable<> t);
}

TEST(UnorderedTable, can_create_copied_unordered_table)
{
    UnorderedTable<> t1;
    Monomial m(1, 111);
    Polynomial p(m);
    t1.insert(1, p);

    ASSERT_NO_THROW(UnorderedTable<> t2(t1));
}

TEST(UnorderedTable, can_insert_correctly)
{
    UnorderedTable<> t;
    Monomial m(1, 111);
    Polynomial p(m);

    ASSERT_NO_THROW(t.insert(1, p));
    EXPECT_EQ(1, t.get_size());
}

TEST(UnorderedTable, cant_insert_when_data_with_the_same_key_have_already_existed_in_the_table)
{
    UnorderedTable<> t;
    Monomial m1(1, 111);
    Monomial m2(2, 222);
    Polynomial p1(m1);
    Polynomial p2(m2);
    t.insert(1, p1);

    ASSERT_ANY_THROW(t.insert(1, p2));
}

TEST(UnorderedTable, can_erase_correctly)
{
    UnorderedTable<> t;
    Monomial m(1, 111);
    Polynomial p(m);
    t.insert(1, p);

    ASSERT_NO_THROW(t.erase(1));
    EXPECT_EQ(0, t.get_size());
}

TEST(UnorderedTable, cant_erase_when_data_with_such_key_does_not_exist_in_the_table)
{
    UnorderedTable<> t;
    Monomial m(1, 111);
    Polynomial p(m);
    t.insert(1, p);

    ASSERT_ANY_THROW(t.erase(2));
}

TEST(UnorderedTable, can_find_existing_data)
{
    UnorderedTable<> t;
    Monomial m(1, 111);
    Polynomial p(m);
    t.insert(1, p);
    std::pair<size_t, Polynomial> f;
    f.first = 1;
    f.second = p;

    EXPECT_EQ(f, t.find(1));
}

TEST(UnorderedTable, cant_find_nonexistent_data)
{
    UnorderedTable<> t;
    Monomial m(1, 111);
    Polynomial p(m);
    t.insert(1, p);

    ASSERT_ANY_THROW(t.find(2));
}


TEST(OrderedTable, can_create_empty_ordered_table)
{
    ASSERT_NO_THROW(OrderedTable<> t);
}

TEST(OrderedTable, can_create_copied_ordered_table)
{
    OrderedTable<> t1;
    Monomial m(1, 111);
    Polynomial p(m);
    t1.insert(1, p);

    ASSERT_NO_THROW(OrderedTable<> t2(t1));
}

TEST(OrderedTable, can_insert_correctly)
{
    OrderedTable<> t;
    Monomial m(1, 111);
    Polynomial p(m);

    ASSERT_NO_THROW(t.insert(1, p));
    EXPECT_EQ(1, t.get_size());
}

TEST(OrderedTable, cant_insert_when_data_with_the_same_key_have_already_existed_in_the_table)
{
    OrderedTable<> t;
    Monomial m1(1, 111);
    Monomial m2(2, 222);
    Polynomial p1(m1);
    Polynomial p2(m2);
    t.insert(1, p1);

    ASSERT_ANY_THROW(t.insert(1, p2));
}

TEST(OrderedTable, can_erase_correctly)
{
    OrderedTable<> t;
    Monomial m(1, 111);
    Polynomial p(m);
    t.insert(1, p);

    ASSERT_NO_THROW(t.erase(1));
    EXPECT_EQ(0, t.get_size());
}

TEST(OrderedTable, cant_erase_when_data_with_such_key_does_not_exist_in_the_table)
{
    OrderedTable<> t;
    Monomial m(1, 111);
    Polynomial p(m);
    t.insert(1, p);

    ASSERT_ANY_THROW(t.erase(2));
}

TEST(OrderedTable, can_find_existing_data)
{
    OrderedTable<> t;
    Monomial m(1, 111);
    Polynomial p(m);
    t.insert(1, p);
    std::pair<size_t, Polynomial> f;
    f.first = 1;
    f.second = p;

    EXPECT_EQ(f, t.find(1));
}

TEST(OrderedTable, cant_find_nonexistent_data)
{
    OrderedTable<> t;
    Monomial m(1, 111);
    Polynomial p(m);
    t.insert(1, p);

    ASSERT_ANY_THROW(t.find(2));
}


TEST(HashTable, can_create_empty_hash_table)
{
    ASSERT_NO_THROW(HashTable<> h(2));
}

TEST(HashTable, can_create_copied_hash_table)
{
    HashTable<> h1(2);
    Monomial m(1, 111);
    Polynomial p(m);
    h1.insert(1, p);

    ASSERT_NO_THROW(HashTable<> h2(h1));
}

TEST(HashTable, can_insert_correctly)
{
    HashTable<> h(2);
    Monomial m(1, 111);
    Polynomial p(m);

    ASSERT_NO_THROW(h.insert(1, p));
    EXPECT_EQ(1, h.get_size());
}

TEST(HashTable, cant_insert_when_data_with_the_same_key_have_already_existed_in_the_table)
{
    HashTable<> h(2);
    Monomial m1(1, 111);
    Monomial m2(2, 222);
    Polynomial p1(m1);
    Polynomial p2(m2);
    h.insert(1, p1);

    ASSERT_ANY_THROW(h.insert(1, p2));
}

TEST(HashTable, can_erase_correctly)
{
    HashTable<> h(2);
    Monomial m(1, 111);
    Polynomial p(m);
    h.insert(1, p);

    ASSERT_NO_THROW(h.erase(1));
    EXPECT_EQ(0, h.get_size());
}

TEST(HashTable, cant_erase_when_data_with_such_key_does_not_exist_in_the_table)
{
    HashTable<> h(2);
    Monomial m(1, 111);
    Polynomial p(m);
    h.insert(1, p);

    ASSERT_ANY_THROW(h.erase(2));
}

TEST(HashTable, can_find_existing_data)
{
    HashTable<> h(2);
    Monomial m(1, 111);
    Polynomial p(m);
    h.insert(1, p);
    std::pair<size_t, Polynomial> f;
    f.first = 1;
    f.second = p;

    EXPECT_EQ(f, h.find(1));
}

TEST(HashTable, cant_find_nonexistent_data)
{
    HashTable<> h(2);
    Monomial m(1, 111);
    Polynomial p(m);
    h.insert(1, p);

    ASSERT_ANY_THROW(h.find(2));
}