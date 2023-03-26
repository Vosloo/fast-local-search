#pragma once

#include "Node.hpp"


class Instance
{
private:
    Node** nodes;
    int size;
public:
    Instance(Node** nodes, int size);
    Node** getNodes();
    int getSize();
    ~Instance();
};
