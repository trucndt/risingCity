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
    uint8_t color_;
    NodeRBT *left_ = nullptr, *right_ = nullptr, *parent_ = nullptr;

public:
    NodeRBT(uint buildingNums, ulong totalTime);

    NodeRBT* getUncleNode();

    bool operator< (const NodeRBT &rhs);
    bool operator> (const NodeRBT &rhs);

friend RBT;
};

class RBT
{
public:
    RBT()
    {
        root_ = nullptr;
    }

    /**
     * Insert a node to this tree
     * @param p a NodeRBT to insert
     */
    void insertNode(NodeRBT* p);

    void deleteNode(NodeRBT* p);

private:
    NodeRBT *root_;

    /**
     * Insert node to the tree using the Binary Search Tree algorithm
     * @param p node to insert
     */
    void insertNodeBST(NodeRBT *p);

    void rotateRR(NodeRBT* y);
    void rotateLL(NodeRBT* y);
    void rotateRL(NodeRBT* p);
    void rotateLR(NodeRBT* p);
};




#endif //RBT_H
