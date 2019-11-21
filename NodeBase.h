//
// Created by trucnguyen on 10/31/19.
//

#ifndef NODEBASE_H
#define NODEBASE_H

#include <cstdint>
#include <sys/types.h>
#include <RBT.h>
#include <MinHeap.h>

class RBT;
class MinHeap;

/// Base class for node
class NodeBase
{
public:
    /**
     * Constructor for NodeBase
     * @param buildingNums building number
     * @param totalTime total time
     */
    NodeBase(uint buildingNums, ulong totalTime);

    /**
     * Add time to the executed_time field
     * @param addTime value to add
     */
    virtual void addExecutedTime(ulong addTime);

    /**
     * Swap the data field with another node
     * @param p another node
     */
    virtual void swapData(NodeBase* p);

    /**
     * Get the key value of the node
     * @return nothing since this is pure virtual
     */
    virtual ulong getKey() const = 0;

protected:
    /// Store data of a node: buildingNums, executed_time, total_time
    struct Data
    {
        uint buildingNums;
        ulong executedTime;
        ulong totalTime;
    } data_;

public:
    /**
     * Getter for data
     * @return a const reference to the data object
     */
    const Data &getData() const;

    /**
     * Setter for data
     * @param data the data object
     */
    void setData(const Data &data);
};

/// Node for min heap
class NodeHeap : public NodeBase
{
public:
    /**
     * Constructor for NodeHeap
     * @param buildingNums building number
     * @param totalTime total time
     */
    NodeHeap(uint buildingNums, ulong totalTime);

    /**
     * Get the key value of the node
     * @return executed_time
     */
    ulong getKey() const;

    /**
     * Overload the < operator to compare with another NodeHeap
     * @param rhs the other NodeHeap
     * @return true if <, false otherwise
     */
    bool operator< (const NodeHeap& rhs) const;

    /**
     * Overload the > operator to compare with another NodeHeap
     * @param rhs the other NodeHeap
     * @return true if >, false otherwise
     */
    bool operator> (const NodeHeap& rhs) const;

private:
    /// Current index of this node in the heap
    int heapPos_;

friend MinHeap;
};

/// Define color for the red-black tree
enum COLOR
{
    RED,
    BLACK
};

/// Node for red-black tree
class NodeRBT : public NodeBase
{
public:
    /**
     * Constructor for NodeRBT
     * @param buildingNums building number
     * @param totalTime total time
     * @param pointerToHeap pointer to the corresponding node in heap
     */
    NodeRBT(uint buildingNums, ulong totalTime, NodeHeap *pointerToHeap);

    /**
     * Add time to the executed_time field, update the correspond node in heap
     * @param addTime value to add
     */
    void addExecutedTime(ulong addTime);

    /**
     * Swap the data field and the pointerToHeap with another node
     * @param p another node
     */
    void swapData(NodeBase* p);

    /**
     * Get the key value of the node
     * @return buildingNums
     */
    ulong getKey() const;

    /**
     * Get the corresponding node in heap
     * @return the NodeHeap
     */
    NodeHeap *getNodeHeap() const;

    /**
     * Overload the < operator to compare with another NodeRBT
     * @param rhs the other NodeHeap
     * @return true if <, false otherwise
     */
    bool operator< (const NodeRBT &rhs);

    /**
     * Overload the > operator to compare with another NodeRBT
     * @param rhs the other NodeHeap
     * @return true if >, false otherwise
     */
    bool operator> (const NodeRBT &rhs);

    /**
     * Overload the < operator to compare with another key
     * @param rhs the other key
     * @return true if <, false otherwise
     */
    bool operator< (const uint& key);

    /**
     * Overload the == operator to compare with another key
     * @param rhs the other key
     * @return true if ==, false otherwise
     */
    bool operator== (const uint& key);

private:
    uint8_t color_; // Color of the node
    /// Pointers to related nodes
    NodeRBT *left_ = nullptr, *right_ = nullptr, *parent_ = nullptr;

    NodeHeap* pointerToHeap_; // Pointer to the corresponding node in heap

    /**
     * Get uncle node. Make sure it has the a grand parent
     * @return the uncle node
     */
    NodeRBT* getUncleNode();

    /**
     * Count the number of red children
     * @return the number of red children
     */
    uint8_t cntRedChild();

friend RBT;
};


#endif //NODEBASE_H
