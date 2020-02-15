#include "PickUpQueue.hpp"
#include "Request.hpp"
#include <stdlib.h>

void PickUpQueue::addRequest(Request *request)
{
    PickUpQueueNode *sTNode = new PickUpQueueNode(request);

    if(isEmpty())
    {
        head = tail = sTNode;
    }
    else
    {
        PickUpQueueNode *iter = head;

        while(iter->next() != nullptr)
        {
            if(iter->getTrack() == request->track())
            {
                iter->getFCFS()->addRequest(request);
                return;
            }
            else if(iter->getTrack() > request->track() && iter->next()->getTrack() < request->track())
            {
                sTNode->next(iter->next());
                iter->next(sTNode);
                return;
            }
            else if(iter->getTrack() < request->track() && iter->next()->getTrack() > request->track())
            {
                sTNode->next(iter->next());
                iter->next(sTNode);
                return;
            }
            iter = iter->next();
        }
        iter->next(sTNode);
        tail = iter->next();
    }
}

Request *PickUpQueue::getRequest()
{
    if( isEmpty() )
    {
        std::cout << "Calling FCFSQueueNode::getRequest() on empty queue. Terminating...\n";
        exit(1);
    }

    return head->getFCFS()->getRequest();
}

void PickUpQueue::deleteHead()
{
    head->getFCFS()->deleteHead();
    if(head->getFCFS()->isEmpty())
    {
        PickUpQueueNode *tempNode = head;
        head = head->next();
        delete tempNode;
    }
}

void PickUpQueue::print()
{
    for(auto cur = head; cur; cur = cur->next() )
    {
        cur->getFCFS()->print();
    }
}

bool PickUpQueue::isEmpty()
{
    return head == nullptr;
}


PickUpQueue::~PickUpQueue()
{
    while( head != nullptr )
    {
        PickUpQueueNode *node = head;
        head = node->next();
        delete node;
    }
}
