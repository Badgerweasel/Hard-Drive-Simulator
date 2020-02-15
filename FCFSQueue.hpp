#ifndef FCFSQUEUE_H
#define FCFSQUEUE_H


#include<iostream>

#include "Queue.hpp"
#include "FCFSQueueNode.hpp"

class Request;

class FCFSQueue: public Queue {

public:
    FCFSQueue(): head(nullptr), tail(nullptr) {}

    virtual void addRequest(Request *request);

    virtual Request *getRequest();
    virtual bool isEmpty();
    virtual void print();
    virtual void deleteHead();
    virtual ~FCFSQueue();

private:
    FCFSQueueNode *head, *tail;
};


#endif // FCFSQUEUE_H
