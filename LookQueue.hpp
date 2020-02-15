#include<iostream>

#include "Queue.hpp"
#include "LookQueueNode.hpp"

class Request;

class LookUpQueue: public Queue {

public:
    LookUpQueue(): head(nullptr), tail(nullptr), turningPoint(nullptr) {inward = true;}

    virtual void addRequest(Request *request);

    virtual Request *getRequest();
    virtual bool isEmpty();
    virtual void print();
    virtual void deleteHead();
    virtual ~LookUpQueue();

private:
    LookUpQueueNode *head, *tail, *turningPoint;
    bool inward;
};
