//
// Created by liad on 13/12/16.
//

#ifndef TAXI_MENU_H
#define TAXI_MENU_H
#include "Grid.h"
#include "Driver.h"
#include "sockets/Socket.h"

class Menu {
public:
    Menu();
    void online(Grid* grid,int port);
    static void* mainThread(void *info);
    static void* clientRiciever(void *info);
    static void* tripRoute(void *info);
};


#endif //TAXI_MENU_H
