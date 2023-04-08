#include "Node.hpp"

#include <iostream>

Node::Node(int id, double x, double y)
{
    this->id = id;
    this->x = x;
    this->y = y;
}

int Node::getId()
{
    return this->id;
}

double Node::getX()
{
    return this->x;
}

double Node::getY()
{
    return this->y;
}
