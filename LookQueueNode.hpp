#ifndef __LookUpQueueNode_hpp
#define __LookUpQueueNode_hpp

#include "FCFSQueue.hpp"

class Request;

class LookUpQueueNode {
public:
    LookUpQueueNode(Request *req, LookUpQueueNode *nextPtr);
    LookUpQueueNode(Request *req);
    LookUpQueueNode *next();
    void next(LookUpQueueNode *node);
    bool sameTracksEmpty();
    int getTrack();
    FCFSQueue *getFCFS();

private:
    LookUpQueueNode *_next;
    FCFSQueue *sameTracks;
    int trackNum;
};

#endif
