#include<iostream>

#include "Queue.hpp"
#include "CLookQueueNode.hpp"

class Request;

class CLookQueue: public Queue {

public:
    CLookQueue(): head(nullptr), tail(nullptr), turningPoint(nullptr) {}

    virtual void addRequest(Request *request);

    virtual Request *getRequest();
    virtual bool isEmpty();
    virtual void print();
    virtual void deleteHead();
    virtual ~CLookQueue();

private:
    CLookQueueNode *head, *tail, *turningPoint;
};
