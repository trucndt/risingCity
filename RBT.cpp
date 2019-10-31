//
// Created by trucnguyen on 10/31/19.
//

#include "RBT.h"

using namespace std;

Node::Node(uint buildingNums, ulong totalTime)
    : mColor(RED), mData{buildingNums, 0, totalTime}
{}
