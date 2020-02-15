#include "SameTrackQueue.hpp"
#include "Request.hpp"
#include <stdlib.h>

void SameTrackQueue::addRequest(Request *request)
{
    SameTrackQueueNode *sTNode = new SameTrackQueueNode(request);

    if(isEmpty())
    {
        head = tail = sTNode;
    }
    else
    {
        SameTrackQueueNode *iter = head;
        while(iter->next() != nullptr)
        {
            if(iter->getTrack() == request->track())
            {
                iter->getFCFS()->addRequest(request);
                return;
            }
            iter = iter->next();
        }
        iter->next(sTNode);
    }
}

Request *SameTrackQueue::getRequest()
{
    if( isEmpty() )
    {
        std::cout << "Calling FCFSQueueNode::getRequest() on empty queue. Terminating...\n";
        exit(1);
    }

    return head->getFCFS()->getRequest();
}

void SameTrackQueue::deleteHead()
{
    head->getFCFS()->deleteHead();
    if(head->getFCFS()->isEmpty())
    {
        SameTrackQueueNode *tempNode = head;
        head = head->next();
        delete tempNode;
    }
}

void SameTrackQueue::print()
{
    for(auto cur = head; cur; cur = cur->next() )
    {
        cur->getFCFS()->print();
    }
}

bool SameTrackQueue::isEmpty()
{
    return head == nullptr;
}


SameTrackQueue::~SameTrackQueue()
{
    while( head != nullptr )
    {
        SameTrackQueueNode *node = head;
        head = node->next();
        delete node;
    }
}
