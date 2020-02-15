#ifndef EVENTQUEUENODE_H
#define EVENTQUEUENODE_H

#include "Event.hpp"
#include <iostream>

class EventQueueNode
{
public:
    EventQueueNode(Event *e);
    void setNext(EventQueueNode *node);
    EventQueueNode *getNextNode();
    Event *getEvent();
    double getTime();

private:
    Event *_event;
    EventQueueNode *next;
};
#endif // EVENTQUEUENODE_H
