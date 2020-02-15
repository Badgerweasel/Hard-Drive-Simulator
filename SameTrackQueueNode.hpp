#ifndef __SAMETRACKQueueNode_hpp
#define __SAMETRACKQueueNode_hpp

#include "FCFSQueue.hpp"

class Request;

class SameTrackQueueNode {
public:
    SameTrackQueueNode(Request *req, SameTrackQueueNode *nextPtr);
    SameTrackQueueNode(Request *req);
    SameTrackQueueNode *next();
    void next(SameTrackQueueNode *node);
    bool sameTracksEmpty();
    int getTrack();
    FCFSQueue *getFCFS();

private:
    SameTrackQueueNode *_next;
    FCFSQueue *sameTracks;
    int trackNum;
};

#endif
