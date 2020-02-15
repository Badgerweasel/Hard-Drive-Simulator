#include<iostream>

#include "PickUpQueueNode.hpp"

class Request;

class PickUpQueue: public Queue {

public:
    PickUpQueue(): head(nullptr), tail(nullptr) {}

    virtual void addRequest(Request *request);

    virtual Request *getRequest();
    virtual bool isEmpty();
    virtual void print();
    virtual void deleteHead();
    virtual ~PickUpQueue();

private:
    PickUpQueueNode *head, *tail;
};
