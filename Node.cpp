//
// Created by trucnguyen on 10/31/19.
//

#include "Node.h"

Node::Node(uint buildingNums, ulong totalTime)
    : data_{buildingNums, 0, totalTime} {}

bool Node::operator>(const Node &rhs) const
{
    return this->data_.executedTime > rhs.data_.executedTime;
}

bool Node::operator<(const Node &rhs) const
{
    return this->data_.executedTime < rhs.data_.executedTime;
}
