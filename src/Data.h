//
// Created by gal on 16/01/17.
//

#ifndef TAXI_DATA_H
#define TAXI_DATA_H


#include "TaxiCenter.h"
#include "sockets/Socket.h"

class Data {
private:
    int numOfDrivers;
    TaxiCenter* taxiCenter;
    int port;
    Socket* socket;
    int accept;

public:
    Data(int numOfDrivers,TaxiCenter* taxiCenter,int port,Socket* socket,int accept);

    ~Data();

    int getNumOfDrivers();

    void setNumOfDrivers(int numOfDrivers);

    TaxiCenter *getTaxiCenter();

    void setTaxiCenter(TaxiCenter *taxiCenter);

    int getPort();

    void setPort(int port);

    Socket *getSocket();

    void setSocket(Socket *socket);

    int getAccept();

    void setAccept(int accept);

};


#endif //TAXI_DATA_H
