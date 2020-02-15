#include "FCFSQueue.hpp"
#include "Request.hpp"
#include <stdlib.h>

void FCFSQueue::addRequest(Request *request) {
    FCFSQueueNode *rNode = new FCFSQueueNode(request);
    if( isEmpty() ) {
        head = tail = rNode;
    } else {
        tail->next(rNode);
        tail = rNode;
    }
}

Request *FCFSQueue::getRequest() {
    if( isEmpty() ) {
        std::cout << "Calling FCFSQueueNode::getRequest() on empty queue. Terminating...\n";
        exit(1);
    }

    return head->request();
}

void FCFSQueue::deleteHead()
{
    FCFSQueueNode *tempNode = head;
    head = head->next();
    delete tempNode;
}

bool FCFSQueue::isEmpty() {
    return head == nullptr;
}

void FCFSQueue::print() {
    for(auto cur = head; cur; cur = cur->next() )
        std::cout << cur->request()->time() << " " << cur->request()->track() << " " << cur->request()->sector() << std::endl;
}

FCFSQueue::~FCFSQueue() {
    while( head != nullptr ) {
        FCFSQueueNode *node = head;
        head = node->next();
        delete node;
    }
}
