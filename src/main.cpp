#include "../include/BSTree.hpp"
#include "../include/TreeInspector.hpp"

int main()
{

    // create tree
    BSTree<int> t;
    t.insert(6);
    t.insert(2);
    t.insert(1);
    t.insert(9);
    t.insert(8);
    t.insert(15);
    t.insert(13);
    t.insert(11);
    t.insert(18);

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

    std::cout << "Min elem value = " << min.second -> get_key() << std::endl;

    t.remove(15);

    inspector.print_tree(t);
}
