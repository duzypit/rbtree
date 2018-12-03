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

    auto result = t.search(10);

    TreeInspector inspector(t);

}
