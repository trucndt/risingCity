//
// Created by trucnguyen on 11/19/19.
//

#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include <Node.h>

class MinHeap
{
public:
    MinHeap();
private:
    std::vector<Node*> _heap;
};


#endif //MINHEAP_H
