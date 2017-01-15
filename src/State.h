
#ifndef FAST_TAXI_STATE_H
#define FAST_TAXI_STATE_H

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


class State {
public:
    State();
    //constructor
    State(Point state, State* comeFrom, bool wasHere);

    bool Comparison(State other);

    Point getState();

    State* getComeFrom();

    bool getWasHere();

    int getIsObstacle();

    void setState(Point s);

    void setComeFrom(State* s);

    void setWasHere(bool s);

    void setIsObstacle(int x);
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & isObstacle;
        ar & state;
        ar & comeFrom;
        ar & wasHere;
    }
private:
    int isObstacle;
    Point state ;
    State* comeFrom;
    bool wasHere;

};


#endif //TAXI_STATE_H
