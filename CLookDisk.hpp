#ifndef CLookDISK_H
#define CLookDISK_H

#include "CLookQueue.hpp"
#include <vector>

class CLookDisk
{
public:
    CLookDisk();
    ~CLookDisk();
    void acceptRequest(Request *req);
    Request *finishRequest(double time);
    double serviceRequest(double totalTime);
    void timerInterrupt(double time);
    int dist(int currTrack, int destTrack);
    int rotDist(int currSector, int destSector);
    int getRequestNumber(double t);
    void setInitTime(double t, double totalTime);
    double getInitTime(double t);
    void setFinTime(double t, double totalTime);
    double timeInSystemSmallest();
    double timeInSystemLargest();
    double timeInSystemAvg();
    double waitTimeSmallest();
    double waitTimeLargest();
    double waitTimeAvg();
    double serviceTimeSmallest();
    double serviceTimeLargest();
    double serviceTimeAvg();
    int getMaxLength();
    double getAvgLength();


private:
    CLookQueue *diskQueue;
    Request *serve;
    std::vector<double> reqNum;
    std::vector<double> timeInit;
    std::vector<double> timeFin;
    int length;
    int numInterrupts;
    int totalLengthOfQueue;
    int requestsServed;
    int maxLengthOfQueue;
    int track;
    int sector;

};
#endif // PickUpDISK_H



