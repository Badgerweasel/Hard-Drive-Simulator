#ifndef __PickUpQueueNode_hpp
#define __PickUpQueueNode_hpp

#include "FCFSQueue.hpp"

class Request;

class PickUpQueueNode {
public:
    PickUpQueueNode(Request *req, PickUpQueueNode *nextPtr);
    PickUpQueueNode(Request *req);
    PickUpQueueNode *next();
    void next(PickUpQueueNode *node);
    bool sameTracksEmpty();
    int getTrack();
    FCFSQueue *getFCFS();

private:
    PickUpQueueNode *_next;
    FCFSQueue *sameTracks;
    int trackNum;
};

#endif
