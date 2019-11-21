//
// Created by trucnguyen on 11/19/19.
//

#include "MinHeap.h"

MinHeap::MinHeap()
{
    heap_.reserve(2000);
}

void MinHeap::insertNode(NodeHeap *p)
{
    heap_.push_back(p);

    uint idx = heap_.size() - 1;
    p->heapPos_ = idx;

    // pushing up
    while (idx != 0 && *heap_[getParent(idx)] > *heap_[idx])
    {
        swap(heap_[getParent(idx)], heap_[idx]);
        idx = getParent(idx);
    }
}

NodeHeap *MinHeap::extractMin()
{
    NodeHeap* res = heap_[0];

    swap(heap_[0], heap_.back());
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
        swap(heap_[idx],heap_[min]);
        heapify(min);
    }
}

NodeHeap *MinHeap::peekMin()
{
    return heap_[0];
}

void MinHeap::increaseKey(NodeHeap *p)
{
    heapify(p->heapPos_);
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
//    s->insertNode(new NodeHeap(9, 0));
//    s->insertNode(new NodeHeap(8, 0));
//    s->insertNode(new NodeHeap(7, 0));
//    s->insertNode(new NodeHeap(2, 0));
//    s->insertNode(new NodeHeap(6, 0));
//    NodeHeap *p = new NodeHeap(1, 0);
//    s->insertNode(p);
//    s->insertNode(new NodeHeap(3, 0));
//    s->insertNode(new NodeHeap(4, 1));
//    s->insertNode(new NodeHeap(10, 0));
//    s->insertNode(new NodeHeap(11, 0));
//    s->insertNode(new NodeHeap(12, 0));
//    s->insertNode(new NodeHeap(0, 0));

//    p->addExecutedTime(1);
//    s->increaseKey(p);
//    s->remove(p);
}

void MinHeap::swap(NodeHeap *&a, NodeHeap *&b)
{
    // Swap pointer
    NodeHeap *p = a;
    a = b;
    b = p;

    // Swap pos
    int tmp = a->heapPos_;
    a->heapPos_ = b->heapPos_;
    b->heapPos_ = tmp;
}

bool MinHeap::isEmpty()
{
    return heap_.empty();
}

void MinHeap::remove(NodeHeap *p)
{
    int pos = p->heapPos_;
    swap(heap_[pos], heap_.back());
    heap_.pop_back();

    if (*heap_[pos] > *heap_[getParent(pos)])
    {
        heapify(pos);
        return;
    }

    while (pos != 0 && *heap_[getParent(pos)] > *heap_[pos])
    {
        swap(heap_[getParent(pos)], heap_[pos]);
        pos = getParent(pos);
    }
}
