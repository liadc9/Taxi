
#ifndef FAST_TEXI_TRIP_H
#define FAST_TEXI_TRIP_H
#include<iostream>
#include <vector>
#include "ISearchable.h"
#include "Grid.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include "Point.h"

using namespace std;

class Trip : public ISearchable
{
private:
    int ride_id;
    int numOfPassengers;
    double tariff;
    int meter_passed;
    int timeOfStart;
    bool happening;
    vector<Point> route;
    State* start;
    State* stop;
    Grid* grid;
public:
    Trip();
    Trip(int id, State* start, State* stop ,Grid* grid,
         int passengers, double tariff,int timeOfStart, bool happening);
    Trip(State* start1, State* stop1, Grid* grid1);
    virtual State* getStart();
    virtual State* getdest();
    virtual Grid* getGrid();

    int getRide_id();

    int getNumOfPassengers();

    double getTariff();

    bool getHappening();

    void setRoute(vector<Point> route);

    vector<Point> getRoute() ;

    void setHappening(bool happening);

    int getMeter_passed();

    int getTimeOfStart() ;

    void setTimeOfStart(int timeOfStart);

    void setRide_id(int ride_id);

    void setNumOfPassengers(int numOfPassengers);

    void setTariff(int tariff);

    void setMeter_passed(int meter_passed);

    void setStart(State *start);

    void setStop(State *stop);

    void setGrid(Grid *grid);

    void doRoute();

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & ride_id;
        ar & numOfPassengers;
        ar & tariff;
        ar & start;
        ar & stop;
        ar & timeOfStart;
        ar & grid;
    }

};


#endif //TAXI_TRIP_H
