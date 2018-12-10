#ifndef __RBNODE_HPP__
#define __RBNODE_HPP__
#include "Node.hpp"

template <typename T>
class RBNode : public Node<T>
{
    enum class Color {black = false, red = true};

    Color _color = Color::red;

public:
    RBNode::Color get_color()
    {
        return _color;
    }

    void set_color(Color c)
    {
        _color = c;
    }

    bool is_red()
    {
        return (_color == Color::red) ? true : false;
    }

    void flip_color()
    {
        (_color == Color::red) ? _color = Color::black : _color = Color::red;
    }

};
#endif
