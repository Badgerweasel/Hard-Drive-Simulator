#include "Event.hpp"

Event::Event()
{
    timer = diskdone = request = false;
    timerEvent = nullptr;
    requestEvent = nullptr;
    diskDoneEvent = nullptr;
}

Event::~Event()
{
    if(request)
    {
        delete requestEvent;
    }
    else if(diskdone)
    {
        delete diskDoneEvent;
    }
    else if(timer)
    {
        delete timerEvent;
    }
}

void Event::addRequest(Request *req)
{
    requestEvent = req;
    request = true;
}

void Event::addDiskDone(DiskDone *ddone)
{
    diskDoneEvent = ddone;
    diskdone = true;
}

void Event::addTimer(Timer *t)
{
    timerEvent = t;
    timer = true;
}

bool Event::isRequest()
{
    return request;
}
bool Event::isDiskDone()
{
    return diskdone;
}

bool Event::isTimer()
{
    return timer;
}

Request *Event::getRequest()
{
    return requestEvent;
}

DiskDone *Event::getDiskDone()
{
    return diskDoneEvent;
}

Timer *Event::getTimer()
{
    return timerEvent;
}

