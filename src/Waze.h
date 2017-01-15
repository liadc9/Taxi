//
// Created by gal on 13/12/16.
//

#ifndef TAXI_WAZE_H
#define TAXI_WAZE_H


#include "Driver.h"

class Waze {

public:
    Driver* findClosest(vector<Driver*> vec, State* start,Grid* grid);
};


#endif //TAXI_WAZE_H
