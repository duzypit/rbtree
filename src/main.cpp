#include "../include/BSTree.hpp"
#include "../include/TreeInspector.hpp"
#include "../include/RBTree.hpp"
#include "../include/Node.hpp"
#include <vector>

int main()
{
/*
    // create tree
    BSTree<int> t;
    t.insert(50);
    t.insert(30);
    t.insert(70);
    t.insert(10);
    t.insert(5);
    t.insert(7);
    t.insert(40);
    t.insert(39);
    t.insert(38);
    t.insert(45);
    t.insert(80);
    t.insert(90);
    t.insert(75);

    TreeInspector inspector(t);

    //test: search
    int search_val = 15;
    auto result = t.search(search_val);

    std::cout << "search for elem "<< search_val <<", results:" << std::endl;
    if (result.first != nullptr)
        std::cout << "parent pointer points to: " << result.first -> get_key() << std::endl;
    if (result.second != nullptr)
        std::cout << "needle pointer points to: " << result.second -> get_key() << std::endl;

    //test: search for min val
    auto min = t.find_min_val_node(result.second);

    if (min.second != nullptr)
        std::cout << "Min elem value = " << min.second -> get_key() << std::endl;

    t.remove(7);
    inspector.print_tree(t);
    t.remove(10);
    inspector.print_tree(t);
    t.remove(70);
    inspector.print_tree(t);
    std::cout << "remove 50" << std::endl;
    t.remove(50);
    inspector.print_tree(t);

*/
    std::cout << "RBTree" << std::endl;

    RBTree<int> rbt;

    //firs test case
    //std::vector<int> data = {40,20, 60,80,50,10,30,25,2,1};
    //std::vector<int> data = {0, 5, 10, 7, 12, 8, 6, /*8, 9*/};
    //left - left case
    //std::vector<int> data = {15,20, 10, 5, 3,4};
    //left - right case
    //std::vector<int> data = {15, 20, 10, 5,8,9};
    //right - right case
    std::vector<int> data = {15, 20,10,30, 40,41};
    //right - left case
    //std::vector<int> data = {15,10,20,30,25,31};
    for( auto &a : data)
    {
        rbt.insert(a);
    }

    TreeInspector inspector(rbt);

}
