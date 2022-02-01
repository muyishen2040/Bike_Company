#ifndef COMPANY_HPP_INCLUDED
#define COMPANY_HPP_INCLUDED
#include "Station.hpp"
#include "Event.hpp"
#include "Queue.hpp"
//latest version
using namespace std;

struct BikeRate{
    int elec;
    int lady;
    int road;
};

struct User{
    string userID;
    string bike_type;
    int bikeID;
    int rentTime;
    int fromStation;
    bool has_bike;
    bool dif_Bike;
};


class Company{
public:
    Company();
    ~Company();
    void initialize();
    void execute_part1();
    void execute_part2();
    void inputMapFile();
    void inputStationFile();
    void inputFeeFile();
    void inputUserFile();
    void allPairShortestPath();
    void userInit();
    void setRevenue();
    void printStationStatus();
    int userID_Decoder(string userID);
    string userID_Encoder(int userID);
private:
    int** stationDis;
    Station* stations;
	int stationNum;
    int pathNum;
    User* users;
    int userNum;
    Queue<Event>* events;
    BikeRate discRate;
    BikeRate rglrRate;
	int waitFee;
    double rdcRate;
    int transFee;
    int revenue;
    int INF;
};

#endif // COMPANY_HPP_INCLUDED
