//
// Created by trucnguyen on 10/31/19.
//

#include "Node.h"

Node::Node(uint buildingNums, ulong totalTime)
    : mData{buildingNums, 0, totalTime} {}

bool Node::operator>(const Node &rhs) const
{
    return this->mData.executedTime > rhs.mData.executedTime;
}

bool Node::operator<(const Node &rhs) const
{
    return this->mData.executedTime < rhs.mData.executedTime;
}
