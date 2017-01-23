/**
 * this class includes all methds specifically for luxury cab
 */

#include "LuxuryCab.h"
#include "Grid.h"
#include "Trip.h"
#include "BFS.h"
/**
 * this mehod is used for creating the move method for a lexury ab on the grid
 * @param start - start position of the cab
 * @param rideStart - end position (pos of customer for start, or fin pos for ride)
 * @param grid - given grid.
 */
State* LuxuryCab::move(State* currentPos, vector<Point> route, Grid* grid) {
    int i = 0;
    Point posInRouteVetor;
    vector<Point>::iterator it;
    for (it = route.begin(); it < route.end(); it++, i++) {
        posInRouteVetor.setX(route.at(i).getX());
        posInRouteVetor.setY(route.at(i).getY());
        if (currentPos->getState().getX() == posInRouteVetor.getX() &&
            currentPos->getState().getY() == posInRouteVetor.getY()) {
            int sizeLeft = route.size() - i;
            if (sizeLeft < 2) {
                posInRouteVetor.setX(route.at(i + 1).getX());
                posInRouteVetor.setY(route.at(i + 1).getY());
            } else {
                posInRouteVetor.setX(route.at(i + 2).getX());
                posInRouteVetor.setY(route.at(i + 2).getY());
            }
            State *cabNewState = grid->getState(posInRouteVetor.getX(), posInRouteVetor.getY());
            setLocation(cabNewState);
            return cabNewState;
        }

    }
}

/*

    int x;
    int y;
    // new trip
    Trip* trip = new Trip(start,rideStart,grid);
    // use BFS algorithm
    BFS* bfs = new BFS(trip);
    // check size of vector of BFS route
    unsigned int sizeOfSteps = bfs->AlgoRun().size();
    // if we can only do one more step and not two
    if(sizeOfSteps == 2){
         x = bfs->getBFSreturn().at(1).getX();
         y = bfs->getBFSreturn().at(1).getY();
    }
        //otherwise make a jump of two steps
    else{
         x = bfs->getBFSreturn().at(2).getX();
         y = bfs->getBFSreturn().at(2).getY();
    }
    // change the position stored in the cab.
    State* cabNewState = grid->getState(x,y);
    setLocation(cabNewState);
    return cabNewState;
}
*/