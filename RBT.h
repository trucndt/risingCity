//
// Created by trucnguyen on 10/31/19.
//

#ifndef RBT_H
#define RBT_H

#include <cstdint>
#include <Node.h>

class RBT;

enum COLOR
{
    RED,
    BLACK
};

class NodeRBT : public Node
{
private:
    uint8_t mColor;
    NodeRBT *mLeft = nullptr, *mRight = nullptr, *mParent = nullptr;

public:
    NodeRBT(uint buildingNums, ulong totalTime);

    bool operator< (const NodeRBT& rhs);
    bool operator> (const NodeRBT& rhs);

friend RBT;
};

class RBT
{
public:
    RBT()
    {
        root = nullptr;
    }

    void insertNode(NodeRBT* p);

    void deleteNode(NodeRBT* p);

private:
    NodeRBT *root;
};




#endif //RBT_H
