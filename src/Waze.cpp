/**
 * The following class holds all info for waze class
 */

#include "Waze.h"
#include "BFS.h"

using namespace std;
/**
 * This class is used to find the closest driver to our customer location.
 * @param vec - the vector of drivers
 * @param start - the customers start point
 * @param grid - our grid
 * @return the closest driver
 */
Driver* Waze::findClosest(vector<Driver*> vec, State* start,Grid* grid){
    int min ;
    int i;
    Driver* driver;
    // makes sure we only look at drivers who aren't occupied at the moment.
    for(i = 0; i < vec.size(); i++){
        if(!vec.at(i)->isOnTrip()){
            break;
        }
    }
    // get driver location.
    State* stateJ = vec.at(i)->getTaxiCabInfo()->getLocation();
    Trip* tripJ = new Trip(start, stateJ, grid);
    BFS* waze = new BFS(tripJ);
    // runs the algorith for the first unoccupied driver
    min = waze->AlgoRun().size();
    driver = vec.at(i);
    // now for all the rest of the drivers
    for(int j = i+1; j < vec.size(); j++){
        // makes sure he is vacant and finds driver location
        bool notVacant = vec.at(j)->isOnTrip();
        State* state2 = vec.at(j)->getTaxiCabInfo()->getLocation();
        Trip* trip2 = new Trip(start, stateJ, grid);
        BFS* waze2 = new BFS(tripJ);
        /*
         * runs BFS and checks route length, only if he is closer and vacant
         * we keep him as min.
         */
        if(min > waze->AlgoRun().size() && notVacant == false){
            min = waze->AlgoRun().size();
            driver = vec.at(j);
        }
        delete tripJ;
        delete waze2;
    }
    delete tripJ;
    delete waze;
    return driver;
}
