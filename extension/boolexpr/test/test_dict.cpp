/*
** Filename: test_dict.cpp
**
** Test the BX_Dict data type.
*/


#include "boolexprtest.hpp"


class BX_Dict_Test: public BoolExpr_Test {};


TEST_F(BX_Dict_Test, MinimumSize)
{
    struct BX_Dict *dict = BX_Dict_New();
    EXPECT_EQ(dict->_pridx, 4);

    BX_Dict_Del(dict);
}


TEST_F(BX_Dict_Test, BasicReadWrite)
{
    struct BX_Dict *dict = BX_Dict_New();

    BX_Dict_Insert(dict, xs[0], &BX_Zero);
    EXPECT_EQ(BX_Dict_Search(dict, xs[0]), &BX_Zero);
    EXPECT_TRUE(BX_Dict_Contains(dict, xs[0]));
    EXPECT_EQ(dict->length, 1);

    BX_Dict_Insert(dict, xs[1], &BX_One);
    EXPECT_EQ(BX_Dict_Search(dict, xs[1]), &BX_One);
    EXPECT_TRUE(BX_Dict_Contains(dict, xs[1]));
    EXPECT_EQ(dict->length, 2);

    // Over-write
    BX_Dict_Insert(dict, xs[0], &BX_One);
    EXPECT_EQ(BX_Dict_Search(dict, xs[0]), &BX_One);
    EXPECT_EQ(dict->length, 2);

    // Not found
    EXPECT_EQ(BX_Dict_Search(dict, xs[2]), (BoolExpr *) NULL);
    EXPECT_FALSE(BX_Dict_Contains(dict, xs[2]));

    BX_Dict_Del(dict);
}


TEST_F(BX_Dict_Test, Collision)
{
    struct BX_Dict *dict = BX_Dict_New();

    // Create a few collisions
    for (int i = 0; i < 64; ++i)
        BX_Dict_Insert(dict, xs[i], xns[i]);

    // Check Contains/Search on collisions
    for (int i = 0; i < 64; ++i)
        EXPECT_TRUE(BX_Dict_Contains(dict, xs[i]));
    for (int i = 0; i < 64; ++i)
        EXPECT_EQ(BX_Dict_Search(dict, xs[i]), xns[i]);

    BX_Dict_Del(dict);
}


TEST_F(BX_Dict_Test, Resize)
{
    struct BX_Dict *dict = BX_Dict_New();

    for (int i = 0; i < 512; ++i)
        BX_Dict_Insert(dict, xns[i], xs[i]);

    BX_Dict_Del(dict);
}


TEST_F(BX_Dict_Test, Removal)
{
    struct BX_Dict *dict = BX_Dict_New();
    int length = 0;

    for (int i = 0; i < 32; ++i) {
        BX_Dict_Insert(dict, xns[i], xs[i]);
        EXPECT_EQ(dict->length, ++length);
    }

    // Invalid deletion
    EXPECT_EQ(BX_Dict_Remove(dict, xs[0]), false);

    for (int i = 0; i < 32; ++i) {
        BX_Dict_Remove(dict, xns[i]);
        EXPECT_EQ(dict->length, --length);
    }

    for (int i = 0; i < 32; ++i) {
        BX_Dict_Insert(dict, xns[i], xs[i]);
        EXPECT_EQ(dict->length, ++length);
    }
    for (int i = 0; i < 32; ++i) {
        BX_Dict_Remove(dict, xns[i]);
        EXPECT_EQ(dict->length, --length);
    }

    for (int i = 0; i < 32; ++i) {
        BX_Dict_Insert(dict, xns[i], xs[i]);
        EXPECT_EQ(dict->length, ++length);
    }

    for (int i = 0; i < 32; ++i) {
        BX_Dict_Remove(dict, xns[i]);
        EXPECT_EQ(dict->length, --length);
    }

    BX_Dict_Del(dict);
}


TEST_F(BX_Dict_Test, Clear)
{
    struct BX_Dict *dict = BX_Dict_New();
    int length = 0;

    for (int i = 0; i < 32; ++i) {
        BX_Dict_Insert(dict, xns[i], xs[i]);
        EXPECT_EQ(dict->length, ++length);
    }

    BX_Dict_Clear(dict);
    EXPECT_EQ(dict->length, 0);

    BX_Dict_Del(dict);
}

