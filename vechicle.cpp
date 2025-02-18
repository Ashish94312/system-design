// #include<bits/stdc++.h>
#include<iostream>
#include<string>
#include<map>
#include<chrono>
#include<sstream>
#include<iomanip>
#include<ctime>
#include<random>
using namespace std;


class Vehicle {
 

    private:
    string regNum;
    VehicleType vType;


    public: 
    Vehicle(const string& regNum, VehicleType vType){
        this->regNum=regNum;
        this->vType=vType;
    }

    public:
    VehicleType getVType() const {
        return vType;
    }

};




enum VehicleType{
    CAR,
    BIKE,
    TRUCK
};


/// intheritence
class BikeVehicle : public Vehicle{

    public:
    BikeVehicle(const string& regNum):Vehicle(regNum,VehicleType::BIKE){};

    // public:

    // static BikeVehicle create(const string &regNum){
    //     return BikeVehicle(regNum,VehicleType::BIKE);
    // }
    
};


class CarVechile :public Vehicle {
    public:
    CarVechile(const string &regNum):Vehicle(regNum,VehicleType::CAR){}

    // public:
    // static CarVechile create(const string &regNum){
    //     return CarVechile(regNum,VehicleType::CAR);
    // }

};


class TruckVechile :public Vehicle {
    public:
    TruckVechile(const string &regNum):Vehicle(regNum,VehicleType::TRUCK){}

    // public:
    // static CarVechile create(const string &regNum){
    //     return CarVechile(regNum,VehicleType::CAR);
    // }

};


class VehicleFactory{

    public:

    static Vehicle createVehicle(string regNum, VehicleType vType){

        switch (vType)
        {
        case CAR:
            return  CarVechile(regNum);
        case BIKE:
            return BikeVehicle(regNum);
        case TRUCK:
            return TruckVechile(regNum);
        
        default:
            break;
        }
    }
};


class ParkingLot {

    public:
    void parkVehicle(string regNum, VehicleType vType){

        // Vehicle vehicle = VehicleFactory.createVehicle(regNum, vType);
        VehicleFactory vf;
        Vehicle vehicle = vf.createVehicle(regNum, vType);

        // implement parking logic




    }
};

enum ParkingSpaceType {
    BikeParking,
    CarParking,
    TruckParking
};




class Floor {
    string floorid;
    map<ParkingSpaceType,vector<ParkingSpace>> pSpaces;

    Floor(string floorid){
        this->floorid=floorid;
        pSpaces[ParkingSpaceType::BikeParking] = {};
        pSpaces[ParkingSpaceType::CarParking] = {};
        pSpaces[ParkingSpaceType::TruckParking] = {};
    }

    void addParkingSpace(ParkingSpace p){

        // pSpaces[p.]xs

    }
    
    void removeParkingSpace(ParkingSpace p){

    }

    bool canParkVehicle(Vehicle vType) {
        // for( ParkingSpace p : )
    }

    ParkingSpaceType getSpaceTypeForVehicle(VehicleType vType){
        switch(vType){
            case CAR:
                return ParkingSpaceType::CarParking;
            case BIKE:
                return ParkingSpaceType::BikeParking;
            case TRUCK:
                return ParkingSpaceType::TruckParking;
        }

        throw invalid_argument("Invalid vehicle type");
    }

    ParkingSpace getSpace(Vehicle v) {
        vector<ParkingSpace> availableSpaces;

        for(ParkingSpace p : pSpaces[getSpaceTypeForVehicle(v.getVType())]){

        }
    }


};









class Ticket {
    private:

    string ticketid;
    const Vehicle* vehicle;

    ParkingSpace pSpaceAssigned;
    bool isActive;
    double charges;


    chrono::system_clock::time_point exitTime;
    chrono::system_clock::time_point entryTime;



    static string generateUUID(){
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int>dist(0,15);
        stringstream ss;

        for(int i=0;i<8;i++){
            ss<<hex<<dist(gen);
        }

        return ss.str();

    }

    public:
    Ticket(const Vehicle &v, const ParkingSpace& pSpace):ticketid(generateUUID()),
        entryTime(chrono::system_clock::now()),
        vehicle(&v),
        pSpaceAssigned(pSpace),
        isActive(true),
        charges(0.0) {}

    string getTicketId() {
        return ticketid;
    }

    string getEntryTime(){
        auto in_time_t = chrono::system_clock::to_time_t(entryTime);
        stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
        return ss.str();

    }

    Vehicle getVehicle()  {return *vehicle;}
    ParkingSpace getPSpaceAssigned(){return pSpaceAssigned;}

    string getExitTime() {
        if (exitTime.time_since_epoch().count()==0) return "Not set";

        auto in_time_t = chrono::system_clock::to_time_t(exitTime);

        stringstream ss;
        ss<<put_time(localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
    }

    bool getIsActive() {
        return isActive;
    }


    double getCharges(){
        return charges;
    }

    void setExitTime() {exitTime = std::chrono::system_clock::now();}
    void setIsActive(bool status) { isActive = status;}
    void setCharges(double c) {charges =c ;}

};






class ParkingSpace {

    private:
        string spaceId;
        ParkingSpaceType pType;
        Vehicle* vehicle;
        bool isEmpty;

    public:

     ParkingSpace(string spaceId, ParkingSpaceType type){
        this->spaceId =spaceId;
        this->pType = type;
        this->isEmpty = true;
     }

     void parkVehicle(Vehicle* v){
        isEmpty = false;
        vehicle = v;
     }

     void removeVehicle(){
        vehicle = nullptr;
        isEmpty = true;

     }



};

class BikeParkingSpace : public ParkingSpace {

    public:

    BikeParkingSpace(string spaceid): ParkingSpace(spaceid, ParkingSpaceType::BikeParking){};

};

class CarParkingSpace : public ParkingSpace {
    public:
    CarParkingSpace(string spaceid): ParkingSpace(spaceid,ParkingSpaceType::CarParking){};
};


class TruckParkingSpace : public ParkingSpace {
    public:
    TruckParkingSpace(string spaceid): ParkingSpace(spaceid,ParkingSpaceType::TruckParking){};
};


class ParkingStrategy {
    public:

    virtual ~ParkingStrategy() = default;
    virtual ParkingSpace* park(vector<shared_ptr<ParkingSpace>>& availableSpaces) = 0;
    

};



class ExitGate {
    string gateId;

    public:
    ExitGate(string gateId){
        this->gateId = gateId;
    }

    shared_ptr<Payment> makePayment(PaymentType pType, PaymentStrategy pStrategy,Ticket ticket){

        ticket.setExitTime();
        double cost = pStrategy.calculateCost(ticket);
        ticket.setCharges(cost);

        shared_ptr<Payment> payment = make_shared<Payment>(cost, ticket, pStrategy);

        payment -> makePayment(pType);

        ticket.setIsActive(false);

        freeParkingSpace(&ticket.getPSpaceAssigned());

        return payment;

    }

    private:
    
    void freeParkingSpace(ParkingSpace* pSpace){
        pSpace->removeVehicle();
    }



};








enum PaymentType {
    CASH,
    UPI,
};



class Payment {



};


class PaymentStrategy {

    public:
    double calculateCost(Ticket ticket);

};
 
double PaymentStrategy::calculateCost(Ticket ticket)
{
    return 0.0;
}
