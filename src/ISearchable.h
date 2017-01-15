#include "State.h"
#include <iostream>
#include <list>
#include <vector>
#ifndef TAXI_SEARCHABLE_H
#define TAXI_SEARCHABLE_H

class State;
class Grid;


using namespace std;
class ISearchable {
public:

    virtual ~ISearchable(){}
    virtual State* getStart()=0;
    virtual State* getdest()=0;
    virtual Grid* getGrid()=0;

};


#endif //TAXI_SEARCHABLE_H
