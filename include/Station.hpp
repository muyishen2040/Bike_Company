#ifndef STATION_HPP_INCLUDED
#define STATION_HPP_INCLUDED
#include "MinHeap.hpp"
#include "Queue.hpp"
#include "Event.hpp"
//latest version
class Station{
friend class Company;
public:
    Station();
    ~Station();
    void initialize(int curStation, int elecNum, int ladyNum, int roadNum);
    void printStatus();
private:
    MinHeap* electric;
    MinHeap* lady;
    MinHeap* road;
    int StationID;
    //Queue<Event>* events;
};

#endif // STATION_HPP_INCLUDED
