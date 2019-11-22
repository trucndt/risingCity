//
// Created by trucnguyen on 11/18/19.
//

#include "Simulator.h"
#include <iostream>

using namespace std;

void Simulator::initialize(const std::string &inputFileName)
{
    s_inFile = new ifstream(inputFileName);
    s_outFile = new ofstream("output_file.txt");
    s_timestamp = 0;

    s_rbt = new RBT();
    s_heap = new MinHeap();
}

void Simulator::loop()
{
    /**
     * There are two kinds of event in this loop:
     *  1. Read the next command, represented by s_cmdTime
     *  2. Choose the next building, represented by s_buildingTime
     * If there is no event, the corresponding variables are set to -1. At each timestamp, the simulator chooses to work
     * on the event with the smallest timestamp
     */

    s_cmdTime = readCommand(); // read first command

    // event loop
    while (s_cmdTime != -1 || s_buildingTime != -1) // There is some event
    {
        if ((s_cmdTime <= s_buildingTime && s_cmdTime != -1) || s_buildingTime == -1)
        {
            // This is the event for reading the next command

            updateCurBuilding(s_cmdTime - s_timestamp); // Update the exe time of the current building

            s_timestamp = s_cmdTime; // update the global time

            executePendingCommand();

            s_cmdTime = readCommand(); // get the next read command event
        }
        else
        {
            // This is the event for choosing the next building

            updateCurBuilding(s_buildingTime - s_timestamp); // Update the exe time of the current building

            s_timestamp = s_buildingTime; // update the global time

            const auto& buildingData = s_curBuilding->getData();

            if (buildingData.executedTime == buildingData.totalTime) // remove building
            {
                removeCurBuilding();
            }

            // choose new building to work on
            s_buildingTime = chooseNextBuilding();
        }

        if (s_curBuilding == nullptr) // find new building to work on
        {
            s_buildingTime = chooseNextBuilding();
        }

    }
}

void Simulator::parseCommand(const std::string &cmdStr)
{
    // Look for the colon
    auto colon = cmdStr.find(':');

    // Get arrival time
    const auto& time = cmdStr.substr(0, colon);
    s_pendingCommand.arrivalTime = stoi(time);

    // Look for the left parenthesis
    auto paren = cmdStr.find('(');

    // Get command data
    const auto &data = cmdStr.substr(paren + 1, cmdStr.length() - paren - 2);
    s_pendingCommand.data = data;

    // Get command type
    const auto &cmdType = cmdStr.substr(colon + 2, paren - colon - 2);
    if (cmdType == "Insert")
        s_pendingCommand.cmdType = INSERT;
    else if (cmdType == "PrintBuilding")
    {
        if (data.find(',') == string::npos)
            s_pendingCommand.cmdType = PRINT1;
        else
            s_pendingCommand.cmdType = PRINT2;
    }
}

void Simulator::printBuilding(uint num1)
{
    auto p = s_rbt->searchNode(num1); // search for the building

    if (p == nullptr) // not found
    {
        *s_outFile << "(0,0,0)" << endl;
    }
    else
    {
        const auto& data = p->getData();
        *s_outFile << "(" << data.buildingNums << "," << data.executedTime << "," << data.totalTime << ")" << endl;
    }
}

void Simulator::printBuilding(uint num1, uint num2)
{
    bool comma = false;
    RBT::printRange(s_rbt->getRoot(), num1, num2, *s_outFile, comma);

    if (comma) // something was printed
        *s_outFile << endl;
    else
        *s_outFile << "(0,0,0)" << endl;
}

long Simulator::readCommand()
{
    string line;
    if (getline(*s_inFile, line)) // get the entire a line
    {
        if (!line.empty() && line[line.size() - 1] == '\r') // remove trailing line endings
            line.erase(line.size() - 1);

        parseCommand(line);
        return s_pendingCommand.arrivalTime;
    }

    return -1;
}

void Simulator::executePendingCommand()
{
    /*
     * Extract info from the command field
     */
    auto comma = s_pendingCommand.data.find(',');
    auto num1 = stoi(s_pendingCommand.data.substr(0, comma));
    auto num2 = stoi(s_pendingCommand.data.substr(comma + 1));

    /*
     * Act upon the command type
     */
    switch (s_pendingCommand.cmdType)
    {
    case PRINT1:
        printBuilding(stoi(s_pendingCommand.data));
        break;
    case PRINT2:
        printBuilding(num1, num2);
        break;
    case INSERT:
        if (s_rbt->searchNode(num1) != nullptr) // check for duplication before insert
        {
            exit(1);
        }

        auto nodeHeap = new NodeHeap(num1, num2); // create a new heap node
        s_heap->insertNode(nodeHeap); // insert to the heap
        s_rbt->insertNode(new NodeRBT(num1, num2, nodeHeap)); // create and insert the corresponding rbt node
        break;
    }
}

void Simulator::updateCurBuilding(long timePassed)
{
    if (timePassed == 0 || s_curBuilding == nullptr) // nothing to update
        return;
    s_curBuilding->addExecutedTime(timePassed); // update exe time
    s_heap->increaseKey(s_curBuilding->getNodeHeap()); // update the heap
}

long Simulator::chooseNextBuilding()
{
    if (s_heap->isEmpty())
        return -1;

    // search for the node with buildingNums in the rbt and select that node
    s_curBuilding = s_rbt->searchNode(s_heap->peekMin()->getData().buildingNums);
    const auto& buildingData = s_curBuilding->getData();

    // calculate the working time of the building
    int workingTime = min(buildingData.totalTime - buildingData.executedTime, (ulong)5);
    return s_timestamp + workingTime; // get the next event for choosing a new building
}

void Simulator::removeCurBuilding()
{
    /*
     * Print out the building info
     */
    const auto& data = s_curBuilding->getData();
    *s_outFile << "(" << data.buildingNums << "," << s_timestamp << ")" << endl;

    auto nodeHeap = s_curBuilding->getNodeHeap(); // get node heap
    s_heap->remove(nodeHeap); // remove from the heap
    s_rbt->deleteNode(s_curBuilding); // remove from the rbt
    s_curBuilding = nullptr; // set to null
}

void Simulator::close()
{
    delete s_rbt;
    delete s_heap;
    s_inFile->close();
    s_outFile->close();
    delete s_inFile;
    delete s_outFile;
}

