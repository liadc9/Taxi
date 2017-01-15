//
// Created by gal on 28/12/16.
//

#ifndef TAXI_UDP_H
#define TAXI_UDP_H
/************************************************************
* File description: UDP header file. the class inherit from	*
* socket. methods of udp socket type						*
************************************************************/

#include "Socket.h"


class Udp: public Socket {
public:
    /***********************************************************************
    * function name: Udp												   *
    * The Input: Boolean, true - if server, false if client and port number*
    * The output: none										               *
    * The Function operation: creating new Udp						       *
    ***********************************************************************/
    Udp(bool isServers, string ip_address, int port_num);
    /***********************************************************************
    * function name: ~Udp												   *
    * The Input: none													   *
    * The output: none										               *
    * The Function operation: default destructor					       *
    ***********************************************************************/
    virtual ~Udp();
    /***********************************************************************
    * function name: initialize											   *
    * The Input: none              										   *
    * The output: int number representing the return status		           *
    * The Function operation: initialize the Socket object and getting a   *
    * socket descriptor.												   *
    ***********************************************************************/
    int initialize();
    /***********************************************************************
    * function name: sendData											   *
    * The Input: string representing the data to send		               *
    * The output: int number representing the return status		           *
    * The Function operation: sending the input data to the socket         *
    * who connect to this socket.										   *
    ***********************************************************************/
    int sendData(string data);
    /***********************************************************************
    * function name: recive	`											   *
    * The Input: none										               *
    * The output: int number representing the return status	               *
    * The Function operation: getting data from the other socket and print *
    * the data															   *
    ***********************************************************************/
    int reciveData(char* buffer, int size);

    int closeData();


};

#endif //TAXI_UDP_H
