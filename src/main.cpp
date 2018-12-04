#include "../include/RBTree.hpp"
#include "../include/TreeInspector.hpp"

int main()
{

    RBTree<int> t;
    t.insert(10);
    t.insert(11);
    t.insert(20);
    t.insert(21);
    t.insert(3);
    t.insert(5);
    t.insert(15);

    int search_val = 55;
    auto result = t.search(search_val);

    std::cout << "search for elem "<< search_val <<", results:" << std::endl;
    if (result.first != nullptr)
        std::cout << "parent pointer points to: " << result.first -> get_key() << std::endl;
    if (result.second != nullptr)
        std::cout << "needle pointer points to: " << result.second -> get_key() << std::endl;


    TreeInspector inspector(t);
    t.remove(10);
    inspector.print_tree(t._head);
}
