#include "../include/RBTree.hpp"
#include "../include/TreeInspector.hpp"

int main()
{

    RBTree<int> t;
    t.insert(6);
    t.insert(2);
    t.insert(1);
    t.insert(11);
    t.insert(8);
    t.insert(15);
    t.insert(13);
    t.insert(11);
    t.insert(18);

    int search_val = 55;
    auto result = t.search(search_val);

    std::cout << "search for elem "<< search_val <<", results:" << std::endl;
    if (result.first != nullptr)
        std::cout << "parent pointer points to: " << result.first -> get_key() << std::endl;
    if (result.second != nullptr)
        std::cout << "needle pointer points to: " << result.second -> get_key() << std::endl;


//    t.remove(10);
//    inspector.print_tree(t._head);
//
    auto min = t.find_min_val_node(t.get_head());

    std::cout << "Min elem value = " << min.second -> get_key() << std::endl;

    t.remove(20);

    TreeInspector inspector(t);
}
