/**
 * this class is used to hold the passenger info
 */

#include "Passenger.h"
#include "TaxiCenter.h"
/**
 * constructor for passenger
 */
Passenger::Passenger() {}
/**
 * constructor for passenger that all receives start and end point for passenger
 * @param start_point - passenger start point
 * @param end_point - passenger end point
 */
Passenger::Passenger(State* start_point, State* end_point) {
this->start_point = start_point;
this->end_point = end_point;
}
/**
 * getter for Passenger start position
 * @return position
 */
State* Passenger::getStart_point() {
    return start_point;
}
/**
 * setter for Passenger start position
 * @param start_point
 */
void Passenger::setStart_point(State* start_point) {
    Passenger::start_point = start_point;
}
/**
 * getter for Passenger end position
 * @return position
 */
State* Passenger::getEnd_point() {
    return end_point;
}
/**
 * setter for Passenger end position
 * @param end_point
 */
void Passenger::setEnd_point(State* end_point) {
    Passenger::end_point = end_point;
}
/**
 * possible way to let passenger catch a ride - not implemented yet
 * @param taxiCenter
 */
void Passenger::CatchRide(TaxiCenter* taxiCenter){

}
/**
 * possible way for customer to express satisfaction
 * @param taxiCenter - gets the taxi center.
 */
void Passenger::letSetisfaction(TaxiCenter* taxiCenter){

}
