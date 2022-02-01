#include "Event.hpp"
//latest version
Event::Event(){}

void Event::print(){
    if(affair=="rent"){
        std::cout<<affair<<" "<<stationID<<" "<<bike_type<<" "<<userID<<" "<<time<<std::endl;
    }
    else if(affair=="return"){
        std::cout<<affair<<" "<<stationID<<" "<<userID<<" "<<time<<std::endl;
    }
}
