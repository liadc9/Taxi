/**
 * The following is the driver class that holds all indormation about the driver.
 */
#include "ITaxiCab.h"
#include "Driver.h"

/**
 * constructor for the driver class:
 * @param id - driver id
 * @param age - driver age
 * @param experience - drivers expirience
 * @param satisfaction - drivers satisfaction rating
 * @param taxiCabInfo - information about the drivers cab
 * @param status - marriage status
 * @param customer - number of passengers
 * @param onTrip - is the driver occupied with customers
 */
Driver::Driver(int id, int age, int experience, double satisfaction,
               ITaxiCab* taxiCabInfo, Status status,
               Passenger* customer, bool onTrip, int taxiID){
    this->id = id;
    this->age = age;
    this->experience = experience;
    this->satisfaction = satisfaction;
    this->taxiCabInfo = taxiCabInfo;
    this->status = status;
    this->customer = customer;
    this->onTrip = onTrip;
    this->taxiID = taxiID;
}

Driver::Driver(){}
/**
 * getter for driver id
 * @return id
 */
int Driver::getId() {
    return id;
}
/**
 * getter for driver age
 * @return age
 */
int Driver::getAge() {
    return age;
}
/**
 * getter for driver expirience
 * @return expirience
 */
int Driver::getExperience() {
    return experience;
}
/**
 * getter for customer satisfaction
 * @return satisfaction
 */
double Driver::getSatisfaction() {
    return satisfaction;
}
/**
 * getter for taxi cab information
 * @return cab info
 */
ITaxiCab* Driver::getTaxiCabInfo() {
    return taxiCabInfo;
}
/**
 * getter for driver status
 * @return status
 */
Status Driver::getStatus() {
    return status;
}
/**
 * getter for customers
 * @return customers
 */
Passenger* Driver::getCustomer() {
    return customer;
}
/**
 * setter for driver id
 * @param id
 */
void Driver::setId(int id) {
    Driver::id = id;
}
/**
 * setter for driver age
 * @param age
 */
void Driver::setAge(int age) {
    Driver::age = age;
}
/**
 * setter for driver expirience
 * @param expirience
 */
void Driver::setExperience(int expirience) {
    Driver::experience = expirience;
}
/**
 * setter for driver satisfaction
 * @param satisfaction
 */
void Driver::setSatisfaction(double satisfaction) {
    Driver::satisfaction = satisfaction;
}
/**
 * setter for taxi cab info for the driver
 * @param taxiCabInfo
 */
void Driver::setTaxiCabInfo(ITaxiCab *taxiCabInfo) {
    Driver::taxiCabInfo = taxiCabInfo;
}
/**
 * setter for driver status.
 * @param status
 */
void Driver::setStatus(Status status) {
    Driver::status = status;
}
/**
 * setter for drivers customer
 * @param customer
 */
void Driver::setCustomer(Passenger *customer) {
    Driver::customer = customer;
}
/**
 * method to check if driver is occupied
 * @return true if is occupied
 */
bool Driver::isOnTrip() {
    return onTrip;
}
/**
 * setter for if the driver is occupied.
 * @param onTrip
 */
void Driver::setOnTrip(bool onTrip) {
    Driver::onTrip = onTrip;
}