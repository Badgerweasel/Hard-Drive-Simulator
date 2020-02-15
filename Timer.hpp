#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
    Timer(double t){time = t;}
    double getTime() {return time;}
private:
    double time;
};
#endif // TIMER_H
