#include <iostream>
#include "Point.h"
#include "State.h"

using namespace std;


/**
 * empty constructor for state class
 */
State::State()
{
    isObstacle;
    Point x;
    state = x;
    comeFrom = NULL;
    wasHere = false;
}
/**
 * constructor for state class
 * @param state - the position state
 * @param comeFrom - the father of the node
 * @param wasHere - have we already been here
 */
State::State(Point state, State* comeFrom, bool wasHere) {
    this->isObstacle =0;
    this->state = state;
    this->comeFrom = comeFrom;
    this->wasHere = wasHere;

}
/**
 * comparison class is used to see if two states are the same or not
 * @param other - the second state to comare with
 * @return true if are the same
 */
bool State:: Comparison(State other)
{
    return state.getX() == other.getState().getX() && state.getY() == other.getState().getY();
}
/**
 * getter for the state of state node
 * @return state
 */
Point State::getState() {
    return state;
}
/**
 * getter for the father
 * @return pointer to father
 */
State* State::getComeFrom()
{
    return comeFrom;
}
/**
 * getter for have we been here
 * @return true if we have
 */
bool State:: getWasHere()
{
    return wasHere;
}
/**
 * getter for is there an obstacle
 * @return 1 if there is an obstacle, 0 otherwise
 */
int State::getIsObstacle(){
    return isObstacle;
}
/**
 * setter for the state position on grid
 * @param point
 */
void State::setState(Point point){
    this->state = point;
}
/**
 * setter for father of node
 * @param father
 */
void State::setComeFrom(State* father){
    comeFrom = father;

}
/**
 * setter for have we already been here
 * @param alreadyBeen
 */
void State:: setWasHere(bool alreadyBeen){
    wasHere = alreadyBeen;
}
/**
 * setter for is there an obstacle here
 * @param obstacle = 1 if there is an obstacle or 0 if there isn't
 */
void State::setIsObstacle(int obstacle){
    isObstacle = obstacle;
}
