//
// Created by trucnguyen on 11/18/19.
//

#include "Simulator.h"
#include <iostream>

using namespace std;

void Simulator::initialize(const std::string &inputFileName)
{
    s_inFile.open(inputFileName);
    s_outFile.open("output_file.txt");
    s_timestamp = 0;

    s_rbt = new RBT();
    s_heap = new MinHeap();
}

void Simulator::loop()
{
    s_cmdTime = readCommand(); // read first command

    // event loop
    while (s_cmdTime != -1 || s_buildingTime != -1)
    {
        if ((s_cmdTime <= s_buildingTime && s_cmdTime != -1) || s_buildingTime == -1)
        {
            if (s_curBuilding != nullptr)
            {
                updateCurBuilding(s_cmdTime - s_timestamp);
            }

            s_timestamp = s_cmdTime;

            executePendingCommand();

            s_cmdTime = readCommand();
        }
        else
        {
            updateCurBuilding(s_buildingTime - s_timestamp);

            s_timestamp = s_buildingTime;

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
    const auto &eventType = cmdStr.substr(colon + 2, paren - colon - 2);
    if (eventType == "Insert")
        s_pendingCommand.eventType = INSERT;
    else if (eventType == "PrintBuilding")
    {
        if (data.find(',') == string::npos)
            s_pendingCommand.eventType = PRINT1;
        else
            s_pendingCommand.eventType = PRINT2;
    }
}

void Simulator::printBuilding(uint num1)
{
    auto p = s_rbt->searchNode(num1);

    if (p == nullptr)
    {
        cout << "(0,0,0)" << endl;
    }
    else
    {
        const auto& data = p->getData();
        cout << "(" << data.buildingNums << "," << data.executedTime << "," << data.totalTime << ")" << endl;
    }
}

void Simulator::printBuilding(uint num1, uint num2)
{
    cout << num1 << num2 << endl;
}

long Simulator::readCommand()
{
    string line;
    if (getline(s_inFile, line))
    {
        if (!line.empty() && line[line.size() - 1] == '\r')
            line.erase(line.size() - 1);

        parseCommand(line);
        return s_pendingCommand.arrivalTime;
    }

    return -1;
}

void Simulator::executePendingCommand()
{
    auto comma = s_pendingCommand.data.find(',');

    switch (s_pendingCommand.eventType)
    {
    case PRINT1:
        printBuilding(stoi(s_pendingCommand.data));
        break;
    case PRINT2:
        printBuilding(stoi(s_pendingCommand.data.substr(0, comma)), stoi(s_pendingCommand.data.substr(comma + 1)));
        break;
    case INSERT:
        auto nodeRbt = new NodeRBT(stoi(s_pendingCommand.data.substr(0, comma)), stoi(s_pendingCommand.data.substr(comma + 1)));
        s_rbt->insertNode(nodeRbt);
        s_heap->insertNode(nodeRbt);
        break;
    }
}

void Simulator::updateCurBuilding(long timePassed)
{
    if (timePassed == 0)
        return;
    s_curBuilding->addExecutedTime(timePassed);
    s_heap->increaseKey(s_curBuilding);
}

long Simulator::chooseNextBuilding()
{
    if (s_heap->isEmpty())
        return -1;

    s_curBuilding = s_heap->peekMin();
    const auto& buildingData = s_curBuilding->getData();

    int workingTime = min(buildingData.totalTime - buildingData.executedTime, (ulong)5);
    return s_timestamp + workingTime;
}

void Simulator::removeCurBuilding()
{
    const auto& data = s_curBuilding->getData();
    cout << "(" << data.buildingNums << "," << s_timestamp << ")" << endl;
    s_heap->remove(s_curBuilding);
    s_rbt->deleteNode(static_cast<NodeRBT*>(s_curBuilding));
    s_curBuilding = nullptr;
}

