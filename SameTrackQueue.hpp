#include<iostream>

#include "SameTrackQueueNode.hpp"

class Request;

class SameTrackQueue: public Queue {

public:
    SameTrackQueue(): head(nullptr), tail(nullptr) {}

    virtual void addRequest(Request *request);

    virtual Request *getRequest();
    virtual bool isEmpty();
    virtual void print();
    virtual void deleteHead();
    virtual ~SameTrackQueue();

private:
    SameTrackQueueNode *head, *tail;
};
