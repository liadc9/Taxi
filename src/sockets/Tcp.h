//
// Created by gal on 16/01/17.
//

#ifndef TAXI_TCP_H
#define TAXI_TCP_H
#include "Socket.h"


class Tcp : public Socket{
public:
    Tcp(bool isServers, string ip_address, int port_num);
    virtual ~Tcp();
    int initialize();
    int acceptOneClient();
    int sendData(string data, int clientDescriptor);
    int receiveData(char* buffer, int size, int clientDescriptor);

};


#endif //TAXI_TCP_H
