#include "Simulation.hpp"
#include "Event.hpp"
#include "Request.hpp"
#include "EventQueue.hpp"
#include "DiskDone.hpp"
#include "Timer.hpp"
#include "FCFSDisk.hpp"
#include "PickUpDisk.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

Simulation::Simulation()
{
    simQueue = new EventQueue();
    addTimer(new Timer(50));
    totalTime = 0;
    numReq = 0;
    fcfsDisk = new FCFSDisk();
    sameTrackDisk = new SameTrackDisk();
    pickUpDisk = new PickUpDisk();
    lookDisk = new LookDisk();
    cLookDisk = new CLookDisk();

    std::ofstream fcfsOut("FCFS_output");
    fcfsOut << std::setw(3) << "#" << std::setw(10) << "Track" << std::setw(8) << "Sec" << std::setw(12) << "Enter" << std::setw(12) << "Init" << std::setw(12) << "Comp" << std::setw(12) << "Wait" << std::setw(12) <<  "Serve" << std::setw(12) << "TmInSys" << "\r\n";
    fcfsOut.close();

    std::ofstream sameTrackOut("SAMETRACK_output");
    sameTrackOut << std::setw(3) << "#" << std::setw(10) << "Track" << std::setw(8) << "Sec" << std::setw(12) << "Enter" << std::setw(12) << "Init" << std::setw(12) << "Comp" << std::setw(12) << "Wait" << std::setw(12) <<  "Serve" << std::setw(12) << "TmInSys" << "\r\n";
    sameTrackOut.close();

    std::ofstream pickUpOut("PICKUP_output");
    pickUpOut << std::setw(3) << "#" << std::setw(10) << "Track" << std::setw(8) << "Sec" << std::setw(12) << "Enter" << std::setw(12) << "Init" << std::setw(12) << "Comp" << std::setw(12) << "Wait" << std::setw(12) <<  "Serve" << std::setw(12) << "TmInSys" << "\r\n";
    pickUpOut.close();

    std::ofstream lookOut("LOOK_output");
    lookOut << std::setw(3) << "#" << std::setw(10) << "Track" << std::setw(8) << "Sec" << std::setw(12) << "Enter" << std::setw(12) << "Init" << std::setw(12) << "Comp" << std::setw(12) << "Wait" << std::setw(12) <<  "Serve" << std::setw(12) << "TmInSys" << "\r\n";
    lookOut.close();

    std::ofstream cLookOut("CLOOK_output");
    cLookOut << std::setw(3) << "#" << std::setw(10) << "Track" << std::setw(8) << "Sec" << std::setw(12) << "Enter" << std::setw(12) << "Init" << std::setw(12) << "Comp" << std::setw(12) << "Wait" << std::setw(12) <<  "Serve" << std::setw(12) << "TmInSys" << "\r\n";
    cLookOut.close();
}

void Simulation::run()
{
   std::string line;
   getline(std::cin, line);
   addRequest(getRequest(line));
  
        while(!simQueue->isEmpty())
        {
	  if(getline(std::cin, line))
	  {
	    Request *newReq = getRequest(line);

	    if(newReq != nullptr)
            {
                addRequest(newReq);
            }
	  }
            processEvent();
            processDisk();
        }
        outPutSummary();
}

Request *Simulation::getRequest(std::string line)
{
        double time = -1;
        int track = -1;
        int sector = -1;
        std::string parser = "";

        if(!line.empty())
        {
            for(int i = 0; i < line.size(); i++)
            {
                if(line[i] != ' ' && line[i] != '\n')
                {
                    parser.push_back(line[i]);
                }
                else if(!parser.empty())
                {
                    if(time < 0)
                    {
                        std::istringstream(parser) >> time;
			time /= 10;
                    }
                    else if(track < 0)
                    {
                        std::istringstream(parser) >> track;
                    }
                    parser.clear();
                }
            }
            std::istringstream(parser) >> sector;
	    if(track < 0 || track > 99)
	    {
	      std::cout << "Error track is out or range, terminating program." << std::endl;
	      exit(1);
	    }
	    if(sector < 0 || sector > 29)
	    {
	      std::cout << "Error sector is out or range, terminating program." << std::endl;
	      exit(1);
	    }
	    
            return new Request(time, track, sector);
        }

        return nullptr;
}

