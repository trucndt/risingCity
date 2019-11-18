//
// Created by trucnguyen on 10/31/19.
//

#include "RBT.h"

using namespace std;

NodeRBT::NodeRBT(uint buildingNums, ulong totalTime)
    : Node(buildingNums, totalTime), color_(RED)
{}

bool NodeRBT::operator<(const NodeRBT &rhs)
{
    return this->data_.buildingNums < rhs.data_.buildingNums;
}

bool NodeRBT::operator>(const NodeRBT &rhs)
{
    return this->data_.buildingNums > rhs.data_.buildingNums;
}
