#include "SameTrackDisk.hpp"
#include "Request.hpp"
#include <stdlib.h>
#include <vector>

SameTrackDisk::SameTrackDisk()
{
    diskQueue = new SameTrackQueue();
    serve = nullptr;
    length = 0;
    numInterrupts = 0;
    totalLengthOfQueue = 0;
    requestsServed = 0;
    maxLengthOfQueue = 0;
    track = 0;
    sector = 0;
}

SameTrackDisk::~SameTrackDisk()
{
    delete diskQueue;
    delete serve;
}

void SameTrackDisk::acceptRequest(Request *req)
{
    length++;
    reqNum.push_back(req->time());
    timeInit.push_back(0);
    timeFin.push_back(0);
    diskQueue->addRequest(req);
}

Request *SameTrackDisk::finishRequest(double time)
{
    Request *tempRequest = new Request(serve->time(), serve->track(), serve->sector());
    serve = nullptr;
    diskQueue->deleteHead();
    length--;
    setFinTime(tempRequest->time(), time);
    return tempRequest;
}

double SameTrackDisk::serviceRequest(double totalTime)
{
    if(serve != nullptr || diskQueue->isEmpty())
    {
        return -1;
    }
    serve = diskQueue->getRequest();
    double ddoneTime = dist(track, serve->track()) * 3 + rotDist(sector, serve->sector()) * 0.1 + 0.1;


    track = serve->track();
    sector = serve->sector() + 1;
    setInitTime(serve->time(), totalTime);
    if(sector > 30)
    {
        sector -= 30;
    }

    return ddoneTime;
}

void SameTrackDisk::timerInterrupt(double time)
{
    numInterrupts++;
    totalLengthOfQueue += length;
    if(length > maxLengthOfQueue)
    {
        maxLengthOfQueue = length;
    }
}

int SameTrackDisk::dist(int currTrack, int destTrack)
{
    return abs(currTrack - destTrack);
}

int SameTrackDisk::rotDist(int currSector, int destSector)
{
    if(currSector > destSector)
    {
        return 30 - currSector + destSector;
    }
    return destSector - currSector;
}

int SameTrackDisk::getRequestNumber(double t)
{
    for(int i = 0; i < reqNum.size(); i++)
    {
        if(t == reqNum[i])
        {
            return i + 1;
        }
    }
}

void SameTrackDisk::setInitTime(double t, double totalTime)
{
    for(int i = 0; i < reqNum.size(); i++)
    {
        if(t == reqNum[i])
        {
            timeInit[i] = totalTime;
        }
    }
}

double SameTrackDisk::getInitTime(double t)
{
    for(int i = 0; i < reqNum.size(); i++)
    {
        if(t == reqNum[i])
        {
            return timeInit[i];
        }
    }
}

void SameTrackDisk::setFinTime(double t, double totalTime)
{
    for(int i = 0; i < reqNum.size(); i++)
    {
        if(t == reqNum[i])
        {
            timeFin[i] = totalTime;
        }
    }
}

double SameTrackDisk::timeInSystemSmallest()
{
    double smallest = timeFin[0] - reqNum[0];
    for(int i = 1; i < timeFin.size(); i++)
    {
        double newTime = timeFin[i] - reqNum[i];
        if(smallest > newTime)
        {
            smallest = newTime;
        }
    }
    return smallest;
}

double SameTrackDisk::timeInSystemLargest()
{
    double largest = timeFin[0] - reqNum[0];
    for(int i = 1; i < timeFin.size(); i++)
    {
        double newTime = timeFin[i] - reqNum[i];
        if(largest < newTime)
        {
            largest = newTime;
        }
    }
    return largest;
}

double SameTrackDisk::timeInSystemAvg()
{
    double sum = 0;
    for(int i = 0; i < timeFin.size(); i++)
    {
        sum += timeFin[i] - reqNum[i];
    }
    return sum / timeFin.size();
}

double SameTrackDisk::waitTimeSmallest()
{
    double smallest = timeInit[0] - reqNum[0];
    for(int i = 1; i < timeFin.size(); i++)
    {
        double newTime = timeInit[i] - reqNum[i];
        if(smallest > newTime)
        {
            smallest = newTime;
        }
    }
    return smallest;
}

double SameTrackDisk::waitTimeLargest()
{
    double largest = timeInit[0] - reqNum[0];
    for(int i = 1; i < timeFin.size(); i++)
    {
        double newTime = timeInit[i] - reqNum[i];
        if(largest < newTime)
        {
            largest = newTime;
        }
    }
    return largest;
}

double SameTrackDisk::waitTimeAvg()
{
    double sum = 0;
    for(int i = 0; i < timeFin.size(); i++)
    {
        sum += timeInit[i] - reqNum[i];
    }
    return sum / timeFin.size();
}

double SameTrackDisk::serviceTimeSmallest()
{
    double smallest = timeFin[0] - timeInit[0];
    for(int i = 1; i < timeFin.size(); i++)
    {
        double newTime = timeFin[i] - timeInit[i];
        if(smallest > newTime)
        {
            smallest = newTime;
        }
    }
    return smallest;
}

double SameTrackDisk::serviceTimeLargest()
{
    double largest = timeFin[0] - timeInit[0];
    for(int i = 1; i < timeFin.size(); i++)
    {
        double newTime = timeFin[i] - timeInit[i];
        if(largest < newTime)
        {
            largest = newTime;
        }
    }
    return largest;
}

double SameTrackDisk::serviceTimeAvg()
{
    double sum = 0;
    for(int i = 0; i < timeFin.size(); i++)
    {
        sum += timeFin[i] - timeInit[i];
    }
    return sum / timeFin.size();
}

int SameTrackDisk::getMaxLength()
{
    return maxLengthOfQueue;
}

double SameTrackDisk::getAvgLength()
{
    return (double)totalLengthOfQueue/(double)numInterrupts;
}

