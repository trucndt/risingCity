#include <Simulator.h>

int main(int argc, char **argv)
{
    Simulator::initialize(argv[1]); // initialize the Simulator
    Simulator::loop(); // start the Simulator

    return 0;
}