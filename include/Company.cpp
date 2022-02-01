#include "Company.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
//latest version
using namespace std;

Company::Company(){
    stationDis = nullptr;
    stations = nullptr;
    stationNum = 0;
    pathNum = 0;
    users = new User[100000];
    userNum = 0;

    events = new Queue<Event>;

    discRate.elec = 0;
    discRate.lady = 0;
    discRate.road = 0;

    rglrRate.elec = 0;
    rglrRate.lady = 0;
    rglrRate.road = 0;

    waitFee = 0;
    rdcRate = 0;
    transFee = 0;
    revenue = 0;
    revenue = 0;
    INF = 10000000;
}

Company::~Company(){
    for(int i=1;i<=stationNum;i++)
        delete [] stationDis[i];
    delete [] stationDis;
    delete [] stations;
    delete [] users;
    events->~Queue();
    delete events;
}

void Company::initialize(){
    inputStationFile();
    inputFeeFile();
    inputMapFile();
    inputUserFile();
}

void Company::execute_part1(){
    int EventsNum = events->num;
    ofstream outFile1("part1_status.txt");
    ofstream outFile2("part1_response.txt");

    for(int i=0;i<EventsNum;i++){
        Event curEvent = events->front();
        //cout<<curEvent.affair<<endl;
        if(curEvent.affair=="rent"){
            outFile2<<curEvent.affair<<" "<<curEvent.stationID<<" "<<curEvent.bike_type<<" "<<curEvent.userID<<" "<<curEvent.time;
            if(i!=EventsNum-1){
                outFile2<<endl;
            }

            if(curEvent.bike_type=="electric"){
                
                if(stations[curEvent.stationID].electric->cnt-1>0){
                    
                    int userID = userID_Decoder(curEvent.userID);
                    users[userID].bikeID = stations[curEvent.stationID].electric->top();
                    stations[curEvent.stationID].electric->pop();
                    
                    users[userID].bike_type = curEvent.bike_type;
                    users[userID].has_bike = true;
                    users[userID].userID = curEvent.userID;
                    users[userID].rentTime = curEvent.time;
                    users[userID].fromStation = curEvent.stationID;
                    
                    outFile2<<"accept"<<endl;
                }
                else{
                    
                    int userID = userID_Decoder(curEvent.userID);
                    users[userID].bikeID = -1;
                    users[userID].bike_type = "none";
                    users[userID].has_bike = false;
                    users[userID].userID = curEvent.userID;
                    users[userID].rentTime = curEvent.time;
                    users[userID].fromStation = curEvent.stationID;
                    
                    outFile2<<"reject"<<endl;
                }
            }
            else if(curEvent.bike_type=="lady"){
                if(stations[curEvent.stationID].lady->cnt-1>0){
                    int userID = userID_Decoder(curEvent.userID);
                    users[userID].bikeID = stations[curEvent.stationID].lady->top();
                    stations[curEvent.stationID].lady->pop();

                    users[userID].bike_type = curEvent.bike_type;
                    users[userID].has_bike = true;
                    users[userID].userID = curEvent.userID;
                    users[userID].rentTime = curEvent.time;
                    users[userID].fromStation = curEvent.stationID;

                    outFile2<<"accept"<<endl;
                }
                else{
                    int userID = userID_Decoder(curEvent.userID);
                    users[userID].bikeID = -1;
                    users[userID].bike_type = "none";
                    users[userID].has_bike = false;
                    users[userID].userID = curEvent.userID;
                    users[userID].rentTime = curEvent.time;
                    users[userID].fromStation = curEvent.stationID;

                    outFile2<<"reject"<<endl;
                }
            }
            else if(curEvent.bike_type=="road"){
                if(stations[curEvent.stationID].road->cnt-1>0){
                    int userID = userID_Decoder(curEvent.userID);
                    users[userID].bikeID = stations[curEvent.stationID].road->top();
                    stations[curEvent.stationID].road->pop();

                    users[userID].bike_type = curEvent.bike_type;
                    users[userID].has_bike = true;
                    users[userID].userID = curEvent.userID;
                    users[userID].rentTime = curEvent.time;
                    users[userID].fromStation = curEvent.stationID;

                    outFile2<<"accept"<<endl;
                }
                else{
                    int userID = userID_Decoder(curEvent.userID);
                    users[userID].bikeID = -1;
                    users[userID].bike_type = "none";
                    users[userID].has_bike = false;
                    users[userID].userID = curEvent.userID;
                    users[userID].rentTime = curEvent.time;
                    users[userID].fromStation = curEvent.stationID;

                    outFile2<<"reject"<<endl;
                }
            }
        }
        else if(curEvent.affair=="return"){
            outFile2<<curEvent.affair<<" "<<curEvent.stationID<<" "<<curEvent.userID<<" "<<curEvent.time;
            if(i!=EventsNum-1){
                outFile2<<endl;
            }

            int userID = userID_Decoder(curEvent.userID);

            if(users[userID].has_bike==true){
                if(users[userID].bike_type=="electric"){
                    
                    stations[curEvent.stationID].electric->push(users[userID].bikeID);
                    
                    if(curEvent.time-users[userID].rentTime==stationDis[curEvent.stationID][users[userID].fromStation]){
                        revenue = revenue + (curEvent.time-users[userID].rentTime)*discRate.elec;
                        //cout<<"| "<<(curEvent.time-users[userID].rentTime)*discRate.elec<<" |"<<endl;
                    }
                    else if(curEvent.time-users[userID].rentTime>stationDis[curEvent.stationID][users[userID].fromStation]){
                        revenue = revenue + (curEvent.time-users[userID].rentTime)*rglrRate.elec;
                        //cout<<"| "<<(curEvent.time-users[userID].rentTime)*rglrRate.elec<<" |"<<endl;
                    }
                }
                else if(users[userID].bike_type=="lady"){
                    
                    stations[curEvent.stationID].lady->push(users[userID].bikeID);
                    
                    if(curEvent.time-users[userID].rentTime==stationDis[curEvent.stationID][users[userID].fromStation]){
                        revenue = revenue + (curEvent.time-users[userID].rentTime)*discRate.lady;
                        //cout<<"| "<<(curEvent.time-users[userID].rentTime)*discRate.lady<<" |"<<endl;
                    }
                    else if(curEvent.time-users[userID].rentTime>stationDis[curEvent.stationID][users[userID].fromStation]){
                        revenue = revenue + (curEvent.time-users[userID].rentTime)*rglrRate.lady;
                        //cout<<"| "<<(curEvent.time-users[userID].rentTime)*rglrRate.lady<<" |"<<endl;
                    }
                }
                else if(users[userID].bike_type=="road"){
                    
                    stations[curEvent.stationID].road->push(users[userID].bikeID);
                    
                    if(curEvent.time-users[userID].rentTime==stationDis[curEvent.stationID][users[userID].fromStation]){
                        revenue = revenue + (curEvent.time-users[userID].rentTime)*discRate.road;
                        //cout<<"| "<<(curEvent.time-users[userID].rentTime)*discRate.road<<" |"<<endl;
                    }
                    else if(curEvent.time-users[userID].rentTime>stationDis[curEvent.stationID][users[userID].fromStation]){
                        revenue = revenue + (curEvent.time-users[userID].rentTime)*rglrRate.road;
                        //cout<<"| "<<(curEvent.time-users[userID].rentTime)*rglrRate.road<<" |"<<endl;
                    }
                }
                users[userID].has_bike = false;
            }
        }
        events->pop();
        
    }
    
    for(int i=1;i<=stationNum;i++){
        outFile1<<i<<":"<<endl;
        outFile1<<"electric:";
        while(stations[i].electric->cnt-1>0){
            outFile1<<" "<<stations[i].electric->top();
            stations[i].electric->pop();
        }
        outFile1<<endl;

        outFile1<<"lady:";
        while(stations[i].lady->cnt-1>0){
            outFile1<<" "<<stations[i].lady->top();
            stations[i].lady->pop();
        }
        outFile1<<endl;

        outFile1<<"road:";
        while(stations[i].road->cnt-1>0){
            outFile1<<" "<<stations[i].road->top();
            stations[i].road->pop();
        }
        outFile1<<endl;
    }
    
    outFile1<<revenue;

    outFile1.close();
    outFile2.close();
    
}

