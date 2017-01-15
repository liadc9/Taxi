//
// Created by gal on 30/11/16.
//

#ifndef TAXI_STANDARDCAB_H
#define TAXI_STANDARDCAB_H


#include "ITaxiCab.h"
#include "Grid.h"
#include "Trip.h"

class StandardCab: public ITaxiCab {

public:
    StandardCab():ITaxiCab(){};
    StandardCab(int Cab_ID, int distance_made, Color color, Model model, int coeficient, int speed,
                State* location, bool hasDriver):ITaxiCab(Cab_ID,distance_made,color,
                                          model,coeficient,speed,location, hasDriver){};

    State* move(State* start,State* rideStart,Grid* grid);
    friend class boost::serialization::access;
    template<class Archive>
    void  serialize(Archive &ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<ITaxiCab>(*this);

    }
    };


#endif //TAXI_STANDARDCAB_H
