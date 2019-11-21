//
// Created by trucnguyen on 11/19/19.
//

#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include <NodeBase.h>

class NodeHeap;

/// A min heap data structure
class MinHeap
{
public:
    /**
     * Constructor for MinHeap
     */
    MinHeap();

    /**
     * Insert a node of type NodeHeap to the heap
     * @param p node to insert
     */
    void insertNode(NodeHeap *p);

    /**
     * Extract the min/root of the heap, the root is then removed from the structure. Note that it doesn't delete the
     * object pointed by the root
     * @return root of the heap
     */
    NodeHeap* extractMin();

    /**
     * Get the min/root of the heap, the structure is unchanged
     * @return root of the heap
     */
    NodeHeap* peekMin();

    /**
     * Update the structure to increase the key of a node in the heap
     * @param p the node with the **increased** key
     */
    void increaseKey(NodeHeap* p);

    /**
     * Check if the heap is empty
     * @return true if empty, false otherwise
     */
    bool isEmpty();

    /**
     * Remove a node from the heap
     * @param p node to remove
     */
    void remove(NodeHeap* p);

    /**
     * Run some unit tests
     */
    static void unitTest();

private:
    /// Array to store the node in heap
    std::vector<NodeHeap*> heap_;

    /**
     * Perform heapify on the heap starting from an index
     * @param idx index
     */
    void heapify(uint idx);

    /**
     * Swap two nodes in the heap
     * @param a first node
     * @param b second node
     */
    void swap(NodeHeap *&a, NodeHeap *&b);

    /**
     * Get the index of the parent node
     * @param idx index of the current node
     * @return index of the parent node
     */
    uint getParent(const uint &idx);

    /**
     * Get the index of the left child
     * @param idx index of the current node
     * @return index of the left child
     */
    uint getLeft(const uint &idx);

    /**
     * Get the index of the right child
     * @param idx index of the current node
     * @return index of the right child
     */
    uint getRight(const uint &idx);
};


#endif //MINHEAP_H
