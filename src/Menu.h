//
// Created by liad on 13/12/16.
//

#ifndef TAXI_MENU_H
#define TAXI_MENU_H

#include <map>
#include <queue>
#include"Grid.h"
#include "Driver.h"
#include "sockets/Socket.h"

extern map<int,vector<int>*> moves;
extern vector<int> acceptVect;
extern int choice;
extern int timer;
extern int wait;
extern bool wait2;
extern bool wait3;

class Menu {
public:
    Menu();
    void online(Grid* grid,int port);
    static void* clientCreat(void* info);
    static void* clientRiciever(void* info);
    static void* tripRoute(void* info);
    static void* tripThread(void* info);

private:
/*    struct Data
    {
        int numOfDrivers;
        TaxiCenter* taxiCenter;
        int port;
        Socket* socket;
        int accept;
    };*/

};


#endif //TAXI_MENU_H