void Simulation::addRequest(Request *req)
{
    Event *tempEvent = new Event();
    tempEvent->addRequest(req);
    simQueue->addEvent(tempEvent);
    req++;
}

void Simulation::addDDone(DiskDone *ddone)
{
    Event *tempEvent = new Event();
    tempEvent->addDiskDone(ddone);
    simQueue->addEvent(tempEvent);
}

void Simulation::addTimer(Timer *t)
{
    Event *tempEvent = new Event();
    tempEvent->addTimer(t);
    simQueue->addEvent(tempEvent);
}

void Simulation::processEvent()
{
    if(!simQueue->isEmpty())
    {
        Event *tempEvent = simQueue->getEvent();
        if(tempEvent->isRequest())
        {
            totalTime = tempEvent->getRequest()->time();
            fcfsDisk->acceptRequest(tempEvent->getRequest());
            sameTrackDisk->acceptRequest(tempEvent->getRequest());
            pickUpDisk->acceptRequest(tempEvent->getRequest());
            lookDisk->acceptRequest(tempEvent->getRequest());
            cLookDisk->acceptRequest(tempEvent->getRequest());
        }
        else if(tempEvent->isDiskDone())
        {

            totalTime = tempEvent->getDiskDone()->getTime();

            if(tempEvent->getDiskDone()->getAlg() == 1)
            {
                Request *tempReq = fcfsDisk->finishRequest(totalTime);
                double reqTime = tempReq->time();
                double timeInit = fcfsDisk->getInitTime(reqTime);
                std::ofstream fcfsOut("FCFS_output", std::ios_base::app);
                fcfsOut << std::setw(3) << fcfsDisk->getRequestNumber(reqTime) << std::setw(10) << tempReq->track() << std::setw(8) << tempReq->sector() << std::setw(12) << tempReq->time() << std::setw(12)
                << timeInit << std::setw(12) << totalTime << std::setw(12) << timeInit - reqTime << std::setw(12) << totalTime - timeInit << std::setw(12) << (totalTime - tempReq->time()) << "\n";
                fcfsOut.close();
            }
            else if(tempEvent->getDiskDone()->getAlg() == 2)
            {
                Request *tempReq = sameTrackDisk->finishRequest(totalTime);
                double reqTime = tempReq->time();
                double timeInit = sameTrackDisk->getInitTime(reqTime);
                std::ofstream sameTrackOut("SAMETRACK_output", std::ios_base::app);
                sameTrackOut << std::setw(3) << sameTrackDisk->getRequestNumber(reqTime) << std::setw(10) << tempReq->track() << std::setw(8) << tempReq->sector() << std::setw(12) << tempReq->time() << std::setw(12)
                << timeInit << std::setw(12) << totalTime << std::setw(12) << timeInit - reqTime << std::setw(12) << totalTime - timeInit << std::setw(12) << (totalTime - tempReq->time()) << "\n";
                sameTrackOut.close();
            }
            else if(tempEvent->getDiskDone()->getAlg() == 3)
            {
                Request *tempReq = pickUpDisk->finishRequest(totalTime);
                double reqTime = tempReq->time();
                double timeInit = pickUpDisk->getInitTime(reqTime);
                std::ofstream pickUpOut("PICKUP_output", std::ios_base::app);
                pickUpOut << std::setw(3) << pickUpDisk->getRequestNumber(reqTime) << std::setw(10) << tempReq->track() << std::setw(8) << tempReq->sector() << std::setw(12) << tempReq->time() << std::setw(12)
                << timeInit << std::setw(12) << totalTime << std::setw(12) << timeInit - reqTime << std::setw(12) << totalTime - timeInit << std::setw(12) << (totalTime - tempReq->time()) << "\n";
                pickUpOut.close();
            }
            else if(tempEvent->getDiskDone()->getAlg() == 4)
            {
                Request *tempReq = lookDisk->finishRequest(totalTime);
                double reqTime = tempReq->time();
                double timeInit = lookDisk->getInitTime(reqTime);
                std::ofstream lookOut("LOOK_output", std::ios_base::app);
                lookOut << std::setw(3) << lookDisk->getRequestNumber(reqTime) << std::setw(10) << tempReq->track() << std::setw(8) << tempReq->sector() << std::setw(12) << tempReq->time() << std::setw(12)
                << timeInit << std::setw(12) << totalTime << std::setw(12) << timeInit - reqTime << std::setw(12) << totalTime - timeInit << std::setw(12) << (totalTime - tempReq->time()) << "\n";
                lookOut.close();
            }
            else if(tempEvent->getDiskDone()->getAlg() == 5)
            {
                Request *tempReq = cLookDisk->finishRequest(totalTime);
                double reqTime = tempReq->time();
                double timeInit = cLookDisk->getInitTime(reqTime);
                std::ofstream cLookOut("CLOOK_output", std::ios_base::app);
                cLookOut << std::setw(3) << cLookDisk->getRequestNumber(reqTime) << std::setw(10) << tempReq->track() << std::setw(8) << tempReq->sector() << std::setw(12) << tempReq->time() << std::setw(12)
                << timeInit << std::setw(12) << totalTime << std::setw(12) << timeInit - reqTime << std::setw(12) << totalTime - timeInit << std::setw(12) << (totalTime - tempReq->time()) << "\n";
                cLookOut.close();
            }
            delete tempEvent;

        }
        else if(tempEvent->isTimer())
        {
            totalTime = tempEvent->getTimer()->getTime();
            fcfsDisk->timerInterrupt(totalTime);
            sameTrackDisk->timerInterrupt(totalTime);
            pickUpDisk->timerInterrupt(totalTime);
            lookDisk->timerInterrupt(totalTime);
            cLookDisk->timerInterrupt(totalTime);
            if(!simQueue->isEmpty())
            {
                Event *newTimer = new Event();
                newTimer->addTimer(new Timer(totalTime + 50));
                simQueue->addEvent(newTimer);
                delete tempEvent;
            }
        }
    }
}

