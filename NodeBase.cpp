//
// Created by trucnguyen on 10/31/19.
//

#include "NodeBase.h"

NodeBase::NodeBase(uint buildingNums, ulong totalTime)
    : data_{buildingNums, 0, totalTime} {}


const NodeBase::Data &NodeBase::getData() const
{
    return data_;
}
void NodeBase::setData(const NodeBase::Data &data)
{
    data_ = data;
}

void NodeBase::swapData(NodeBase *p)
{
    auto tmp = this->getData();
    this->setData(p->getData());
    p->setData(tmp);
}

void NodeBase::addExecutedTime(ulong addTime)
{
    this->data_.executedTime += addTime;
}

NodeHeap::NodeHeap(uint buildingNums, ulong totalTime)
    : NodeBase(buildingNums, totalTime), heapPos_(-1)
{

}

bool NodeHeap::operator>(const NodeHeap &rhs) const
{
    if (this->data_.executedTime == rhs.data_.executedTime)
    {
        return this->data_.buildingNums > rhs.data_.buildingNums;
    }
    return this->data_.executedTime > rhs.data_.executedTime;
}

bool NodeHeap::operator<(const NodeHeap &rhs) const
{
    if (this->data_.executedTime == rhs.data_.executedTime)
    {
        return this->data_.buildingNums < rhs.data_.buildingNums;
    }
    return this->data_.executedTime < rhs.data_.executedTime;
}

NodeRBT::NodeRBT(uint buildingNums, ulong totalTime, NodeHeap *pointerToHeap)
    : NodeBase(buildingNums, totalTime), color_(RED), pointerToHeap_(pointerToHeap)
{}

bool NodeRBT::operator<(const NodeRBT &rhs)
{
    return this->data_.buildingNums < rhs.data_.buildingNums;
}

bool NodeRBT::operator>(const NodeRBT &rhs)
{
    return this->data_.buildingNums > rhs.data_.buildingNums;
}

bool NodeRBT::operator<(const uint &key)
{
    return this->data_.buildingNums < key;
}

bool NodeRBT::operator==(const uint &key)
{
    return this->data_.buildingNums == key;
}

NodeRBT *NodeRBT::getUncleNode()
{
    if (this->parent_->parent_->left_ == this->parent_)
        return this->parent_->parent_->right_;
    else
        return this->parent_->parent_->left_;
}

uint NodeRBT::cntRedChild()
{
    uint cnt = 0;
    if (this->left_ != nullptr && this->left_->color_ == RED) cnt++;
    if (this->right_ != nullptr && this->right_->color_ == RED) cnt++;
    return cnt;
}

void NodeRBT::addExecutedTime(ulong addTime)
{
    NodeBase::addExecutedTime(addTime);
    pointerToHeap_->addExecutedTime(addTime);
}

NodeHeap *NodeRBT::getNodeHeap() const
{
    return pointerToHeap_;
}

void NodeRBT::swapData(NodeBase *p)
{
    NodeBase::swapData(p);

    auto node = static_cast<NodeRBT*>(p);
    auto tmp = node->pointerToHeap_;
    node->pointerToHeap_ = this->pointerToHeap_;
    this->pointerToHeap_ = tmp;
}
