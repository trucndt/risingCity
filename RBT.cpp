//
// Created by trucnguyen on 10/31/19.
//

#include "RBT.h"

using namespace std;

NodeRBT::NodeRBT(uint buildingNums, ulong totalTime)
    : Node(buildingNums, totalTime), mColor(RED)
{}

bool NodeRBT::operator<(const NodeRBT &rhs)
{
    return this->mData.buildingNums < rhs.mData.buildingNums;
}

bool NodeRBT::operator>(const NodeRBT &rhs)
{
    return this->mData.buildingNums > rhs.mData.buildingNums;
}
