
#ifndef FAST_TEXI_TAXICENTER_H
#define FAST_TEXI_TAXICENTER_H


#include "Trip.h"
#include "ITaxiCab.h"
#include "Driver.h"
#include "StandardCab.h"
#include "LuxuryCab.h"
#include "StandardCab.h"
#include <vector>

using namespace std;

class Driver;
class Passenger;

class TaxiCenter {
private:
    vector<Trip*> trips;
    vector<StandardCab*> taxis;
    vector<LuxuryCab*> luxTaxis;
    vector<Driver*> drivers;


public:
    TaxiCenter();

    void answerCall(Passenger *customer);

    Driver* tripCreator(Trip* trip);

    void AddTaxiCab(StandardCab* taxiCab);

    void AddTaxiLux(LuxuryCab* taxiCab);

    void AddTrip(Trip* trip);

    void AddDriver(Driver* driver);

    State* CabLocation(StandardCab* cab);

    State* LuxCabLocation(LuxuryCab* cab);

    vector<Trip*> getTrips();

    vector<StandardCab*> getTaxis();

    vector<LuxuryCab*> getLuxTaxis();

    vector<Driver*> getDrivers();

    void delTrip(int i);

    void delTaxis(int i);

    void delLux(int i);

    void delDriver(int i);

};


#endif //TAXI_TAXICENTER_H