void Company::execute_part2(){
    int EventsNum = events->num;
    ofstream outFile1("part2_status.txt");
    ofstream outFile2("part2_response.txt");
    for(int i=0;i<EventsNum;i++){
        Event curEvent = events->front();
        //cout<<curEvent.affair<<endl;
        if(curEvent.affair=="rent"){
            outFile2<<curEvent.affair<<" "<<curEvent.stationID<<" "<<curEvent.bike_type<<" "<<curEvent.userID<<" "<<curEvent.time;
            if(i!=EventsNum-1){
                outFile2<<endl;
            }

            if(curEvent.bike_type=="electric"){
                if(stations[curEvent.stationID].electric->cnt-1>0){
                    int userID = userID_Decoder(curEvent.userID);
                    users[userID].bikeID = stations[curEvent.stationID].electric->top();
                    stations[curEvent.stationID].electric->pop();

                    users[userID].bike_type = curEvent.bike_type;
                    users[userID].has_bike = true;
                    users[userID].userID = curEvent.userID;
                    users[userID].rentTime = curEvent.time;
                    users[userID].fromStation = curEvent.stationID;
                    users[userID].dif_Bike = false;

                    outFile2<<"accept"<<endl;
                }
                else{
                    if(stations[curEvent.stationID].lady->cnt-1>0){
                        int userID = userID_Decoder(curEvent.userID);
                        users[userID].bikeID = stations[curEvent.stationID].lady->top();
                        stations[curEvent.stationID].lady->pop();

                        users[userID].bike_type = "lady";
                        users[userID].has_bike = true;
                        users[userID].userID = curEvent.userID;
                        users[userID].rentTime = curEvent.time;
                        users[userID].fromStation = curEvent.stationID;
                        users[userID].dif_Bike = true;

                        outFile2<<"discount lady"<<endl;
                    }
                    else if(stations[curEvent.stationID].road->cnt-1>0){
                        int userID = userID_Decoder(curEvent.userID);
                        users[userID].bikeID = stations[curEvent.stationID].road->top();
                        stations[curEvent.stationID].road->pop();

                        users[userID].bike_type = "road";
                        users[userID].has_bike = true;
                        users[userID].userID = curEvent.userID;
                        users[userID].rentTime = curEvent.time;
                        users[userID].fromStation = curEvent.stationID;
                        users[userID].dif_Bike = true;

                        outFile2<<"discount road"<<endl;
                    }
                    else{
                        int userID = userID_Decoder(curEvent.userID);
                        users[userID].bikeID = -1;
                        users[userID].bike_type = "none";
                        users[userID].has_bike = false;
                        users[userID].userID = curEvent.userID;
                        users[userID].rentTime = curEvent.time;
                        users[userID].fromStation = curEvent.stationID;
                        users[userID].dif_Bike = false;

                        outFile2<<"reject"<<endl;
                    }
                }
            }
            else if(curEvent.bike_type=="lady"){
                if(stations[curEvent.stationID].lady->cnt-1>0){
                    int userID = userID_Decoder(curEvent.userID);
                    users[userID].bikeID = stations[curEvent.stationID].lady->top();
                    stations[curEvent.stationID].lady->pop();

                    users[userID].bike_type = curEvent.bike_type;
                    users[userID].has_bike = true;
                    users[userID].userID = curEvent.userID;
                    users[userID].rentTime = curEvent.time;
                    users[userID].fromStation = curEvent.stationID;
                    users[userID].dif_Bike = false;

                    outFile2<<"accept"<<endl;
                }
                else{
                    if(stations[curEvent.stationID].electric->cnt-1>0){
                        int userID = userID_Decoder(curEvent.userID);
                        users[userID].bikeID = stations[curEvent.stationID].electric->top();
                        stations[curEvent.stationID].electric->pop();

                        users[userID].bike_type = "electric";
                        users[userID].has_bike = true;
                        users[userID].userID = curEvent.userID;
                        users[userID].rentTime = curEvent.time;
                        users[userID].fromStation = curEvent.stationID;
                        users[userID].dif_Bike = true;

                        outFile2<<"discount electric"<<endl;
                    }
                    else if(stations[curEvent.stationID].road->cnt-1>0){
                        int userID = userID_Decoder(curEvent.userID);
                        users[userID].bikeID = stations[curEvent.stationID].road->top();
                        stations[curEvent.stationID].road->pop();

                        users[userID].bike_type = "road";
                        users[userID].has_bike = true;
                        users[userID].userID = curEvent.userID;
                        users[userID].rentTime = curEvent.time;
                        users[userID].fromStation = curEvent.stationID;
                        users[userID].dif_Bike = true;

                        outFile2<<"discount road"<<endl;
                    }
                    else{
                        int userID = userID_Decoder(curEvent.userID);
                        users[userID].bikeID = -1;
                        users[userID].bike_type = "none";
                        users[userID].has_bike = false;
                        users[userID].userID = curEvent.userID;
                        users[userID].rentTime = curEvent.time;
                        users[userID].fromStation = curEvent.stationID;
                        users[userID].dif_Bike = false;

                        outFile2<<"reject"<<endl;
                    }
                }
            }
            else if(curEvent.bike_type=="road"){
                if(stations[curEvent.stationID].road->cnt-1>0){
                    int userID = userID_Decoder(curEvent.userID);
                    users[userID].bikeID = stations[curEvent.stationID].road->top();
                    stations[curEvent.stationID].road->pop();

                    users[userID].bike_type = curEvent.bike_type;
                    users[userID].has_bike = true;
                    users[userID].userID = curEvent.userID;
                    users[userID].rentTime = curEvent.time;
                    users[userID].fromStation = curEvent.stationID;
                    users[userID].dif_Bike = false;

                    outFile2<<"accept"<<endl;
                }
                else{
                    if(stations[curEvent.stationID].electric->cnt-1>0){
                        int userID = userID_Decoder(curEvent.userID);
                        users[userID].bikeID = stations[curEvent.stationID].electric->top();
                        stations[curEvent.stationID].electric->pop();

                        users[userID].bike_type = "electric";
                        users[userID].has_bike = true;
                        users[userID].userID = curEvent.userID;
                        users[userID].rentTime = curEvent.time;
                        users[userID].fromStation = curEvent.stationID;
                        users[userID].dif_Bike = true;

                        outFile2<<"discount electric"<<endl;
                    }
                    else if(stations[curEvent.stationID].lady->cnt-1>0){
                        int userID = userID_Decoder(curEvent.userID);
                        users[userID].bikeID = stations[curEvent.stationID].lady->top();
                        stations[curEvent.stationID].lady->pop();

                        users[userID].bike_type = "lady";
                        users[userID].has_bike = true;
                        users[userID].userID = curEvent.userID;
                        users[userID].rentTime = curEvent.time;
                        users[userID].fromStation = curEvent.stationID;
                        users[userID].dif_Bike = true;

                        outFile2<<"discount lady"<<endl;
                    }
                    else{
                        int userID = userID_Decoder(curEvent.userID);
                        users[userID].bikeID = -1;
                        users[userID].bike_type = "none";
                        users[userID].has_bike = false;
                        users[userID].userID = curEvent.userID;
                        users[userID].rentTime = curEvent.time;
                        users[userID].fromStation = curEvent.stationID;
                        users[userID].dif_Bike = false;

                        outFile2<<"reject"<<endl;
                    }
                }
            }
        }
        else if(curEvent.affair=="return"){
            outFile2<<curEvent.affair<<" "<<curEvent.stationID<<" "<<curEvent.userID<<" "<<curEvent.time;
            if(i!=EventsNum-1){
                outFile2<<endl;
            }

            int userID = userID_Decoder(curEvent.userID);

            if(users[userID].has_bike==true){
                if(users[userID].bike_type=="electric"){
                    stations[curEvent.stationID].electric->push(users[userID].bikeID);
                    if(curEvent.time-users[userID].rentTime==stationDis[curEvent.stationID][users[userID].fromStation]){
                        if(users[userID].dif_Bike==true){
                            double tmp = double(discRate.elec)*rdcRate;
                            int newRate = int(round(tmp));
                            revenue = revenue + (curEvent.time-users[userID].rentTime)*newRate;
                        }
                        else{
                            revenue = revenue + (curEvent.time-users[userID].rentTime)*discRate.elec;
                        }
                        //cout<<"| "<<(curEvent.time-users[userID].rentTime)*discRate.elec<<" |"<<endl;
                    }
                    else if(curEvent.time-users[userID].rentTime>stationDis[curEvent.stationID][users[userID].fromStation]){
                        if(users[userID].dif_Bike==true){
                            double tmp = double(rglrRate.elec)*rdcRate;
                            int newRate = int(round(tmp));
                            revenue = revenue + (curEvent.time-users[userID].rentTime)*newRate;
                        }
                        else{
                            revenue = revenue + (curEvent.time-users[userID].rentTime)*rglrRate.elec;
                        }
                        //cout<<"| "<<(curEvent.time-users[userID].rentTime)*rglrRate.elec<<" |"<<endl;
                    }
                }
                else if(users[userID].bike_type=="lady"){
                    stations[curEvent.stationID].lady->push(users[userID].bikeID);
                    if(curEvent.time-users[userID].rentTime==stationDis[curEvent.stationID][users[userID].fromStation]){
                        if(users[userID].dif_Bike==true){
                            double tmp = double(discRate.lady)*rdcRate;
                            int newRate = int(round(tmp));
                            revenue = revenue + (curEvent.time-users[userID].rentTime)*newRate;
                        }
                        else{
                            revenue = revenue + (curEvent.time-users[userID].rentTime)*discRate.lady;
                        }
                        //cout<<"| "<<(curEvent.time-users[userID].rentTime)*discRate.lady<<" |"<<endl;
                    }
                    else if(curEvent.time-users[userID].rentTime>stationDis[curEvent.stationID][users[userID].fromStation]){
                        if(users[userID].dif_Bike==true){
                            double tmp = double(rglrRate.lady)*rdcRate;
                            int newRate = int(round(tmp));
                            revenue = revenue + (curEvent.time-users[userID].rentTime)*newRate;
                        }
                        else{
                            revenue = revenue + (curEvent.time-users[userID].rentTime)*rglrRate.lady;
                        }
                        //cout<<"| "<<(curEvent.time-users[userID].rentTime)*rglrRate.lady<<" |"<<endl;
                    }
                }
                else if(users[userID].bike_type=="road"){
                    stations[curEvent.stationID].road->push(users[userID].bikeID);
                    if(curEvent.time-users[userID].rentTime==stationDis[curEvent.stationID][users[userID].fromStation]){
                        if(users[userID].dif_Bike==true){
                            double tmp = double(discRate.road)*rdcRate;
                            int newRate = int(round(tmp));
                            revenue = revenue + (curEvent.time-users[userID].rentTime)*newRate;
                        }
                        else{
                            revenue = revenue + (curEvent.time-users[userID].rentTime)*discRate.road;
                        }
                        //cout<<"| "<<(curEvent.time-users[userID].rentTime)*discRate.road<<" |"<<endl;
                    }
                    else if(curEvent.time-users[userID].rentTime>stationDis[curEvent.stationID][users[userID].fromStation]){
                        if(users[userID].dif_Bike==true){
                            double tmp = double(rglrRate.road)*rdcRate;
                            int newRate = int(round(tmp));
                            revenue = revenue + (curEvent.time-users[userID].rentTime)*newRate;
                        }
                        else{
                            revenue = revenue + (curEvent.time-users[userID].rentTime)*rglrRate.road;
                        }
                        //cout<<"| "<<(curEvent.time-users[userID].rentTime)*rglrRate.road<<" |"<<endl;
                    }
                }
                users[userID].has_bike = false;
            }
        }
        events->pop();
    }

    for(int i=1;i<=stationNum;i++){
        outFile1<<i<<":"<<endl;
        outFile1<<"electric:";
        while(stations[i].electric->cnt-1>0){
            outFile1<<" "<<stations[i].electric->top();
            stations[i].electric->pop();
        }
        outFile1<<endl;

        outFile1<<"lady:";
        while(stations[i].lady->cnt-1>0){
            outFile1<<" "<<stations[i].lady->top();
            stations[i].lady->pop();
        }
        outFile1<<endl;

        outFile1<<"road:";
        while(stations[i].road->cnt-1>0){
            outFile1<<" "<<stations[i].road->top();
            stations[i].road->pop();
        }
        outFile1<<endl;
    }

    outFile1<<revenue;

    outFile1.close();
    outFile2.close();
}

