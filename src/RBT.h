//
// Created by trucnguyen on 10/31/19.
//

#ifndef RBT_H
#define RBT_H

#include <cstdint>
#include <NodeBase.h>
#include <fstream>

class NodeRBT;

/// A red-black tree data structure
class RBT
{
public:
    /**
     * Default constructor of RBT
     */
    RBT()
    {
        root_ = nullptr;
    }

    /**
     * Insert a node to this tree
     * @param p a NodeRBT to insert
     */
    void insertNode(NodeRBT* p);

    /**
     * Delete a node from this tree by its key
     * @param key the key to delete
     * @return true if the key is found, false otherwise
     */
    bool deleteNode(uint key);

    /**
     * Delete a node from this tree
     * @param y the NodeRBT to delete
     */
    void deleteNode(NodeRBT* y);

    /**
     * Search for the node using its key
     * @param key the key to search
     * @return null if not found, otherwise return the node
     */
    NodeRBT* searchNode(uint key);

    /**
     * Getter for the root of the tree
     * @return
     */
    NodeRBT *getRoot() const;

    /**
     * Print the list of nodes in which its key lie within a specific range [left, right]
     * @param root the root of a RBT
     * @param left the left value
     * @param right the right value
     * @param out the output stream
     * @param comma must be false
     */
    static void printRange(NodeRBT *root, const uint &left, const uint &right, std::ostream &out, bool &comma);

    /**
     * Some unit tests for RBT
     */
    static void unitTest();

private:
    /// Root of the tree
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

    /**
     * Procedure to delete a black leaf
     * @param y the black leaf
     */
    void deleteBlackLeaf(NodeRBT *y);

    /**
     * Delete a leaf node in the tree, regardless of color
     * @param p the leaf node
     */
    void deleteLeafNode(NodeRBT *p);

    /**
     * RR rotation
     * @param y the start node
     */
    void rotateRR(NodeRBT* y);

    /**
     * LL rotation
     * @param y the start node
     */
    void rotateLL(NodeRBT* y);

    /**
     * RL rotation
     * @param p the start node
     */
    void rotateRL(NodeRBT* p);

    /**
     * LR rotation
     * @param p the start node
     */
    void rotateLR(NodeRBT* p);
};




#endif //RBT_H
