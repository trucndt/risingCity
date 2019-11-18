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
}

void Simulator::loop()
{
    string line;
    while (getline(s_inFile, line))
    {
        if (!line.empty() && line[line.size() - 1] == '\r')
            line.erase(line.size() - 1);

        parseCommand(line);

        s_timestamp = s_pendingCommand.arrivalTime;

        switch (s_pendingCommand.eventType)
        {
        case INSERT:break;
        case PRINT1:
            printBuilding(stoi(s_pendingCommand.data));
            break;
        case PRINT2:
            auto comma = s_pendingCommand.data.find(',');
            printBuilding(stoi(s_pendingCommand.data.substr(0, comma)), stoi(s_pendingCommand.data.substr(comma + 1)));
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
    cout << num1 << endl;
}

void Simulator::printBuilding(uint num1, uint num2)
{
    cout << num1 << num2 << endl;
}

