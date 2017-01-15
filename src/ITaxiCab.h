//
// Created by gal on 30/11/16.
//
#ifndef TAXI_TAXICAB_H
#define TAXI_TAXICAB_H

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
#include <cstring>
#include <boost/serialization/access.hpp>
#include "State.h"
#include "Grid.h"
#include "Point.h"
#include "Trip.h"

enum Color {RED = 0,BLUE = 1,GREEN = 2,PINK = 3,WHITE = 4};
enum Model{HONDA,SUBARU,TESLA,FIAT};

using namespace std;

class ITaxiCab {

protected:
    int coeficient;
    int Cab_ID;
    int distance_made;
    Color color;
    Model model;
    int speed;
    State* location;
    bool hasDriver;


public:
    ITaxiCab();
    ITaxiCab(int Cab_ID, int distance_made, Color color,
             Model model, int coeficient,
              int speed, State* location, bool hasDriver);
    ~ITaxiCab(){}

    int getCab_ID();

    int getCoeficient();

    int getDistance_made();

    Color getColor();

    Model getModel();

    int getSpeed();

    State* getLocation();

    bool isHasDriver();

    void setHasDriver(bool hasDriver);


    void setCab_ID(int Cab_ID);

    void setDistance_made(int distance_made);

    void setColor(Color color);

    void setCoeficient(int coeficient);

    void setModel(Model model);

    void setSpeed(int speed);

    void setLocation(State* location);


    virtual State* move(State* start ,State* rideStart, Grid* grid) = 0;

    friend class boost::serialization::access;
    template<class Archive>
    void  serialize(Archive &ar, const unsigned int version)
    {
        ar & Cab_ID;
        ar & distance_made;
        ar & color;
        ar & model;
        ar & coeficient;
        ar & speed;
        ar & location;
        ar & hasDriver;
    }
};
BOOST_SERIALIZATION_ASSUME_ABSTRACT(ITaxiCab)


#endif //TAXI_TAXICAB_H
