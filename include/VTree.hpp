#ifndef __VTREE_HPP__
#define __VTREE_HPP__
#include "Node.hpp"

class VTree
{
    public:
        VTree();
        ~VTree();
        virtual void insert() = 0;
        virtual void remove() = 0;
        virtual void destroy_tree() = 0;
        virtual void search() = 0;
};
#endif
