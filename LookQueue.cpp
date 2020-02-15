#include "LookQueue.hpp"
#include "FCFSQueue.hpp"
#include "Request.hpp"
#include <stdlib.h>

void LookUpQueue::addRequest(Request *request)
{
    LookUpQueueNode *sTNode = new LookUpQueueNode(request);

    if(isEmpty())
    {
        head = tail = turningPoint = sTNode;
    }
    else
    {


        if((inward && request->track() < head->getTrack()) || (!inward && request->track() > head->getTrack()))
        {
            LookUpQueueNode *iter = turningPoint;
            while(iter->next() != nullptr)
            {
                if(iter->getTrack() == request->track())
                {
                    iter->getFCFS()->addRequest(request);
                    return;
                }
                else if(inward && iter->getTrack() > request->track() && iter->next()->getTrack() < request->track())
                {
                    sTNode->next(iter->next());
                    iter->next(sTNode);
                    return;
                }
                else if(!inward && iter->getTrack() < request->track() && iter->next()->getTrack() > request->track())
                {
                    sTNode->next(iter->next());
                    iter->next(sTNode);
                    return;
                }
                iter = iter->next();
            }
            iter->next(sTNode);
            tail = sTNode;
        }
        else
        {
            LookUpQueueNode *iter = head;
            while(iter->next() != nullptr)
            {
                if(iter->getTrack() == request->track())
                {
                    iter->getFCFS()->addRequest(request);
                    return;
                }
                else if(inward && iter->next()->getTrack() < head->getTrack())
                {
                    sTNode->next(iter->next());
                    iter->next(sTNode);
                    turningPoint = iter;
                    return;
                }
                else if(!inward && iter->next()->getTrack() > head->getTrack())
                {
                    sTNode->next(iter->next());
                    iter->next(sTNode);
                    turningPoint = iter;
                    return;
                }
                else if(inward && iter->getTrack() < request->track() && iter->next()->getTrack() > request->track())
                {
                    sTNode->next(iter->next());
                    iter->next(sTNode);
                    return;
                }
                else if(!inward && iter->getTrack() > request->track() && iter->next()->getTrack() < request->track())
                {
                    sTNode->next(iter->next());
                    iter->next(sTNode);
                    return;
                }
                iter = iter->next();
            }
            iter->next(sTNode);
            tail = turningPoint = sTNode;

        }

    }
}

Request *LookUpQueue::getRequest()
{
    if( isEmpty() )
    {
        std::cout << "Calling FCFSQueueNode::getRequest() on empty queue. Terminating...\n";
        exit(1);
    }

    return head->getFCFS()->getRequest();
}

void LookUpQueue::deleteHead()
{
    head->getFCFS()->deleteHead();

    if(head->getFCFS()->isEmpty())
    {
        if(head->next() != nullptr)
        {
             if(head->next()->getTrack() < head->getTrack())
            {
                inward = false;
            }
            else
            {
                inward = true;
            }
        }
        if(turningPoint->getFCFS()->isEmpty())
        {
            turningPoint = tail;
        }

        LookUpQueueNode *tempNode = head;
        head = head->next();
        delete tempNode;
    }
}

void LookUpQueue::print()
{
    for(auto cur = head; cur; cur = cur->next() )
    {
        cur->getFCFS()->print();
    }
}

bool LookUpQueue::isEmpty()
{
    return head == nullptr;
}


LookUpQueue::~LookUpQueue()
{
    while( head != nullptr )
    {
        LookUpQueueNode *node = head;
        head = node->next();
        delete node;
    }
}


