#include "EventQueueNode.hpp"
#include <stdlib.h>

EventQueueNode::EventQueueNode(Event *e)
{
    _event = e;
    next = nullptr;
}

EventQueueNode *EventQueueNode::getNextNode()
{
    return next;
}

void EventQueueNode::setNext(EventQueueNode *node)
{
    next = node;
}

Event *EventQueueNode::getEvent()
{
    return _event;
}

double EventQueueNode::getTime()
{
    if(_event->isRequest())
    {
        return _event->getRequest()->time();
    }
    else if(_event->isDiskDone())
    {
        return _event->getDiskDone()->getTime();
    }
    else if(_event->isTimer())
    {
        return _event->getTimer()->getTime();
    }
    else
    {
        std::cout << "Error, Event is empty. Terminating program." << std::endl;
        exit(1);
    }
}
