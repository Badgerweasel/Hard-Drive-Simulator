#ifndef DISKDONE_H
#define DISKDONE_H

class DiskDone
{
public:
    DiskDone(double t, int a) {time = t; alg = a;}
    double getTime() {return time;}
    int getAlg() {return alg;}
private:
    double time;
    int alg; //1 = fcfs, 2 = sameTrack, 3 = pickup, 4 = look, 5 = cLook
};
#endif // DISKDONE_H
