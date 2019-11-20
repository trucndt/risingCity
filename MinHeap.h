//
// Created by trucnguyen on 11/19/19.
//

#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include <Node.h>

class Node;

class MinHeap
{
public:
    MinHeap();

    void insertNode(Node* p);
    Node* extractMin();
    Node* peekMin();
    void increaseKey(Node* p);

    static void unitTest();
private:
    std::vector<Node*> heap_;

    void heapify(uint idx);
    void swap(Node *&a, Node *&b);

    uint getParent(const uint &idx);
    uint getLeft(const uint &idx);
    uint getRight(const uint &idx);
};


#endif //MINHEAP_H
