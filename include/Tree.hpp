#ifndef __TREE_HPP__
#define __TREE_HPP__



class Tree
{
    public:
        Tree();
        ~Tree();
        virtual void insert() = 0;
        virtual void remove() = 0;
        virtual void destroy() = 0;
};
#endif
