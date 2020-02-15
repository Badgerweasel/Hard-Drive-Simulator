
class Request;
#include "CLookQueueNode.hpp"
#include "FCFSQueue.hpp"
#include "Request.hpp"

CLookQueueNode::CLookQueueNode(Request *req, CLookQueueNode *nextPtr): _next(nextPtr)
{
    trackNum = req->track();
    sameTracks = new FCFSQueue();
    sameTracks->addRequest(req);
}

CLookQueueNode::CLookQueueNode(Request *req): _next(nullptr)
{
    trackNum = req->track();
    sameTracks = new FCFSQueue();
    sameTracks->addRequest(req);
}

CLookQueueNode *CLookQueueNode::next() {
    return _next;
}

void CLookQueueNode::next(CLookQueueNode *node) {
    _next = node;
}

bool CLookQueueNode::sameTracksEmpty()
{
    return sameTracks->isEmpty();
}

FCFSQueue *CLookQueueNode::getFCFS() {
    return sameTracks;
}

int CLookQueueNode::getTrack()
{
    return trackNum;
}
