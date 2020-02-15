#include "CLookQueue.hpp"
#include "FCFSQueue.hpp"
#include "Request.hpp"
#include <stdlib.h>

void CLookQueue::addRequest(Request *request)
{
    CLookQueueNode *sTNode = new CLookQueueNode(request);

    if(isEmpty())
    {
        head = tail = turningPoint = sTNode;
    }
    else
    {
        CLookQueueNode *iter;

        if(request->track() < head->getTrack())
        {
           iter = turningPoint;
           while(iter->next() != nullptr)
            {
                if(iter->getTrack() == request->track())
                {
                    iter->getFCFS()->addRequest(request);
                    return;
                }
                else if(request->track() < iter->next()->getTrack())
                {
                    sTNode->next(iter->next());
                    iter->next(sTNode);
                    return;
                }
                iter = iter->next();
            }
            iter->next(sTNode);
            tail = iter;
        }
        else
        {
            iter = head;
            while(iter->next() != nullptr)
            {
                if(iter->getTrack() == request->track())
                {
                    iter->getFCFS()->addRequest(request);
                    return;
                }
                else if(iter->next()->getTrack() < head->getTrack())
                {
                    sTNode->next(iter->next());
                    iter->next(sTNode);
                    turningPoint = sTNode;
                    return;
                }
                else if(request->track() < iter->next()->getTrack())
                {
                    sTNode->next(iter->next());
                    iter->next(sTNode);
                    return;
                }
                iter = iter->next();
            }
            iter->next(sTNode);
            tail = turningPoint = iter;
        }
    }
}

Request *CLookQueue::getRequest()
{
    if( isEmpty() )
    {
        std::cout << "Calling FCFSQueueNode::getRequest() on empty queue. Terminating...\n";
        exit(1);
    }

    return head->getFCFS()->getRequest();
}

void CLookQueue::deleteHead()
{
    head->getFCFS()->deleteHead();

    if(head->getFCFS()->isEmpty())
    {
        CLookQueueNode *tempNode = head;
        head = head->next();
        delete tempNode;
    }
}

void CLookQueue::print()
{
    std::cout << "Turning point is: ";
    turningPoint->getFCFS()->print();
    std::cout << std::endl;
    for(auto cur = head; cur; cur = cur->next() )
    {
        cur->getFCFS()->print();
    }
}

bool CLookQueue::isEmpty()
{
    return head == nullptr;
}


CLookQueue::~CLookQueue()
{
    while( head != nullptr )
    {
        CLookQueueNode *node = head;
        head = node->next();
        delete node;
    }
}


