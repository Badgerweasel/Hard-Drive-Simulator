
class Request;
#include "SameTrackQueueNode.hpp"
#include "FCFSQueue.hpp"
#include "Request.hpp"

SameTrackQueueNode::SameTrackQueueNode(Request *req, SameTrackQueueNode *nextPtr): _next(nextPtr)
{
    trackNum = req->track();
    sameTracks = new FCFSQueue();
    sameTracks->addRequest(req);
}

SameTrackQueueNode::SameTrackQueueNode(Request *req): _next(nullptr)
{
    trackNum = req->track();
    sameTracks = new FCFSQueue();
    sameTracks->addRequest(req);
}

SameTrackQueueNode *SameTrackQueueNode::next() {
    return _next;
}

void SameTrackQueueNode::next(SameTrackQueueNode *node) {
    _next = node;
}

bool SameTrackQueueNode::sameTracksEmpty()
{
    return sameTracks->isEmpty();
}

FCFSQueue *SameTrackQueueNode::getFCFS() {
    return sameTracks;
}

int SameTrackQueueNode::getTrack()
{
    return trackNum;
}
