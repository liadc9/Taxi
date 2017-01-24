/**
 * this class includes all methds specifically for standard cab
 */

#include "StandardCab.h"
#include "Trip.h"
#include "BFS.h"
/**
 * this mehod is used for creating the move method for a standard ab on the grid
 * @param start - start position of the cab
 * @param rideStart - end position (pos of customer for start, or fin pos for ride)
 * @param grid - given grid.
 */
State* StandardCab::move(State* currentPos, vector<Point> route, Grid* grid) {

    int i = 0;
    Point posInRouteVetor;
    vector<Point>::iterator it;
    // iterate over route
    for (it = route.begin(); it < route.end(); it++, i++) {
        posInRouteVetor.setX(route.at(i).getX());
        posInRouteVetor.setY(route.at(i).getY());
        // check if we reached our position in route
        if (currentPos->getState().getX() == posInRouteVetor.getX() &&
            currentPos->getState().getY() == posInRouteVetor.getY()) {
            // advance us by one
            posInRouteVetor.setX(route.at(i + 1).getX());
            posInRouteVetor.setY(route.at(i + 1).getY());
            State *cabNewState = grid->getState(posInRouteVetor.getX(), posInRouteVetor.getY());
            setLocation(cabNewState);
            return cabNewState;
        }
    }
}
