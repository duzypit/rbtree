#include "../include/BSTree.hpp"
#include "../include/TreeInspector.hpp"
#include "../include/RBTree.hpp"
#include "../include/Node.hpp"
#include <vector>
#include "gtest/gtest.h"

class BSTTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        std::vector<int> data = {50,30,70,10,5,7,40,39,38,45,80,90,75};
        for (const auto & d : data)
        {
            bst.insert(d);
        }

    }

    BSTree<int> bst;
};

class BSTTestRemove : public ::testing::Test
{
protected:
    void SetUp() override
    {
        std::vector<int> data_hibb = {6,2,1,4,3,9,8,7,13,11,18};
        for(const auto& d : data_hibb)
        {
            hibbard.insert(d);
        }

    }
    BSTree<int> hibbard;
};

TEST_F(BSTTest, insertion)
{
    auto head = bst.get_head();
    //check head
    ASSERT_EQ(head -> get_key(), 50);
    //check right child
    ASSERT_EQ(head -> get_right() -> get_key(), 70);
}

TEST_F(BSTTest, search)
{
    int needle = 15;
    auto result = bst.search(needle);
    ASSERT_EQ(result, nullptr);

    needle = 90;
    result = bst.search(needle);
    ASSERT_NE(result -> get_parent(), nullptr);
    EXPECT_EQ(result -> get_key(), needle);

    needle = 50;
    result = bst.search(needle);
    ASSERT_EQ(result -> get_parent(), nullptr);
    EXPECT_EQ(result -> get_key(), needle);
}

TEST_F(BSTTest, min_val)
{
    //to be reworked - is the argument really needed?
    auto min = bst.find_min_val_node(bst.get_head());
    ASSERT_NE(min -> get_parent(), nullptr);
    EXPECT_EQ(min -> get_key(), 5);

}


TEST_F(BSTTestRemove, remove_left_leaf)
{

    //Hibbard algo check
    //1. the deletion node has no subtree, left child
    hibbard.remove(3);
    auto needle = hibbard.search(4);
    EXPECT_EQ(needle -> get_left(), nullptr);
}

TEST_F(BSTTestRemove, remove_right_leaf)
{

    //Hibbard algo check
    //1. the deletion node has no subtree, left child
    hibbard.remove(18);
    auto needle = hibbard.search(13);
    EXPECT_EQ(needle -> get_right(), nullptr);
}


TEST_F(BSTTestRemove, delete_subtree_both_ch)
{
    //3. the deletion node has both childrens
    hibbard.remove(9);
    auto needle = hibbard.search(11);
    EXPECT_EQ(needle -> get_left() -> get_key(), 8);
    EXPECT_EQ(needle -> get_right() -> get_key(), 13);
}

TEST_F(BSTTestRemove, delete_head)
{

    //4. remove the head
    hibbard.remove(6);
    auto head = hibbard.get_head();
    EXPECT_EQ(head -> get_key(), 7);
    EXPECT_EQ(head -> get_left() -> get_key(), 2);
    EXPECT_EQ(head -> get_right() -> get_key(), 9);
}

class RBTreeTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        std::vector<int> data = {10,7,3};
        for(const auto& d : data)
        {
            rbt.insert(d);
        }

    }
    RBTree<int> rbt;
};



TEST_F(RBTreeTest, insertion_recolor)
{
    //TreeInspector i(rbt);


    auto head = rbt.get_head();

    EXPECT_EQ(head -> is_red(), false);
    EXPECT_EQ(head -> get_right() -> is_red(), false);
    EXPECT_EQ(head -> get_left() -> is_red(), false);

}

TEST_F(RBTreeTest, insertion_right_left)
{
    rbt.insert(15);
    rbt.insert(14);

    auto head = rbt.get_head();
    EXPECT_EQ(head -> get_right() -> get_key(), 14);
    EXPECT_EQ(head -> get_right() -> is_red(), false);
}

