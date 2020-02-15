#ifndef QUEUE_H
#define QUEUE_H

class Request;

class Queue {

public:
    virtual void addRequest(Request *request) = 0;
    virtual Request *getRequest() = 0;
    virtual bool isEmpty() = 0;
    virtual void print() = 0;
    virtual ~Queue() {}

};

#endif // QUEUE_H
