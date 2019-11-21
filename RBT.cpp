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

bool RBT::deleteNode(uint key)
{
    auto p = searchNode(key);
    if (p == nullptr)
        return false;

    deleteNode(p);
    return true;
}

void RBT::deleteNode(NodeRBT *y)
{
    y = getReplaceNodeForDeletion(y);

    if (y == root_) // y is root
    {
        root_ = nullptr;
        delete y;
        return;
    }

    if (y->color_ == RED)
    {
        deleteLeafNode(y);
    }
    else // y is black
    {
        if (y->left_ != nullptr || y->right_ != nullptr) // y is degree 1
        {
            auto py = y->parent_;
            // short py to y's child
            auto child = (y->left_ != nullptr)? y->left_ : y->right_;
            child->parent_ = py;
            if (y == py->left_)
                py->left_ = child;
            else
                py->right_= child;

            delete y;
            y = child; //change y to the child

            if (y->color_ == RED)
            {
                y->color_ = BLACK;
                return;
            }
        }

        deleteBlackLeaf(y);
    }
}

void RBT::deleteLeafNode(NodeRBT *p)
{
    if (p == p->parent_->left_)
        p->parent_->left_ = nullptr;
    else
        p->parent_->right_ = nullptr;

    delete p;
}

void RBT::deleteBlackLeaf(NodeRBT *y)
{
    auto p = y;

    while (y->color_ == BLACK && root_ != y)
    {
        auto py = y->parent_;

        if (y == py->right_) //Rcn
        {
            auto v = py->left_;
            if (v->color_ == BLACK) // Rbn
            {
                auto n = v->cntRedChild();
                if (n == 0) // Rb0
                {
                    if (py->color_ == BLACK) // case 1
                    {
                        v->color_ = RED;
                        y = py;
                        continue;
                    }
                    else
                    {
                        py->color_ = BLACK;
                        v->color_ = RED;
                        break;
                    }
                }
                else if (n == 1) // Rb1
                {
                    if (v->left_ != nullptr && v->left_->color_ == RED) // case 1
                    {
                        rotateLL(v);
                        v->color_ = py->color_;
                        v->left_->color_ = BLACK;
                        py->color_ = BLACK;
                        break;
                    }
                    else // case 2
                    {
                        auto w = v->right_;
                        rotateLR(w);
                        w->color_ = py->color_;
                        py->color_ = BLACK;
                        break;
                    }
                }
                else // Rb2
                {
                    auto w = v->right_;
                    rotateLR(w);
                    w->color_ = py->color_;
                    py->color_ = BLACK;
                    break;
                }
            }
            else // Rrn
            {
                auto w = v->right_;
                auto n = w->cntRedChild();
                if (n == 0) // Rr0
                {
                    rotateLL(v);
                    v->color_ = BLACK;
                    py->left_->color_ = RED;
                    break;
                }
                else if (n == 1) // Rr1
                {
                    if (w->left_ != nullptr && w->left_->color_ == RED) // case 1
                    {
                        rotateLR(w);
                        v->right_->color_ = BLACK;
                        break;
                    }
                    else // case 2
                    {
                        auto x = w->right_;
                        rotateRR(x);
                        rotateRR(x);
                        rotateLL(x);
                        x->color_ = BLACK;
                        break;
                    }
                }
                else // Rr2
                {
                    auto x = w->right_;
                    rotateRR(x);
                    rotateRR(x);
                    rotateLL(x);
                    x->color_ = BLACK;
                    break;
                }
            }
        }
        else // Lcn
        {
            auto v = py->right_;
            if (v->color_ == BLACK) // Lbn
            {
                auto n = v->cntRedChild();
                if (n == 0) // Lb0
                {
                    if (py->color_ == BLACK) // case 1
                    {
                        v->color_ = RED;
                        y = py;
                        continue;
                    }
                    else
                    {
                        py->color_ = BLACK;
                        v->color_ = RED;
                        break;
                    }
                }
                else if (n == 1) // Lb1
                {
                    if (v->right_ != nullptr && v->right_->color_ == RED) // case 1
                    {
                        rotateRR(v);
                        v->color_ = py->color_;
                        v->right_->color_ = BLACK;
                        py->color_ = BLACK;
                        break;
                    }
                    else // case 2
                    {
                        auto w = v->left_;
                        rotateRL(w);
                        w->color_ = py->color_;
                        py->color_ = BLACK;
                        break;
                    }
                }
                else // Lb2
                {
                    auto w = v->left_;
                    rotateRL(w);
                    w->color_ = py->color_;
                    py->color_ = BLACK;
                    break;
                }
            }
            else // Lrn
            {
                auto w = v->left_;
                auto n = w->cntRedChild();
                if (n == 0) // Lr0
                {
                    rotateRR(v);
                    v->color_ = BLACK;
                    py->right_->color_ = RED;
                    break;
                }
                else if (n == 1) // Lr1
                {
                    if (w->right_ != nullptr && w->right_->color_ == RED) // case 1
                    {
                        rotateRL(w);
                        v->left_->color_ = BLACK;
                        break;
                    }
                    else // case 2
                    {
                        auto x = w->left_;
                        rotateLL(x);
                        rotateLL(x);
                        rotateRR(x);
                        x->color_ = BLACK;
                        break;
                    }
                }
                else // Lr2
                {
                    auto x = w->left_;
                    rotateLL(x);
                    rotateLL(x);
                    rotateRR(x);
                    x->color_ = BLACK;
                    break;
                }
            }
        }
    }

    deleteLeafNode(p);
}


NodeRBT* RBT::searchNode(uint key)
{
    auto node = root_;

    while (node != nullptr)
    {
        if (*node == key)
            break;

        if (*node < key)
            node = node->right_;
        else
            node = node->left_;
    }

    return node;
}

NodeRBT *RBT::getReplaceNodeForDeletion(NodeRBT *p)
{
    if (p->left_ == nullptr && p->right_ == nullptr) // p is the leaf
        return p;

    if (p->left_ != nullptr && p->right_ != nullptr) // p has two children
    {
        // return the max of the left subtree
        auto node = p->left_;
        while (node->right_ != nullptr)
            node = node->right_;

        // swap data
        p->swapData(node);

        return node;
    }

    return p;
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

void RBT::unitTest()
{
    this->insertNode(new NodeRBT(9, 0));
    this->insertNode(new NodeRBT(8, 0));
    this->insertNode(new NodeRBT(7, 0));
    this->insertNode(new NodeRBT(2, 0));
    this->insertNode(new NodeRBT(6, 0));
    this->insertNode(new NodeRBT(1, 0));
    this->insertNode(new NodeRBT(3, 0));
    this->insertNode(new NodeRBT(4, 1));
    this->insertNode(new NodeRBT(10, 0));
    this->insertNode(new NodeRBT(11, 0));
    this->insertNode(new NodeRBT(12, 0));
    this->insertNode(new NodeRBT(0, 0));

    this->deleteNode(6);
}

void RBT::printRange(NodeRBT *root, const uint &left, const uint &right, ostream &out, bool& comma)
{
    if (root == nullptr)
        return;

    const auto& key = root->getData().buildingNums;
    if (left < key)
        printRange(root->left_, left, right, out, comma);

    if (left <= key && key <= right)
    {
        const auto& data = root->getData();
        if (comma)
            out << ',';
        else
            comma = true;

        out << '(' << data.buildingNums << "," << data.executedTime << "," << data.totalTime << ")";
    }

    if (key < right)
        printRange(root->right_, left, right, out, comma);
}

NodeRBT *RBT::getRoot() const
{
    return root_;
}

