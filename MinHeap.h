//
// Created by trucnguyen on 11/19/19.
//

#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include <NodeBase.h>

class MinHeap
{
public:
    MinHeap();

    void insertNode(NodeHeap *p);
    NodeHeap* extractMin();
    NodeHeap* peekMin();
    void increaseKey(NodeHeap* p);
    bool isEmpty();
    void remove(NodeHeap* p);

    static void unitTest();
//private:
    std::vector<NodeHeap*> heap_;

    void heapify(uint idx);
    void swap(NodeHeap *&a, NodeHeap *&b);

    uint getParent(const uint &idx);
    uint getLeft(const uint &idx);
    uint getRight(const uint &idx);
};


#endif //MINHEAP_H
