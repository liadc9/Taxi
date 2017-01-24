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
    // iterate over route
    for (it = route.begin(); it < route.end(); it++, i++) {
        posInRouteVetor.setX(route.at(i).getX());
        posInRouteVetor.setY(route.at(i).getY());
        // check if we reached our position in route
        if (currentPos->getState().getX() == posInRouteVetor.getX() &&
            currentPos->getState().getY() == posInRouteVetor.getY()) {
            // advance us by two unless trip is shorter then advance by one
            int sizeLeft = route.size() - i;
            if (sizeLeft <= 2) {
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
