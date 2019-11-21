//
// Created by trucnguyen on 10/31/19.
//

#ifndef NODEBASE_H
#define NODEBASE_H

#include <cstdint>
#include <sys/types.h>
#include <RBT.h>

class RBT;

class NodeBase
{
public:
    NodeBase(uint buildingNums, ulong totalTime);

    virtual void addExecutedTime(ulong addTime);

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
    virtual void swapData(NodeBase* p);
};

enum COLOR
{
    RED,
    BLACK
};

class NodeRBT : public NodeBase
{
private:
    uint8_t color_;
    NodeRBT *left_ = nullptr, *right_ = nullptr, *parent_ = nullptr;

public:
    NodeRBT(uint buildingNums, ulong totalTime);

    NodeRBT* getUncleNode();
    uint cntRedChild();

    bool operator< (const NodeRBT &rhs);
    bool operator> (const NodeRBT &rhs);
    bool operator< (const uint& key);
    bool operator== (const uint& key);

friend RBT;
};

class NodeHeap : public NodeBase
{
public:
    NodeHeap(uint buildingNums, ulong totalTime, NodeRBT* pointerToRBT);

    virtual void addExecutedTime(ulong addTime);

    virtual bool operator< (const NodeHeap& rhs) const;
    virtual bool operator> (const NodeHeap& rhs) const;

    int heapPos_;
    NodeRBT* pointerToRBT_;
};


#endif //NODEBASE_H
