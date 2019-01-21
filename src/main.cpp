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
    ASSERT_EQ(result.first, nullptr);
    ASSERT_EQ(result.second, nullptr);

    needle = 90;
    result = bst.search(needle);
    ASSERT_NE(result.first, nullptr);
    EXPECT_EQ(result.second -> get_key(), needle);

    needle = 50;
    result = bst.search(needle);
    std::cout << "value of result.first (should be nullptr): " << result.first -> get_key() << std::endl;
    ASSERT_EQ(result.first, nullptr);
    EXPECT_EQ(result.second -> get_key(), needle);
}

TEST_F(BSTTest, min_val)
{
    //to be reworked - is the argument really needed?
    auto min_pair = bst.find_min_val_node(bst.get_head());
    ASSERT_NE(min_pair.first, nullptr);
    EXPECT_EQ(min_pair.second -> get_key(), 5);

}

TEST_F(BSTTest, remove)
{
    bst.remove(7);

    bst.remove(10);

    bst.remove(70);

    bst.remove(50);

}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


/*
int main()
{
    t.remove(7);
    inspector.print_tree(t);
    t.remove(10);
    inspector.print_tree(t);
    t.remove(70);
    inspector.print_tree(t);
    std::cout << "remove 50" << std::endl;
    t.remove(50);
    inspector.print_tree(t);


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
