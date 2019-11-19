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

const Node::Data &Node::getData() const
{
    return data_;
}
void Node::setData(const Node::Data &data)
{
    data_ = data;
}

void Node::swapData(Node *p)
{
    auto tmp = this->getData();
    this->setData(p->getData());
    p->setData(tmp);
}