void Simulation::processDisk()
{
    double fcfsTime = fcfsDisk->serviceRequest(totalTime);
    if(fcfsTime >= 0)
    {
        fcfsTime += totalTime;
        Event *fcfsEvent = new Event();
        fcfsEvent->addDiskDone(new DiskDone(fcfsTime, 1));
        simQueue->addEvent(fcfsEvent);
    }

    double sameTrackTime = sameTrackDisk->serviceRequest(totalTime);
    if(sameTrackTime >= 0)
    {
        sameTrackTime += totalTime;
        Event *sameTrackEvent = new Event();
        sameTrackEvent->addDiskDone(new DiskDone(sameTrackTime, 2));
        simQueue->addEvent(sameTrackEvent);
    }

    double pickUpTime = pickUpDisk->serviceRequest(totalTime);
    if(pickUpTime >= 0)
    {
        pickUpTime += totalTime;
        Event *pickUpEvent = new Event();
        pickUpEvent->addDiskDone(new DiskDone(pickUpTime, 3));
        simQueue->addEvent(pickUpEvent);
    }

    double lookTime = lookDisk->serviceRequest(totalTime);
    if(lookTime >= 0)
    {
        lookTime += totalTime;
        Event *lookEvent = new Event();
        lookEvent->addDiskDone(new DiskDone(lookTime, 4));
        simQueue->addEvent(lookEvent);
    }

    double cLookTime = cLookDisk->serviceRequest(totalTime);
    if(cLookTime >= 0)
    {
        cLookTime += totalTime;
        Event *cLookEvent = new Event();
        cLookEvent->addDiskDone(new DiskDone(cLookTime, 5));
        simQueue->addEvent(cLookEvent);
    }

}

