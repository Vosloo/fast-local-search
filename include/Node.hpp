#pragma once

class Node
{
private:
    int id;
    double x;
    double y;
public:
    Node(int id, double x, double y);
    int getId();
    double getX();
    double getY();
};
