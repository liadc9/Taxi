//
// Created by gal on 16/01/17.
//

#include "Data.h"

Data::Data(int numOfDrivers ,TaxiCenter* taxiCenter ,int port ,Socket* socket ,int accept){
    this->numOfDrivers = numOfDrivers;
    this->taxiCenter = taxiCenter;
    this->port = port;
    this->socket = socket;
    this->accept = accept;
}

Data::~Data() {
    // TODO Auto-generated destructor stub
}

int Data::getNumOfDrivers() {
    return numOfDrivers;
}

void Data::setNumOfDrivers(int numOfDrivers) {
    Data::numOfDrivers = numOfDrivers;
}

TaxiCenter *Data::getTaxiCenter() {
    return taxiCenter;
}

void Data::setTaxiCenter(TaxiCenter *taxiCenter) {
    Data::taxiCenter = taxiCenter;
}

int Data::getPort(){
    return port;
}

void Data::setPort(int port) {
    Data::port = port;
}

Socket *Data::getSocket(){
    return socket;
}

void Data::setSocket(Socket *socket) {
    Data::socket = socket;
}

int Data::getAccept(){
    return accept;
}

void Data::setAccept(int accept) {
    Data::accept = accept;
}
