
class Request;
#include "LookQueueNode.hpp"
#include "FCFSQueue.hpp"
#include "Request.hpp"

LookUpQueueNode::LookUpQueueNode(Request *req, LookUpQueueNode *nextPtr): _next(nextPtr)
{
    trackNum = req->track();
    sameTracks = new FCFSQueue();
    sameTracks->addRequest(req);
}

LookUpQueueNode::LookUpQueueNode(Request *req): _next(nullptr)
{
    trackNum = req->track();
    sameTracks = new FCFSQueue();
    sameTracks->addRequest(req);
}

LookUpQueueNode *LookUpQueueNode::next() {
    return _next;
}

void LookUpQueueNode::next(LookUpQueueNode *node) {
    _next = node;
}

bool LookUpQueueNode::sameTracksEmpty()
{
    return sameTracks->isEmpty();
}

FCFSQueue *LookUpQueueNode::getFCFS() {
    return sameTracks;
}

int LookUpQueueNode::getTrack()
{
    return trackNum;
}
