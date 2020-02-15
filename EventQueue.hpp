#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include "Event.hpp"
#include "EventQueueNode.hpp"

class EventQueue
{
public:
    EventQueue();
    ~EventQueue();

    void addEvent(Event *e);
    Event *getEvent();
    bool isEmpty();

private:
    EventQueueNode *head, *tail;


};
#endif // EVENTQUEUE_H
