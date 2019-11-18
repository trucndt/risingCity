#include <Simulator.h>

int main(int argc, char **argv)
{
    Simulator::initialize(argv[1]);
    Simulator::loop();
    return 0;
}