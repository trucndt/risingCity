//
// Created by trucnguyen on 11/18/19.
//

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <RBT.h>
#include <string>
#include <fstream>
#include <utility>

class Simulator
{
public:
    // Disallow creating an instance of this object
    Simulator() = delete;

    static void initialize(const std::string& inputFileName);

    static void loop();

private:
    enum EventType {INSERT, PRINT1, PRINT2};

    inline static struct
    {
        uint arrivalTime;
        EventType eventType;
        std::string data;

//        Command(uint time, EventType eventType, std::string data)
//            : time(time), eventType(eventType), data(std::move(data)) {}
    } s_pendingCommand;

    inline static uint s_timestamp;
    inline static RBT* s_rbt;
    inline static std::ifstream s_inFile;
    inline static std::ofstream s_outFile;

    /**
     * Parse command string and save to s_pendingCommand
     * @param cmdStr the command string
     */
    static void parseCommand(const std::string& cmdStr);

    static void printBuilding(uint num1);

    static void printBuilding(uint num1, uint num2);
};


#endif //SIMULATOR_H
