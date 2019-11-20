//
// Created by trucnguyen on 10/31/19.
//

#ifndef NODE_H
#define NODE_H

#include <cstdint>
#include <sys/types.h>
#include <MinHeap.h>

class MinHeap;

class Node
{
public:
    Node(uint buildingNums, ulong totalTime);

    void addExecutedTime(ulong addTime);

    virtual bool operator< (const Node& rhs) const;
    virtual bool operator> (const Node& rhs) const;

protected:
    /// buildingNums, executed_time, total_time
    struct Data
    {
        uint buildingNums;
        ulong executedTime;
        ulong totalTime;
    } data_;

private:
    int heapPos_;

public:
    [[nodiscard]] const Data &getData() const;
    void setData(const Data &data);
    void swapData(Node* p);

friend MinHeap;
};


#endif //NODE_H
