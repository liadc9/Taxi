//
// Created by gal on 30/11/16.
//

#ifndef TAXI_DRIVER_H
#define TAXI_DRIVER_H


#include "ITaxiCab.h"
#include "Passenger.h"
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

class Passenger;
enum Status{Single, Marride, Divorced, Widowed};

class Driver {
private:
    int id;
    int age;
    int experience;
    double satisfaction;
    ITaxiCab* taxiCabInfo;
    Status status;
    Passenger* customer;
    bool onTrip;
    int taxiID;

public:
    Driver();
    Driver(int id, int age, int expirience, double satisfaction,
           ITaxiCab* taxiCabInfo, Status status,
           Passenger* customer, bool onTrip, int taxiID);

    bool isOnTrip();

    void setOnTrip(bool onTrip);

    int getId();

    int getAge();

    int getExperience();

    double getSatisfaction();

    ITaxiCab* getTaxiCabInfo();

    Status getStatus();

    void setId(int id);

    void setAge(int age);

    void setExperience(int expirience);

    void setSatisfaction(double satisfaction);

    void setTaxiCabInfo(ITaxiCab *taxiCabInfo);

    void setStatus(Status status);

    void setCustomer(Passenger *customer);

    Passenger* getCustomer();

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & id;
        ar & age;
        ar & experience;
        ar & satisfaction;
        ar & taxiCabInfo;
        ar & status;
        ar & customer;
        ar & onTrip;
    }
};


#endif //TAXI_DRIVER_H
