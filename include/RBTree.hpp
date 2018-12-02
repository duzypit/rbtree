#ifndef __BWTREE_HPP__
#define __BWTREE_HPP__
#include "VTree.hpp"
#include "Node.hpp"

template<typename T>
class RBTree
{
    std::shared_ptr<Node<T>> head = nullptr;

public:
    RBTree();
    RBTree(T value);
    ~RBTree();
    void insert(T i);
    void remove(T r);
    void destroy_tree();
    Node<T>* search(T value);
};
#endif


