#pragma once

#include <iostream>

#include "Node.hpp"


class Instance
{
private:
    Node** nodes;
    int size;
    std::string name;
public:
    Instance(Node** nodes, int size, std::string name);
    ~Instance();
    Node** getNodes();
    int getSize();
    std::string getName();
};
