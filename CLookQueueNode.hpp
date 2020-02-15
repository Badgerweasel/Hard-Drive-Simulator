#ifndef __CLookQueueNode_hpp
#define __CLookQueueNode_hpp

#include "FCFSQueue.hpp"

class Request;

class CLookQueueNode {
public:
    CLookQueueNode(Request *req, CLookQueueNode *nextPtr);
    CLookQueueNode(Request *req);
    CLookQueueNode *next();
    void next(CLookQueueNode *node);
    bool sameTracksEmpty();
    int getTrack();
    FCFSQueue *getFCFS();

private:
    CLookQueueNode *_next;
    FCFSQueue *sameTracks;
    int trackNum;
};

#endif
