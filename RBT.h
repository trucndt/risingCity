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
    auto getKey();
    void setKey(uint key);
    void swapKey(NodeRBT* p);

    bool operator< (const NodeRBT &rhs);
    bool operator> (const NodeRBT &rhs);
    bool operator< (const uint& key);
    bool operator== (const uint& key);

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

    bool deleteNode(uint key);

    void deleteNode(NodeRBT* p);

    NodeRBT* searchNode(uint key);

private:
    NodeRBT *root_;

    /**
     * Insert node to the tree using the Binary Search Tree algorithm
     * @param p node to insert
     */
    void insertNodeBST(NodeRBT *p);

    /**
     * Find a node from the tree that is used to swap with the *node to delete* using the Binary Search Tree algorithm,
     * then swap the key and return the node that is either leaf or has a single child
     * @param p node to delete
     * @return the replace node
     */
    NodeRBT * getReplaceNodeForDeletion(NodeRBT *p);

    void deleteBlackNode(NodeRBT *p);

    void rotateRR(NodeRBT* y);
    void rotateLL(NodeRBT* y);
    void rotateRL(NodeRBT* p);
    void rotateLR(NodeRBT* p);
};




#endif //RBT_H
