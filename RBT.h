//
// Created by trucnguyen on 10/31/19.
//

#ifndef RBT_H
#define RBT_H

#include <cstdint>
#include <tuple>

class RBT;

enum COLOR
{
    RED,
    BLACK
};

class Node
{
private:
    uint8_t mColor;
    Node *mLeft = nullptr, *mRight = nullptr, *mParent = nullptr;

    /// buildingNums, executed_time, total_time
    struct Data
    {
        uint buildingNums;
        ulong executedTime;
        ulong totalTime;
    } mData;

public:
    Node(uint buildingNums, ulong totalTime);

friend RBT;
};

class RBT
{
public:
    RBT()
    {
        root = nullptr;
    }

    void insertNode(Node* p);

    void deleteNode(Node* p);

private:
    Node *root;
};




#endif //RBT_H
