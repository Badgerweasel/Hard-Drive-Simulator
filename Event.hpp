#ifndef EVENT_H
#define EVENT_H

#include "Request.hpp"
#include "Timer.hpp"
#include "DiskDone.hpp"

class Event
{
public:
    Event();
    ~Event();
    void addRequest(Request *req);
    void addDiskDone(DiskDone *ddone);
    void addTimer(Timer *t);
    bool isRequest();
    bool isTimer();
    bool isDiskDone();
    Request *getRequest();
    DiskDone *getDiskDone();
    Timer *getTimer();
private:
    bool timer, request, diskdone;
    Request *requestEvent;
    Timer *timerEvent;
    DiskDone *diskDoneEvent;

};
#endif // EVENT_H
