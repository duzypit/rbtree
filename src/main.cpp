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
        std::vector<int> data_hibb = {6, 2,1,4,3,9,8,7,13,11,18};
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
    ASSERT_EQ(result -> get_parent(), nullptr);
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
/*
TEST_F(BSTTest, min_val)
{
    //to be reworked - is the argument really needed?
    auto min_pair = bst.find_min_val_node(bst.get_head());
    ASSERT_NE(min_pair.first, nullptr);
    EXPECT_EQ(min_pair.second -> get_key(), 5);

}
*/
/*
TEST_F(BSTTestRemove, remove)
{
    //TreeInspector i(bst);
    //Hibbard check
    //1. the deletion node has no subtree, right child
    hibbard.remove(5);
    auto needle = hibbard.search(2);
    EXPECT_EQ(needle.first -> get_key(), 6);
    EXPECT_EQ(needle.second -> get_key(), 2);
    EXPECT_EQ(needle.second -> get_right() -> get_key(), 4);

    //3. the deletion node has both childrens
    hibbard.remove(9);
    needle = hibbard.search(11);
    EXPECT_EQ(needle.second -> get_left() -> get_key(), 8);
    EXPECT_EQ(needle.second -> get_right() -> get_key(), 13);


    std::cout << "first!" <<std::endl;
    //4. remove the head
    hibbard.remove(6);
    std::cout << "first!" <<std::endl;

    auto head = hibbard.get_head();
    std::cout << "first!" <<std::endl;

    EXPECT_EQ(head -> get_key(), 8);
*/
/*    bst.remove(10);

    //3. the deletion node has 3 subtrees
    //bst.remove(40);
    //TreeInspector i(bst);
    //needle = bst.search(30);
    //EXPECT_EQ(needle.second -> get_right() -> get_key(), 38);

    //4. special case - remove of head node
    //bst.remove(50);
    //EXPECT_EQ(bst.get_head() -> get_key(), 90)
    //;
}
*/

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
