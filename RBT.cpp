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

NodeRBT *NodeRBT::getUncleNode()
{
    if (this->parent_->parent_->left_ == this->parent_)
        return this->parent_->parent_->right_;
    else
        return this->parent_->parent_->left_;
}

void RBT::insertNode(NodeRBT *p)
{
    insertNodeBST(p); // perform a normal BST insert

    if (p->parent_ == nullptr) // p is the root node
    {
        p->color_ = BLACK;
        return;
    }

    if (p->parent_ == root_) // eliminate trivial case
        return;

    while (p != root_ && p->parent_->color_ == RED)
    {
        auto uncle = p->getUncleNode();
        if (uncle != nullptr && uncle->color_ == RED) // XYr, flip
        {
            p->parent_->color_ = BLACK;
            p->parent_->parent_->color_ = RED;
            uncle->color_ = BLACK;
            p = p->parent_->parent_;
        }
        else if (p->parent_ == p->parent_->parent_->left_) // LYb
        {
            if (p == p->parent_->left_) // LLb
            {
                p->parent_->color_ = BLACK;
                p->parent_->parent_->color_ = RED;
                rotateLL(p->parent_);
            }
            else // LRb
            {
                p->color_ = BLACK;
                p->parent_->parent_->color_ = RED;
                rotateLR(p);
            }

            break;
        }
        else // RYz
        {
            if (p == p->parent_->right_) // RRb
            {
                p->parent_->color_ = BLACK;
                p->parent_->parent_->color_ = RED;
                rotateRR(p->parent_);
            }
            else // RLb
            {
                p->color_ = BLACK;
                p->parent_->parent_->color_ = RED;
                rotateRL(p);
            }

            break;
        }
    }

    root_->color_ = BLACK;
}

void RBT::insertNodeBST(NodeRBT *p)
{
    NodeRBT* curRoot = root_; // Find where to put p
    NodeRBT* parent = nullptr; // keep track of the parent of curRoot

    while (curRoot != nullptr)
    {
        parent = curRoot;
        if (*p < *curRoot)
            curRoot = curRoot->left_;
        else
            curRoot = curRoot->right_;
    }

    // Add p to the tree
    if (parent == nullptr) // The tree is empty
        root_ = p;
    else if (*p < *parent)
        parent->left_ = p;
    else
        parent->right_ = p;

    p->parent_ = parent;
}

void RBT::rotateRR(NodeRBT *y)
{
    NodeRBT* z = y->parent_;

    z->right_ = y->left_;

    if (z->right_ != nullptr)
        z->right_->parent_ = z;

    y->parent_ = z->parent_;

    if (z->parent_ == nullptr)
        root_ = y;
    else if (z == z->parent_->left_)
        z->parent_->left_ = y;
    else
        z->parent_->right_ = y;

    y->left_ = z;
    z->parent_ = y;
}

void RBT::rotateLL(NodeRBT *y)
{
    NodeRBT* z = y->parent_;

    z->left_ = y->right_;

    if (z->left_ != nullptr)
        z->left_->parent_ = z;

    y->parent_ = z->parent_;

    if (z->parent_ == nullptr)
        root_ = y;
    else if (z == z->parent_->left_)
        z->parent_->left_ = y;
    else
        z->parent_->right_ = y;

    y->right_ = z;
    z->parent_ = y;
}

void RBT::rotateRL(NodeRBT *p)
{
    rotateLL(p);
    rotateRR(p);
}

void RBT::rotateLR(NodeRBT *p)
{
    rotateRR(p);
    rotateLL(p);
}