void Simulation::outPutSummary()
{
    std::ofstream out("SUMMARY_output");

    out << std::left << std::setw(8) << " Name" << std::setw(24) << "   Time In System" << std::setw(24) << "      Wait Time" << std::setw(24) << "    Service Time" << std::setw(16) << " Num in Queue" << "\r\n";
    out << std::setw(8) << " " << std::setw (8) << "Min" << std::setw(8) << "Max" << std::setw(8) << "Avg" << std::setw(8) << "Min" << std::setw(8) << "Max" << std::setw(8) << "Avg" << std::setw(8) << "Min" << std::setw(8) << "Max" << std::setw(8) << "Avg" <<
            std::setw(8) << "Max" << std::setw(8) << "Avg" << "\n";

    out << std::setw(8) << "FCFS" << std::setw (8) << fcfsDisk->timeInSystemSmallest() << std::setw(8) << fcfsDisk->timeInSystemLargest() << std::setw(8) << fcfsDisk->timeInSystemAvg() << std::setw(8) << fcfsDisk->waitTimeSmallest() << std::setw(8) << fcfsDisk->waitTimeLargest()
        << std::setw(8) << fcfsDisk->waitTimeAvg() << std::setw(8) << fcfsDisk->serviceTimeSmallest() << std::setw(8) << fcfsDisk->serviceTimeLargest() << std::setw(8) << fcfsDisk->serviceTimeAvg() << std::setw(8) << fcfsDisk->getMaxLength() << std::setw(8) << fcfsDisk->getAvgLength() << "\n";

    out << std::setw(8) << "STRACK" << std::setw (8) << sameTrackDisk->timeInSystemSmallest() << std::setw(8) << sameTrackDisk->timeInSystemLargest() << std::setw(8) << sameTrackDisk->timeInSystemAvg() << std::setw(8) << sameTrackDisk->waitTimeSmallest() << std::setw(8) <<
        sameTrackDisk->waitTimeLargest() << std::setw(8) << sameTrackDisk->waitTimeAvg() << std::setw(8) << sameTrackDisk->serviceTimeSmallest() << std::setw(8) << sameTrackDisk->serviceTimeLargest() << std::setw(8) << sameTrackDisk->serviceTimeAvg() << std::setw(8)
        << sameTrackDisk->getMaxLength() << std::setw(8) << sameTrackDisk->getAvgLength() << "\n";

    out << std::setw(8) << "PICKUP" << std::setw (8) << pickUpDisk->timeInSystemSmallest() << std::setw(8) << pickUpDisk->timeInSystemLargest() << std::setw(8) << pickUpDisk->timeInSystemAvg() << std::setw(8) << pickUpDisk->waitTimeSmallest() << std::setw(8) <<
        pickUpDisk->waitTimeLargest() << std::setw(8) << pickUpDisk->waitTimeAvg() << std::setw(8) << pickUpDisk->serviceTimeSmallest() << std::setw(8) << pickUpDisk->serviceTimeLargest() << std::setw(8) << pickUpDisk->serviceTimeAvg() << std::setw(8)
        << pickUpDisk->getMaxLength() << std::setw(8) << pickUpDisk->getAvgLength() << "\n";

    out << std::setw(8) << "LOOK" << std::setw (8) << lookDisk->timeInSystemSmallest() << std::setw(8) << lookDisk->timeInSystemLargest() << std::setw(8) << lookDisk->timeInSystemAvg() << std::setw(8) << lookDisk->waitTimeSmallest() << std::setw(8) <<
        lookDisk->waitTimeLargest() << std::setw(8) << lookDisk->waitTimeAvg() << std::setw(8) << lookDisk->serviceTimeSmallest() << std::setw(8) << lookDisk->serviceTimeLargest() << std::setw(8) << lookDisk->serviceTimeAvg() << std::setw(8)
        << lookDisk->getMaxLength() << std::setw(8) << lookDisk->getAvgLength() << "\n";

    out << std::setw(8) << "CLOOK" << std::setw (8) << cLookDisk->timeInSystemSmallest() << std::setw(8) << cLookDisk->timeInSystemLargest() << std::setw(8) << cLookDisk->timeInSystemAvg() << std::setw(8) << cLookDisk->waitTimeSmallest() << std::setw(8) <<
        cLookDisk->waitTimeLargest() << std::setw(8) << cLookDisk->waitTimeAvg() << std::setw(8) << cLookDisk->serviceTimeSmallest() << std::setw(8) << cLookDisk->serviceTimeLargest() << std::setw(8) << cLookDisk->serviceTimeAvg() << std::setw(8)
        << cLookDisk->getMaxLength() << std::setw(8) << cLookDisk->getAvgLength() << "\n";
}
