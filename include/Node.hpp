#pragma once

class Node
{
private:
    int id;
    int x;
    int y;
public:
    Node(int id, int x, int y);
    int getId();
    int getX();
    int getY();
};
