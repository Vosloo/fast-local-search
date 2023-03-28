#include "Node.hpp"

#include <iostream>

Node::Node(int id, int x, int y)
{
    this->id = id;
    this->x = x;
    this->y = y;
}

int Node::getId()
{
    return this->id;
}

int Node::getX()
{
    return this->x;
}

int Node::getY()
{
    return this->y;
}