void Company::inputMapFile(){
    ifstream inFile;
    inFile.open("test_case/map.txt");
    if(inFile.fail()){
        cerr << "Error Opening File" << endl;
        exit(1);
    }
    stationDis = new int*[stationNum+1];
    for(int i=1;i<=stationNum;i++)
        stationDis[i] = new int[stationNum+1];

    for(int i=1;i<=stationNum;i++){
        for(int j=0;j<=stationNum;j++){
            stationDis[i][j] = INF;
            if(i==j){
                stationDis[i][j]=0;
            }
        }
    }
    int station1, station2, dis;
    while(!inFile.eof()){
        inFile>>station1>>station2>>dis;
        stationDis[station1][station2] = dis;
        stationDis[station2][station1] = dis;
        pathNum++;
    }
    inFile.close();
    allPairShortestPath();
}

void Company::allPairShortestPath(){
    for(int i=1;i<=stationNum;i++){
        for(int j=1;j<=stationNum;j++){
            for(int k=1;k<=stationNum;k++){
                if(stationDis[j][i]==INF||stationDis[i][k]==INF)
                    continue;
                if(stationDis[j][i]+stationDis[i][k]<stationDis[j][k])
                    stationDis[j][k] = stationDis[j][i]+stationDis[i][k];
            }
        }
    }
}

