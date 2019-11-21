//
// Created by trucnguyen on 10/31/19.
//

#ifndef NODEBASE_H
#define NODEBASE_H

#include <cstdint>
#include <sys/types.h>
#include <RBT.h>
#include <MinHeap.h>

class RBT;
class MinHeap;

class NodeBase
{
public:
    NodeBase(uint buildingNums, ulong totalTime);

    virtual void addExecutedTime(ulong addTime);
    virtual void swapData(NodeBase* p);
    virtual ulong getKey() = 0;

protected:
    /// buildingNums, executed_time, total_time
    struct Data
    {
        uint buildingNums;
        ulong executedTime;
        ulong totalTime;
    } data_;

public:
    const Data &getData() const;
    void setData(const Data &data);
};

enum COLOR
{
    RED,
    BLACK
};

class NodeHeap : public NodeBase
{
public:
    NodeHeap(uint buildingNums, ulong totalTime);

    virtual ulong getKey();

    virtual bool operator< (const NodeHeap& rhs) const;
    virtual bool operator> (const NodeHeap& rhs) const;

private:
    int heapPos_;

friend MinHeap;
};

class NodeRBT : public NodeBase
{
public:
    NodeRBT(uint buildingNums, ulong totalTime, NodeHeap *pointerToHeap);

    virtual void addExecutedTime(ulong addTime);
    virtual void swapData(NodeBase* p);
    virtual ulong getKey();

    bool operator< (const NodeRBT &rhs);
    bool operator> (const NodeRBT &rhs);
    bool operator< (const uint& key);
    bool operator== (const uint& key);

    NodeHeap *getNodeHeap() const;

private:
    uint8_t color_;
    NodeRBT *left_ = nullptr, *right_ = nullptr, *parent_ = nullptr;

    NodeHeap* pointerToHeap_;

    NodeRBT* getUncleNode();
    uint cntRedChild();

friend RBT;
};


#endif //NODEBASE_H
