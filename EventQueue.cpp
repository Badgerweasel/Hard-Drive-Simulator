#include "EventQueueNode.hpp"
#include "EventQueue.hpp"
#include <stdlib.h>

EventQueue::EventQueue()
{
    head = tail = nullptr;
}

EventQueue::~EventQueue()
{
    while(head != nullptr)
    {
        EventQueueNode *deadNode = head;
        head = head->getNextNode();
        delete deadNode;
    }
}

void EventQueue::addEvent(Event *e)
{
    EventQueueNode *tempNode = new EventQueueNode(e);
    if(head == nullptr)
    {
        head = tail = tempNode;
    }
    else
    {
        EventQueueNode *iter = head;
        if(tempNode->getTime() < iter->getTime())
        {
            tempNode->setNext(head);
            head = tempNode;
            return;
        }
        while(iter->getNextNode() != nullptr)
        {
            if(tempNode->getTime() < iter->getNextNode()->getTime())
            {
                tempNode->setNext(iter->getNextNode());
                iter->setNext(tempNode);
                return;
            }
            iter = iter->getNextNode();
        }
        tail->setNext(tempNode);
        tail = tail->getNextNode();

    }
}

Event  *EventQueue::getEvent()
{
    if(isEmpty())
    {
        std::cout << "Error, Event Queue is empty. Terminating program" << std::endl;
        exit(1);
    }
    EventQueueNode *tempNode = head;
    Event *tempEvent = tempNode->getEvent();
    head = head->getNextNode();
    delete tempNode;

    return tempEvent;
}

bool EventQueue::isEmpty()
{
    return head == nullptr;
}
