#include <Simulator.h>

int main(int argc, char **argv)
{
//    Simulator::initialize(argv[1]);
//    Simulator::loop();

    RBT* rbt = new RBT();
    rbt->insertNode(new NodeRBT(9, 0));
    rbt->insertNode(new NodeRBT(8, 0));
    rbt->insertNode(new NodeRBT(7, 0));
    rbt->insertNode(new NodeRBT(2, 0));
    rbt->insertNode(new NodeRBT(6, 0));
    rbt->insertNode(new NodeRBT(1, 0));
    rbt->insertNode(new NodeRBT(3, 0));
    rbt->insertNode(new NodeRBT(4, 0));
    rbt->insertNode(new NodeRBT(10, 0));
    rbt->insertNode(new NodeRBT(11, 0));
    rbt->insertNode(new NodeRBT(12, 0));
    rbt->insertNode(new NodeRBT(0, 0));

    rbt->deleteNode(7);

//    NodeRBT* p1 = new NodeRBT(13, 0);
//    NodeRBT* p2 = new NodeRBT(10, 0);
//    if (*p1 < *p2)
//        p1 = nullptr;
    return 0;
}