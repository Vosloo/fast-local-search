#include "Instance.hpp"


Instance::Instance(Node** nodes, int size, std::string name)
{
    this->nodes = nodes;
    this->size = size;
    this->name = name;
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

std::string Instance::getName()
{
    return this->name;
}
