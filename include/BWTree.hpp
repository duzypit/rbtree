#ifndef __BWTREE_HPP__
#define __BWTREE_HPP__
#include "Tree.hpp"

class BWTree : public Tree
{
    public:
        void insert() override;
        void remove() override;
        void destroy() override;
};
#endif


