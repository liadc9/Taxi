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

extern std::map<int,std::vector<int>*> moves;
extern int choice;
extern int timer;
extern int wait;

class Menu {
public:
    Menu();
    void online(Grid* grid,int port);
    static void* clientRiciever(void* info);
    static void* tripRoute(void* info);
};


#endif //TAXI_MENU_H
