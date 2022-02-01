#include "Station.hpp"
#include <iostream>
//latest version
Station::Station(){
    electric = nullptr;
    lady = nullptr;
    road = nullptr;
    //events = new Queue<Event>;
}

Station::~Station(){
    //electric->~MinHeap();
    //lady->~MinHeap();
    //road->~MinHeap();
    delete electric;
    delete lady;
    delete road;
    //events->~Queue();
    //delete events;
}

void Station::initialize(int curStation, int elecNum, int ladyNum, int roadNum){
    StationID = curStation;
    int* arrElec = new int[elecNum];
    int* arrLady = new int[ladyNum];
    int* arrRoad = new int[roadNum];

    for(int i=0;i<elecNum;i++)
        arrElec[i] = StationID*100 + i;

    for(int i=0;i<ladyNum;i++)
        arrLady[i] = StationID*100 + i;

    for(int i=0;i<roadNum;i++)
        arrRoad[i] = StationID*100 + i;

    electric = new MinHeap(arrElec, elecNum);
    lady = new MinHeap(arrLady, ladyNum);
    road = new MinHeap(arrRoad, roadNum);

    delete [] arrElec;
    delete [] arrLady;
    delete [] arrRoad;
}

void Station::printStatus(){
    std::cout<<std::endl;
    std::cout<<"----------------------------------------"<<std::endl;
    std::cout<<"Station Number: "<<StationID<<std::endl;
    std::cout<<"Electric: ";
    for(int i=1;i<electric->cnt;i++)
        std::cout<<electric->arr[i]<<" ";
    std::cout<<std::endl;
    std::cout<<"Lady: ";
    for(int i=1;i<lady->cnt;i++)
        std::cout<<lady->arr[i]<<" ";
    std::cout<<std::endl;
    std::cout<<"Road: ";
    for(int i=1;i<road->cnt;i++)
        std::cout<<road->arr[i]<<" ";
    std::cout<<std::endl;
    std::cout<<"----------------------------------------"<<std::endl;
    std::cout<<std::endl;
}
/*
class Station{
friend class Company;
public:
    Station();
    ~Station();
    void initialize(int curStation, int elecNum, int ladyNum, int roadNum);
private:
    MinHeap<int>* electric;
    MinHeap<int>* lady;
    MinHeap<int>* road;
    int StationID;
};
*/
