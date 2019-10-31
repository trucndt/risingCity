//
// Created by trucnguyen on 10/31/19.
//

#ifndef NODE_H
#define NODE_H

#include <cstdint>
#include <sys/types.h>

class Node
{
public:
    Node(uint buildingNums, ulong totalTime);

    virtual bool operator< (const Node& rhs) const;
    virtual bool operator> (const Node& rhs) const;

protected:
    /// buildingNums, executed_time, total_time
    struct Data
    {
        uint buildingNums;
        ulong executedTime;
        ulong totalTime;
    } mData;
};


#endif //NODE_H
