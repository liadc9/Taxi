/**
 * The following class is used to hold all data that is need to be passed to a thread,
 * it is done by creating an abject and then it is cast by (*void) to the thread.
 */

#include "Data.h"

/**
 * constructor for data objects
 * @param numOfDrivers - the number of drivers
 * @param taxiCenter - the taxi center
 * @param port - port in use
 * @param socket - socket in use
 * @param accept - the descriptor
 * @param driver - the driver
 */
Data::Data(int numOfDrivers ,TaxiCenter* taxiCenter ,int port
        ,Socket* socket ,int accept,Driver* driver){
    this->numOfDrivers = numOfDrivers;
    this->taxiCenter = taxiCenter;
    this->port = port;
    this->socket = socket;
    this->accept = accept;
    this->driver = driver;
}

/**
 * destructor for data
 */
Data::~Data() {

}
/**
 * getter for the number of drivers
 * @return numOfDrivers
 */
int Data::getNumOfDrivers() {
    return numOfDrivers;
}
/**
 * setter for num of drivers
 * @param numOfDrivers
 */
void Data::setNumOfDrivers(int numOfDrivers) {
    Data::numOfDrivers = numOfDrivers;
}
/**
 * getter for taxi center
 * @return taxiCenter
 */
TaxiCenter *Data::getTaxiCenter() {
    return taxiCenter;
}
/**
 * setter for taxi center
 * @param taxiCenter
 */
void Data::setTaxiCenter(TaxiCenter *taxiCenter) {
    Data::taxiCenter = taxiCenter;
}
/**
 * getter for port
 * @return port
 */
int Data::getPort(){
    return port;
}
/**
 * setter for the port
 * @param port
 */
void Data::setPort(int port) {
    Data::port = port;
}
/**
 * getter for the socket
 * @return socket
 */
Socket *Data::getSocket(){
    return socket;
}
/**
 * setter for the socket
 * @param socket
 */
void Data::setSocket(Socket *socket) {
    Data::socket = socket;
}
/**
 * getter for descriptor
 * @return accept
 */
int Data::getAccept(){
    return accept;
}
/**
 * setter for descriptor
 * @param accept
 */
void Data::setAccept(int accept) {
    Data::accept = accept;
}
/**
 * getter for driver
 * @return driver
 */
Driver *Data::getDriver() {
    return driver;
}
/**
 * setter for driver
 * @param driver
 */
void Data::setDriver(Driver *driver) {
    Data::driver = driver;
}

