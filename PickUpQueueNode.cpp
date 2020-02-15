
class Request;
#include "PickUpQueueNode.hpp"
#include "FCFSQueue.hpp"
#include "Request.hpp"

PickUpQueueNode::PickUpQueueNode(Request *req, PickUpQueueNode *nextPtr): _next(nextPtr)
{
    trackNum = req->track();
    sameTracks = new FCFSQueue();
    sameTracks->addRequest(req);
}

PickUpQueueNode::PickUpQueueNode(Request *req): _next(nullptr)
{
    trackNum = req->track();
    sameTracks = new FCFSQueue();
    sameTracks->addRequest(req);
}

PickUpQueueNode *PickUpQueueNode::next() {
    return _next;
}

void PickUpQueueNode::next(PickUpQueueNode *node) {
    _next = node;
}

bool PickUpQueueNode::sameTracksEmpty()
{
    return sameTracks->isEmpty();
}

FCFSQueue *PickUpQueueNode::getFCFS() {
    return sameTracks;
}

int PickUpQueueNode::getTrack()
{
    return trackNum;
}
