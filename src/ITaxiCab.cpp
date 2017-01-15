/**
 * The following class is used for the father class ITaxiCab,
 * father of standard and luxury cab
 */

#include "ITaxiCab.h"
#include "Trip.h"
#include "BFS.h"

/**
 * constructor for the ITaxiCab class, with all
 * features for a non specific cab
 * @param Cab_ID - id of cab
 * @param distance_made - distance made by cab
 * @param color - cab color
 * @param model - cab model
 * @param coeficient - cab coeficient for tariff
 * @param speed - car speed
 * @param location - car position on grid
 * @param hasDriver - das cab have a driver
 */
ITaxiCab::ITaxiCab(int Cab_ID, int distance_made, Color color,
                   Model model, int coeficient,
                     int speed,State* location, bool hasDriver){
    this->Cab_ID = Cab_ID;
    this->distance_made = distance_made;
    this->color = color;
    this->model = model;
    this->coeficient = coeficient;
    this->speed = speed;
    this->location = location;
    this->hasDriver = hasDriver;
}
/**
 * empty constructor
 */
ITaxiCab::ITaxiCab(){}

/**
 * getter for cab id
 * @return id
 */
int ITaxiCab::getCab_ID() {
    return Cab_ID;
}
/**
 * getter for distance made
 * @return distance
 */
int ITaxiCab::getDistance_made() {
    return distance_made;
}
/**
 * getter for cab color
 * @return color
 */
Color ITaxiCab::getColor() {
    return color;
}
/**
 * getter for cab model
 * @return model
 */
Model ITaxiCab::getModel() {
    return model;
}
/**
 * getter for cab speed
 * @return speed
 */
int ITaxiCab::getSpeed() {
    return speed;
}
/**
 * getter for cab postion
 * @return location
 */
State* ITaxiCab::getLocation() {
    return location;
}
/**
 * setter for cab id
 * @param Cab_ID
 */
void ITaxiCab::setCab_ID(int Cab_ID) {
    ITaxiCab::Cab_ID = Cab_ID;
}
/**
 * setter for distance made
 * @param distance_made
 */
void ITaxiCab::setDistance_made(int distance_made) {
    ITaxiCab::distance_made = distance_made;
}
/**
 * setter for cab color
 * @param color
 */
void ITaxiCab::setColor(Color color) {
    ITaxiCab::color = color;
}
/**
 * setter for cab model
 * @param model
 */
void ITaxiCab::setModel(Model model) {
    ITaxiCab::model = model;
}
/**
 * setter for cab speed
 * @param speed
 */
void ITaxiCab::setSpeed(int speed) {
    ITaxiCab::speed = speed;
}
/**
 * setter for cab location
 * @param location
 */
void ITaxiCab::setLocation(State* location) {
    ITaxiCab::location = location;
}
/**
 * getter for cab coefficient
 * @return coefficient
 */
int ITaxiCab::getCoeficient() {
    return coeficient;
}
/**
 * setter for cab coefficient
 * @param coeficient
 */
void ITaxiCab::setCoeficient(int coeficient) {
    ITaxiCab::coeficient = coeficient;
}
/**
 * check if cab has driver
 * @return true if has deriver
 */
bool ITaxiCab::isHasDriver(){
    return hasDriver;
}
/**
 * setter for if cab has a driver or not
 * @param hasDriver
 */
void ITaxiCab::setHasDriver(bool hasDriver) {
    ITaxiCab::hasDriver = hasDriver;
}