void Company::inputStationFile(){
    ifstream inFile;
    inFile.open("test_case/station.txt");
    if(inFile.fail()){
        cerr << "Error Opening File" << endl;
        exit(1);
    }
    int curStation, elecNum, ladyNum, roadNum;
    while(!inFile.eof()){
        inFile>>curStation>>elecNum>>ladyNum>>roadNum;
        if(curStation>stationNum)
            stationNum = curStation;
    }

    inFile.clear();
    inFile.seekg(0, ios::beg);

    stations = new Station[stationNum+1];

    while(!inFile.eof()){
        inFile>>curStation>>elecNum>>ladyNum>>roadNum;
        stations[curStation].initialize(curStation, elecNum, ladyNum, roadNum);
    }

    inFile.close();
}

void Company::inputFeeFile(){
    ifstream inFile;
    inFile.open("test_case/fee.txt");
    if(inFile.fail()){
        cerr << "Error Opening File" << endl;
        exit(1);
    }
    string bikeType;
    int num1, num2;
    for(int i=0;i<3;i++){
        inFile>>bikeType>>num1>>num2;
        if(bikeType=="electric"){
            discRate.elec = num1;
            rglrRate.elec = num2;
        }
        else if(bikeType=="lady"){
            discRate.lady = num1;
            rglrRate.lady = num2;
        }
        else if(bikeType=="road"){
            discRate.road = num1;
            rglrRate.road = num2;
        }
    }
    inFile>>waitFee;
    inFile>>rdcRate;
    inFile>>transFee;
    inFile.close();
}

