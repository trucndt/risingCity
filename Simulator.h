//
// Created by trucnguyen on 11/18/19.
//

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <RBT.h>
#include <MinHeap.h>
#include <string>
#include <fstream>
#include <utility>

class Simulator
{
public:
    // Disallow creating an instance of this object
    Simulator() = delete;

    /**
     * Initialize the Simulator
     * @param inputFileName path to input file
     */
    static void initialize(const std::string& inputFileName);

    /**
     * Implement event loop for the simulator
     */
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

    inline static long s_timestamp = 0;
    inline static long s_cmdTime = -1;
    inline static long s_buildingTime = -1;
    inline static RBT* s_rbt;
    inline static MinHeap* s_heap;
    inline static Node* s_curBuilding = nullptr;
    inline static std::ifstream s_inFile;
    inline static std::ofstream s_outFile;

    /**
     * Parse command string and save to s_pendingCommand
     * @param cmdStr the command string
     */
    static void parseCommand(const std::string& cmdStr);

    /**
     * Print the triplet buildingNum,executed_time,total_time
     * @param num1 the buildingNum
     */
    static void printBuilding(uint num1);

    /**
     * Print all triplets bn, executed_time, total_time for which buildingNum1 <= bn <= buildingNum2
     * @param num1 buildingNum1
     * @param num2 buildingNum2
     */
    static void printBuilding(uint num1, uint num2);

    /**
     * Read a new command from the input file
     * @return arrival time of the command
     */
    static long readCommand();

    /**
     * Execute the command in s_pendingCommand
     */
    static void executePendingCommand();

    /**
     * Update the executed time of the current building and update the s_heap accordingly
     * @param timePassed units of time has passed since it was chosen
     */
    static void updateCurBuilding(long timePassed);

    /**
     * Choose a new building to work on based on s_heap
     * @return
     * <p>-1 if there is no building to work on</p>
     * <p>the next timestamp to process the building</p>
     */
    static long chooseNextBuilding();

    /**
     * Remove the current building from s_heap, s_rbt, and set the pointer to null
     */
    static void removeCurBuilding();
};


#endif //SIMULATOR_H
