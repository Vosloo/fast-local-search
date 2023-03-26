#include "Instance.hpp"


Instance::Instance(Node** nodes, int size)
{
    this->nodes = nodes;
    this->size = size;
}

Instance::~Instance()
{
    for (int i = 0; i < this->size; i++) {
        delete this->nodes[i];
    }
    delete[] this->nodes;
}

Node** Instance::getNodes()
{
    return this->nodes;
}

int Instance::getSize()
{
    return this->size;
}