TEST_F(RBTreeTest, insertion_right_right)
{
    rbt.insert(15);
    rbt.insert(16);

    auto head = rbt.get_head();
    EXPECT_EQ(head -> get_right() -> get_key(), 14);
    EXPECT_EQ(head -> get_right() -> is_red(), false);
}

TEST_F(RBTreeTest, insertion_left_right)
{
    rbt.insert(1);
    rbt.insert(2);

    auto head = rbt.get_head();
    EXPECT_EQ(head -> get_left() -> get_key(), 2);
    EXPECT_EQ(head -> get_left() -> is_red(), false);

}

TEST_F(RBTreeTest, insertion_left_left)
{
    rbt.insert(1);
    rbt.insert(0);

    auto head = rbt.get_head();
    EXPECT_EQ(head -> get_left() -> get_key(), 3);
    EXPECT_EQ(head -> get_left() -> is_red(), false);
}

class RBTreeDelete : public ::testing::Test
{
protected:
    void SetUp() override
    {
        std::vector<int> data = {30, 20, 40, 50};
        for(const auto& d : data)
        {
            rbt.insert(d);
        }

    }
    RBTree<int> rbt;
};

TEST_F(RBTreeDelete, simple_u_or_v_is_red)
{
    rbt.insert(10);
    rbt.remove(20);

    auto head = rbt.get_head();
    EXPECT_EQ(head -> get_left() -> get_key(), 10);
    EXPECT_EQ(head -> get_left() -> is_red(), false);
}
/**/
TEST_F(RBTreeDelete, both_black_left_left)
{
/*
    rbt.insert(10);
    rbt.remove(20);

    auto head = rbt.get_head();
    EXPECT_EQ(head -> get_left() -> get_key(), 10);
    EXPECT_EQ(head -> get_left() -> is_red(), false);
*/
}

TEST_F(RBTreeDelete, both_black_left_right)
{
/*    rbt.insert(10);
    rbt.remove(20);

    auto head = rbt.get_head();
    EXPECT_EQ(head -> get_left() -> get_key(), 10);
    EXPECT_EQ(head -> get_left() -> is_red(), false);
*/
}

TEST_F(RBTreeDelete, both_black_right_left)
{
    rbt.insert(35);
    rbt.remove(50);
    rbt.remove(20);

    auto head = rbt.get_head();
    EXPECT_EQ(head -> get_left() -> get_key(), 30);
    EXPECT_EQ(head -> get_left() -> is_red(), false);
    EXPECT_EQ(head -> get_left() -> is_leaf(), true);

    EXPECT_EQ(head -> get_right() -> get_key(), 40);
    EXPECT_EQ(head -> get_right() -> is_red(), false);
    EXPECT_EQ(head -> get_right() -> is_leaf(), true);

}

TEST_F(RBTreeDelete, both_black_right_right)
{
    rbt.insert(35);
    rbt.remove(20);

    auto head = rbt.get_head();
    EXPECT_EQ(head -> get_left() -> get_key(), 10);
    EXPECT_EQ(head -> get_left() -> is_red(), false);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


/*
int main()
{
    std::cout << "RBTree" << std::endl;

    RBTree<int> rbt;

    //firs test case
    std::vector<int> data = {10, 85, 15, 70, 20, 60, 30, 50, 65, 80, 90, 40, 5, 55};
    //std::vector<int> data = {40,20, 60,80,50,10,30,25,2,1};
    //std::vector<int> data = {0, 5, 10, 7, 12, 8, 6, 8, 9};
    //left - left case
    //std::vector<int> data = {15,20, 10, 5, 3,4}/;
    //left - right case
    //std::vector<int> data = {15, 20, 10, 5,8,9};
    //right - right case
    //std::vector<int> data = {15, 20,10,30, 40,41};
    //right - left case
    //std::vector<int> data = {15,10,20,30,25,31};
    for( auto &a : data)
    {
        rbt.insert(a);
    }

    TreeInspector inspector(rbt);

}
*/
