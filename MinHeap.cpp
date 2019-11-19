//
// Created by trucnguyen on 11/19/19.
//

#include "MinHeap.h"
MinHeap::MinHeap()
{
    heap_.reserve(2000);
}

void MinHeap::insertNode(Node *p)
{
    heap_.push_back(p);

    uint idx = heap_.size() - 1;

    // pushing up
    while (idx != 0 && *heap_[getParent(idx)] > *heap_[idx])
    {
        heap_[getParent(idx)]->swapData(heap_[idx]);
        idx = getParent(idx);
    }
}

Node *MinHeap::extractMin()
{
    Node* res = heap_[0];

    heap_[0] = heap_.back();
    heap_.pop_back();

    heapify(0);

    return res;
}

void MinHeap::heapify(uint idx)
{
    auto l = getLeft(idx);
    auto r = getRight(idx);
    auto min = idx;
    auto n = heap_.size();

    if (l < n && *heap_[l] < *heap_[min])
        min = l;

    if (r < n && *heap_[r] < *heap_[min])
        min = r;

    if (min != idx)
    {
        heap_[idx]->swapData(heap_[min]);
        heapify(min);
    }
}

Node *MinHeap::peekMin()
{
    return heap_[0];
}

uint MinHeap::getParent(const uint &idx)
{
    return (idx - 1) / 2;
}
uint MinHeap::getLeft(const uint &idx)
{
    return idx * 2 + 1;
}
uint MinHeap::getRight(const uint &idx)
{
    return idx * 2 + 2;
}

void MinHeap::unitTest()
{
    MinHeap *s = new MinHeap();
    s->insertNode(new Node(9, 0));
    s->insertNode(new Node(8, 0));
    s->insertNode(new Node(7, 0));
    s->insertNode(new Node(2, 0));
    s->insertNode(new Node(6, 0));
    s->insertNode(new Node(1, 0));
    s->insertNode(new Node(3, 0));
//    s->insertNode(new Node(4, 1));
//    s->insertNode(new Node(10, 0));
//    s->insertNode(new Node(11, 0));
//    s->insertNode(new Node(12, 0));
//    s->insertNode(new Node(0, 0));

    s->extractMin();
}
