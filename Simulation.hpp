#ifndef SIMULATION_H
#define SIMULATION_H

#include "EventQueue.hpp"
#include "Request.hpp"
#include "DiskDone.hpp"
#include "Timer.hpp"
#include "FCFSDisk.hpp"
#include "SameTrackDisk.hpp"
#include "PickUpDisk.hpp"
#include "LookDisk.hpp"
#include "CLookDisk.hpp"

class Simulation
{
public:
    Simulation();
    void run();
    void outPutSummary();
private:
    double totalTime;
    int numReq;
    EventQueue *simQueue;
    FCFSDisk *fcfsDisk;
    SameTrackDisk *sameTrackDisk;
    PickUpDisk *pickUpDisk;
    LookDisk *lookDisk;
    CLookDisk *cLookDisk;
    void addRequest(Request *req);
    void addDDone(DiskDone *ddone);
    void addTimer(Timer *t);
    void processEvent();
    void processDisk();
    void outputDisk();
    Request *getRequest(std::string line);

};
#endif // SIMULATION_H