void Company::inputUserFile(){
    ifstream inFile;
    inFile.open("test_case/user.txt");
    if(inFile.fail()){
        cerr << "Error Opening File" << endl;
        exit(1);
    }
    string affair;
    while(!inFile.eof()){
        inFile>>affair;
        if(affair=="rent"){
            int stationID, time;
            string bike_type, userID;
            inFile>>stationID>>bike_type>>userID>>time;
            Event* newEvent = new Event;

            newEvent->affair = affair;
            newEvent->bike_type = bike_type;
            newEvent->stationID = stationID;
            newEvent->userID = userID;
            newEvent->time = time;

            events->push(newEvent);
            //stations[stationID].events->push(newEvent);
            delete newEvent;
        }
        else if(affair=="return"){
            int stationID, time;
            string userID;
            inFile>>stationID>>userID>>time;
            Event* newEvent = new Event;

            newEvent->affair = affair;
            newEvent->bike_type = "none";
            newEvent->stationID = stationID;
            newEvent->userID = userID;
            newEvent->time = time;

            events->push(newEvent);

            delete newEvent;
        }
    }
    //std::cout<<events->num<<std::endl;
    inFile.close();
}

void Company::printStationStatus(){
    std::cout<<"There are "<<stationNum<<" stations."<<std::endl;
    for(int i=1;i<=stationNum;i++){
        stations[i].printStatus();
    }
    std::cout<<"----------------------------------------"<<std::endl;
    std::cout<<"The Map of Stations:"<<std::endl;
    for(int i=1;i<=stationNum;i++){
        std::cout<<"station "<<i<<" : ";
        for(int j=1;j<=stationNum;j++){
            std::cout<<stationDis[i][j]<<"  ";
        }
        std::cout<<std::endl;
    }
    std::cout<<"----------------------------------------"<<std::endl;
    std::cout<<"The price of electric bike: "<<std::endl;
    std::cout<<"Discounted: "<<discRate.elec<<" Regular: "<<rglrRate.elec<<std::endl;
    std::cout<<std::endl;
    std::cout<<"The price of lady bike: "<<std::endl;
    std::cout<<"Discounted: "<<discRate.lady<<" Regular: "<<rglrRate.lady<<std::endl;
    std::cout<<std::endl;
    std::cout<<"The price of road bike: "<<std::endl;
    std::cout<<"Discounted: "<<discRate.road<<" Regular: "<<rglrRate.road<<std::endl;
    std::cout<<"----------------------------------------"<<std::endl;
    std::cout<<"WaitFee of the company is "<<waitFee<<std::endl;
    std::cout<<"RdcRate of the company is "<<rdcRate<<std::endl;
    std::cout<<"TransFee of the company is "<<transFee<<std::endl;
    std::cout<<"The revenue of the company is "<<revenue<<" dollars."<<std::endl;
    std::cout<<"----------------------------------------"<<std::endl;
    std::cout<<"The Events of Company: "<<std::endl;
    int EventsNum = events->num;
    for(int i=0;i<EventsNum;i++){
        events->front().print();
        events->pop();
    }
    std::cout<<"----------------------------------------"<<std::endl;
}
int Company::userID_Decoder(string userID){
    if(userID.size()!=5)
        return -1;
    int ret = 0;
    int power[5] = {10000, 1000, 100, 10, 1};
    for(int i=0;i<userID.size();i++){
        int num = userID[i] - '0';
        ret = ret + power[i] * num;
    }
    return ret;
}

string Company::userID_Encoder(int userID){
    if(userID<0||userID>99999){
        return "Error";
    }
    string tmp, ret;
    for(int i=0;i<5;i++){
        int num = userID%10;
        char number = '0' + num;
        tmp.push_back(number);
        userID = userID/10;
    }
    for(int i=4;i>=0;i--){
        ret.push_back(tmp[i]);
    }
    return ret;
}
/*
class Company{
public:
    Company();
    ~Company();
    void initialize();
    void execute();
    void inputMapFile();
    void inputStationFile();
    void inputFeeFile();
    void inputUserFile();
    void allPairShortestPath();
    void userInit();
    void setRevenue();
    void printStationStatus();
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
    float rdcRate;
    int transFee;
    int revenue;
    int INF;
};
*/
