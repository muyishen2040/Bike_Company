#ifndef EVENT_HPP_INCLUDED
#define EVENT_HPP_INCLUDED
#include <iostream>
//latest version

class Event{
friend class Company;
public:
    Event();
    void print();
private:
    std::string affair;
    int stationID;
    std::string bike_type;
    std::string userID;
    int time;
};

#endif // EVENT_HPP_INCLUDED
