/**
 * The following class is used to hold all posssible menu options classs
 * as well as holding all classes for thread handling.
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include <pthread.h>
#include "Menu.h"
#include "Parser.h"
#include "Driver.h"
#include "State.h"
#include "Grid.h"
#include <boost/any.hpp>
#include <sys/socket.h>
#include "ITaxiCab.h"
#include <boost/serialization/vector.hpp>
#include "BFS.h"
#include "sockets/Tcp.h"
#include "Data.h"

pthread_mutex_t driverMutex;
pthread_mutex_t taxiMutex;
pthread_mutex_t luxMutex;
pthread_mutex_t tripsMutex;
map<int,std::vector<int>*> moves;
vector<int> acceptVect;
int choice;
int choice1 = 0;
int timer ;
int wait = 0;
bool wait2 = false;
bool wait3 = false;

using namespace std;

/**
 * costrcutor for the menu
 */
Menu:: Menu(){

}
/**
 * The online function is called from the main class. it is used for the different options
 * that are possible by the taxi application.
 * press 1) adding a driver
 * press 2) adding a trip
 * press 3) adding a taxi
 * press 4) find driver location
 * press 6) get all drivers to destination
 * press 7 to quit
 * @param grid - our given grid created in main.
 */
void Menu:: online(Grid* grid, int port) {
// creates new parser object
    Parser parse;
// create a list of char data
    vector<boost::any> parsedData;
    int id;
    int age;
    char status;
    int expirience;
    int xStart;
    int yStart;
    int xEnd;
    int yEnd;
    int numPassengers;
    double tariff;
    int taxi_type;
    char manufacturer;
    char color;
    int taxiID;
    int timeOfStart;
    int z;
    Data* data;
    // start time for the trip
    int startTime;
    // string for serialization
    string serial_str;
    Driver *driver;
    Driver *driver1;
    TaxiCenter *taxiCenter;
    taxiCenter = new TaxiCenter();
    bool endOfRoute = false;
    // timers used in process online
    choice = 0;
    timer = 0;
    // mutexs used in code
    pthread_mutex_init(&driverMutex,0);
    pthread_mutex_init(&taxiMutex,0);
    pthread_mutex_init(&luxMutex,0);
    pthread_mutex_init(&tripsMutex,0);
    Socket* server = new Tcp(true, port);
    // while program doesn't terminate
    while (choice != 7) {
        // get user input for choice
        cin >> choice;
        string information;
        cin.ignore();
        switch (choice) {
            // create driver/
            case 1 : {
                pthread_t t1;
                // get number of drivers to input for server side
                cin >> choice;
                cin.ignore();
                //initialize server connection
                server->initialize();
                data = new Data(choice,taxiCenter,port,server,0,NULL);
                // creation of main thread which is used to create client threads
                int status1 = pthread_create(&t1, NULL, clientCreat, (void *) data);
                if(status1){
                    cout << "error" << endl;
                }
                pthread_join(t1,NULL);
                // while loop used to wait as we accumelate the drivers.
                while(choice != taxiCenter->getDrivers().size()){

                }
                break;
            }
                // create a trip
            case 2 : {
                getline(cin, information);
                parsedData = parse.DataSplit(information);

                // handle all info from the parser
                id = boost::any_cast<int>(parsedData[0]);
                xStart = boost::any_cast<int>(parsedData[1]);
                yStart = boost::any_cast<int>(parsedData[2]);
                xEnd = boost::any_cast<int>(parsedData[3]);
                yEnd = boost::any_cast<int>(parsedData[4]);
                numPassengers = boost::any_cast<int>(parsedData[5]);
                tariff = boost::any_cast<double>(parsedData[6]);
                timeOfStart = boost::any_cast<int>(parsedData[7]);

                State *start = new State(Point(xStart, yStart), NULL, false);
                State *end = new State(Point(xEnd, yEnd), NULL, false);

                // create trip according to all info
                Trip *trip = new Trip(id, start, end, grid, numPassengers,
                                      tariff, timeOfStart, false);
                pthread_mutex_lock(&tripsMutex);
                taxiCenter->AddTrip(trip);
                pthread_mutex_unlock(&tripsMutex);
                break;
            }
                // create a cab
            case 3 : {
                getline(cin, information);
                parsedData = parse.DataSplit(information);

                Model enumModel;
                Color enumColor;

                // get all data from parser accordingly
                id = boost::any_cast<int>(parsedData[0]);
                taxi_type = boost::any_cast<int>(parsedData[1]);
                manufacturer = boost::any_cast<char>(parsedData[2]);
                color = boost::any_cast<char>(parsedData[3]);

                if (manufacturer == 'H') {
                    enumModel = HONDA;
                } else if (manufacturer == 'S') {
                    enumModel = SUBARU;
                } else if (manufacturer == 'T') {
                    enumModel = TESLA;
                } else if (manufacturer == 'F') {
                    enumModel = FIAT;
                }

                if (color == 'R') {
                    enumColor = RED;
                } else if (color == 'B') {
                    enumColor = BLUE;
                } else if (color == 'G') {
                    enumColor = GREEN;
                } else if (color == 'P') {
                    enumColor = PINK;
                } else if (color == 'W') {
                    enumColor = WHITE;
                }
                State *location = new State(Point(0, 0), NULL, false);

                // create cab according to the data
                if (taxi_type == 1) {
                    StandardCab *cab = new StandardCab(id, 0, enumColor,
                                                       enumModel, taxi_type, 0, location, false);
                    taxiCenter->AddTaxiCab(cab);
                } else {
                    LuxuryCab *lCab = new LuxuryCab(id, 0, enumColor,
                                                    enumModel, taxi_type, 0, location, false);
                    taxiCenter->AddTaxiLux(lCab);
                }
                break;
            }
                //get position of driver
            case 4 : {
                /*
                 * when "4" is pressed by user, we iterate over all threads in
                 * acceptVect which holds all descriptors
                 * it then turns checks that the inner vector in the map
                 * "moves" for the corresponing descriptor is
                 * zero inorder to sync server and client - meaning we finished
                 * movement until 4 has been pressed.
                 */
                int i = 0;
                int posInAcceptVec = 0;
                vector<int>::iterator it;
                bool finish = false;
                while(!finish) {
                    finish = true;
                    // iterate over vector of descriptors.
                    for (it = acceptVect.begin(); it < acceptVect.end(); it++, i++) {
                        posInAcceptVec = acceptVect.at(i);
                        if (moves.at(posInAcceptVec)->size() != 0) {
                            finish = false;
                            break;
                        }
                    }
                }
                // find driver position
                int cabDriver;
                cin >> cabDriver;
                // get the driver accorind to id.
                ITaxiCab *cablocate = taxiCenter->getDrivers()
                        .at((unsigned int) cabDriver)->getTaxiCabInfo();
                int x = cablocate->getLocation()->getState().getX();
                int y = cablocate->getLocation()->getState().getY();

                Point *pos = new Point(x, y);

                cout << *pos << endl;

                delete pos;
                break;
            }
                // take all drivers to final trip position
            case 6 : {
                // get all drivers to final postion
                for (int i = 0; i < taxiCenter->getTrips().size(); i++) {
                    Trip *trip = taxiCenter->getTrips().at(i);
                    // call trip creator for the driver to send him to final location
                    taxiCenter->tripCreator(trip);
                }
                break;
            }
                // move one step forward in timer - will move drivers on grid during trips
            case 9 : {
                /*
                 * If we currnetly have no trips in motion, we iterate over the descriptor vector.
                 * we mark them all by pushing back 1 to mark there are no trips currently.
                 */
                if(!taxiCenter->getTrips().empty()) {
                    int i = 0;
                    int posInAcceptVec = 0;
                    vector<int>::iterator it;
                    //iterate over descriptor vector
                    for (it = acceptVect.begin(); it < acceptVect.end(); it++, i++) {
                        posInAcceptVec = acceptVect.at(i);
                        moves.at(posInAcceptVec)->push_back(1);
                    }
                }
                // time advancement
                timer++;
                break;
            }
                // no default requirement
        }
    }
    /*
     * when "7" is pressed by user, we iterate over all threads
     * in acceptVect which holds all descriptors
     * it then checks that the inner vector in the map "moves"
     * for the corresponing descriptor is
     * zero in order to sync server and client - meaning we finished
     * movement until 7 has been pressed.
     */
    int i = 0;
    int posInAcceptVec = 0;
    vector<int>::iterator it;
    bool finish = false;
    while(!finish) {
        finish = true;
        for (it = acceptVect.begin(); it < acceptVect.end(); it++, i++) {
            posInAcceptVec = acceptVect.at(i);
            if (moves.at(posInAcceptVec)->size() != 0) {
                finish = false;
                break;
            }
        }
    }
    /*
     * Another point use a while loop to sync server and client
     * as long as the descriptor vector isn't empty we do not proceed to delete taxi center.
     */
    wait2 = true;
    while(!acceptVect.empty()){

    }
        // remove all taxis from memory if 7 is pressed
        for (int i = taxiCenter->getTaxis().size(); i > 0; i--) {
            StandardCab *cab = taxiCenter->getTaxis().at(i - 1);
            delete cab;
            taxiCenter->getTaxis().pop_back();
        }
        // remove all luxury taxis from memory if 7 is pressed
        for (int i = taxiCenter->getLuxTaxis().size(); i > 0; i--) {
            LuxuryCab *cab = taxiCenter->getLuxTaxis().at(i - 1);
            delete cab;
            taxiCenter->getLuxTaxis().pop_back();
        }

        // remove all drivers from memory if 7 is pressed
        for (int i = taxiCenter->getDrivers().size(); i > 0; i--) {
            Driver *driver = taxiCenter->getDrivers().at(i - 1);
            delete driver;
            taxiCenter->getDrivers().pop_back();
        }
        // remove all trips from memory if 7 is pressed
        for (int i = taxiCenter->getTrips().size(); i > 0; i--) {
            Trip *trip = taxiCenter->getTrips().at(i - 1);
            delete trip->getStart();
            delete trip->getdest();
            delete trip;
            taxiCenter->getTrips().pop_back();
        }
    delete taxiCenter;
    delete server;
}
/**
 * The following method is the thread used for the creation of corresponding threads
 * for each client contacting the server. it passes info through the use of the data class
 * @param info - data recieved as *void and used here (check data class for more).
 * @return NULL.
 */
void* Menu::clientCreat(void* info){
    // data members to unload info
    Data* data1;
    Data* data;
    data1 = (Data*)info;
    // loop for creation of each client
    for(int i = 0; i < data1->getNumOfDrivers(); i++) {
        data = new Data(data1->getNumOfDrivers(),data1->getTaxiCenter(),
                        data1->getPort(), data1->getSocket(),0,NULL);
        pthread_t t2;
        // creation of client
        int clientNum = data->getSocket()->acceptOneClient();
        data->setAccept(clientNum);
        data->setSocket(data->getSocket());
        // create vector for new client in map mapping by descriptor.
        moves[clientNum] = new vector<int>;
        acceptVect.push_back(data->getAccept());
        // thread creation for client
        int status1 = pthread_create(&t2, NULL, clientRiciever, (void *) data);
        if(status1){
            cout << "error" << endl;
        }
        sleep(1);
    }

    return NULL;
}
/**
 * The following class is used in order to make all transactions
 * serialized betweeen server and a single client thread.
 * it is used to receive a driver from client, send it a taxi cab,
 * send movement to the client and use different
 * mechanism to make sure communication is fixed between the thread and server.
 * @param info - data recieved as *void and used here (check data class for more).
 * @return NULL.
 */
void* Menu::clientRiciever(void* info){
    //data memebers
    State* newPosition;
    char buffer[65536];
    Trip *trip;
    int tripTime;
    int startTime;
    int z;
    int xCor;
    int yCor;
    int first =0;
    //used to get all information from data argument
    Data* data;
    data = (Data*)info;
    int accept = data->getAccept();
    Socket* serv = data->getSocket();
    TaxiCenter* center = data->getTaxiCenter();
    Driver *driver = new Driver(0, 0, 0, 0,NULL,
                                Marride,NULL, false, 0);
    //wait for client to send driver
    serv->receiveData(buffer, sizeof(buffer), data->getAccept());
    /*
     * deserialize buffer into driver object
     */
    string serial_str(buffer, sizeof(buffer));
    boost::iostreams::basic_array_source<char> device(serial_str.c_str(),
                                                      serial_str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> >
            s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> driver;
    serial_str.clear();
    //add driver to taxicenter with mutex locks
    pthread_mutex_lock(&driverMutex);
    center->AddDriver(driver);
    pthread_mutex_unlock(&driverMutex);
    data->setDriver(driver);
    //assign the driver the correct taxi according to Taxi id
    for (int i = 0; i < center->getTaxis().size(); i++) {
        if (center->getTaxis().at(i)->getCab_ID() == driver->getId()) {
            driver->setTaxiCabInfo(center->getTaxis().at(i));
            // now the cab has a driver
            pthread_mutex_lock(&taxiMutex);
            center->getTaxis().at(i)->setHasDriver(true);
            pthread_mutex_unlock(&taxiMutex);
            /*
             * serialize ItaxiCab into buffer in order to send to client
             */
            ITaxiCab* cab = driver->getTaxiCabInfo();
            std::string serial_str;
            boost::iostreams::back_insert_device<std::string> inserter(serial_str);
            boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> >
                    s(inserter);
            boost::archive::binary_oarchive oa(s);
            oa << cab;
            s.flush();
            serv->sendData(serial_str, data->getAccept());
            serial_str.clear();
        }
    }
    //assign the driver the correct taxi according to Taxi id
    for (int i = 0; i < center->getLuxTaxis().size(); i++) {
        if (center->getLuxTaxis().at(i)->getCab_ID() == driver->getId()) {
            driver->setTaxiCabInfo(center->getLuxTaxis().at(i));
            // now the cab has a driver
            pthread_mutex_lock(&luxMutex);
            center->getLuxTaxis().at(i)->setHasDriver(true);
            pthread_mutex_unlock(&luxMutex);
            /*
             * serialize ItaxiCab into buffer in order to send to client
             */
            ITaxiCab* cab = driver->getTaxiCabInfo();
            std::string serial_str;
            boost::iostreams::back_insert_device<std::string> inserter(serial_str);
            boost::iostreams::stream<boost::iostreams::
            back_insert_device<std::string> > s(inserter);
            boost::archive::binary_oarchive oa(s);
            oa << cab;
            s.flush();
            serv->sendData(serial_str, data->getAccept());
            serial_str.clear();
        }
    }
    xCor = driver->getTaxiCabInfo()->getLocation()->getState().getX();
    yCor = driver->getTaxiCabInfo()->getLocation()->getState().getY();
    /*
     * deserialize buffer into string "waiting for move"
     */
    pthread_t bfsR;
    string ss;
    serv->receiveData(buffer, sizeof(buffer), accept);
    std::string receive(buffer, sizeof(buffer));

    wait++;
    //cration of the TripThread - tt
    pthread_t tt;
    while(choice1 != 7){
        // wait is used to sync server and client
        while(wait != data->getNumOfDrivers()){

        }
        // creat a trip thread
        int what = pthread_create(&tt,NULL,tripThread,(void*)data);
        // join thrad for sync with server
        pthread_join(tt,NULL);
        // while loop to get rid of all clients that have no trips
        while(!moves.at(data->getAccept())->empty()){
            moves.at(data->getAccept())->pop_back();
        }
        break;
    }
    /*
     * when "7" is pressed by user, we iterate over all threads in
     * acceptVect which holds all descriptors
     * it then checks that the inner vector in the map "moves"
     * for the corresponding descriptor is
     * zero in order to sync server and client - meaning we
     * finished movement until 7 has been pressed.
     */
    int i = 0;
    int posInAcceptVec = 0;
    vector<int>::iterator it;
    bool finish = false;
    while(!finish) {
        finish = true;
        for (it = acceptVect.begin(); it < acceptVect.end(); it++, i++) {
            posInAcceptVec = acceptVect.at(i);
            if (moves.at(posInAcceptVec)->size() != 0) {
                finish = false;
                break;
            }
        }
    }
    // create vector empty of points to assure of end transmission
    vector<Point> endTransmission;
    //send the vector
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << endTransmission;
    s.flush();
    serv->sendData(serial_str, accept);
    for(int k = 0 ; k < data->getNumOfDrivers(); k++){
        if(acceptVect.at(k) == data->getAccept()){
            acceptVect.erase(acceptVect.begin() + k);
            break;
        }
    }
    //close the socket
    return NULL;
}
/**
 * This method is used to represent a thread for bfs, it is called for each new trip created
 * inside of the trip thread below and creates a vector of points named the route.
 * @param info - data recieved as *void and used here (check data class for more).
 * @return NULL.
 */
void* Menu::tripRoute(void* info){
    Trip* trip;
    trip = (Trip*) info;
    BFS* bfs = new BFS(trip);
    vector<Point> route = bfs->AlgoRun();
    trip->setRoute(route);
    return NULL;
}
/**
 * This method is used to represent a thread of a trip, it is used to create a trip,
 * move along the route
 * and create serialized transactions of send receive with the client.
 * @param info - data recieved as *void and used here (check data class for more).
 * @return NULL.
 */
void* Menu::tripThread(void* info){
    int first = 0;
    int ourTime = 0;
    State* newPosition;
    char buffer[65536];
    Trip *trip;
    int tripTime;
    int startTime;
    int z;
    vector<Point> route;
    pthread_t bfsR;
    // get all info data
    Data* data;
    data = (Data*) info;
    Socket* serv = data->getSocket();
    TaxiCenter* center = data->getTaxiCenter();
    Driver* driver = data->getDriver();
    int accept = data->getAccept();
    bool endWithTrip = false;
    while(true){
        // if we have data in the vector for our client
        if(!moves[data->getAccept()]->empty()) {
            // if we have 1 at the first position in out clients vector
            if (moves[data->getAccept()]->at(0) == 1) {
                // if we have trips
                if (!center->getTrips().empty()) {
                    //if driver has no trip and it is time for a trip to begin assign driver a trip
                    if (driver->isOnTrip() == false) {
                        //iterate over trips to find correct trip to assign to driver
                        for (int i = 0; i < center->getTrips().size(); i++) {
                            if (center->getTrips().at(i)->getHappening() == false) {
                                if (first == 0) {
                                    if (center->getTrips().at(i)->getRide_id() ==
                                            driver->getId()) {
                                        trip = center->getTrips().at(i);
                                        pthread_mutex_lock(&tripsMutex);
                                        trip->setHappening(true);
                                        pthread_mutex_unlock(&tripsMutex);
                                        z = i;
                                        first++;
                                        // create a bfs thread for our trip
                                        int bfsStatus = pthread_create(&bfsR, NULL,
                                                                       tripRoute, (void *) trip);
                                        if (bfsStatus) {
                                            //error
                                        }
                                        int stat = pthread_join(bfsR, NULL);
                                        pthread_mutex_lock(&tripsMutex);
                                        route = trip->getRoute();
                                        pthread_mutex_unlock(&tripsMutex);
                                        /*
                                         * serialize route into buffer in order to send to client
                                         */
                                        std::string serial_str;
                                        boost::iostreams::back_insert_device<std::string>
                                                inserter(serial_str);
                                        boost::iostreams::stream<boost::iostreams::
                                        back_insert_device<std::string> > s(inserter);
                                        boost::archive::binary_oarchive oa(s);
                                        oa << route;
                                        s.flush();
                                        serv->sendData(serial_str, accept);
                                        tripTime = route.size();
                                        startTime = trip->getTimeOfStart();
                                        if (trip->getHappening() == true) {
                                            pthread_mutex_lock(&driverMutex);
                                            driver->setOnTrip(true);
                                            pthread_mutex_unlock(&driverMutex);
                                            break;
                                        }
                                    } else {
                                        continue;
                                    }
                                    //this isn't our first trip to assign to the driver client
                                } else if (center->getTrips().at(i)->getStart()->getState().getX()
                                           == driver->getTaxiCabInfo()->
                                        getLocation()->getState().getX() &&
                                           center->getTrips().at(i)->getStart()->getState().getY()
                                           == driver->getTaxiCabInfo()->getLocation()->
                                                   getState().getY()) {
                                    trip = center->getTrips().at(i);
                                    pthread_mutex_lock(&tripsMutex);
                                    trip->setHappening(true);
                                    pthread_mutex_unlock(&tripsMutex);
                                    z = i;
                                    // create a bfs thread for our trip
                                    int bfsStatus = pthread_create(&bfsR, NULL,
                                                                   tripRoute, (void *) trip);
                                    if (bfsStatus) {
                                        //error
                                    }
                                    int stat = pthread_join(bfsR, NULL);
                                    pthread_mutex_lock(&tripsMutex);
                                    route = trip->getRoute();
                                    pthread_mutex_unlock(&tripsMutex);
                                    /*
                                    * serialize route into buffer in order to send to client
                                    */
                                    std::string serial_str;
                                    boost::iostreams::back_insert_device<std::string>
                                            inserter(serial_str);
                                    boost::iostreams::stream<boost::iostreams::
                                    back_insert_device<std::string> > s(inserter);
                                    boost::archive::binary_oarchive oa(s);
                                    oa << route;
                                    s.flush();
                                    serv->sendData(serial_str, accept);
                                    tripTime = route.size();
                                    startTime = trip->getTimeOfStart();
                                    if (trip->getHappening() == true) {
                                        pthread_mutex_lock(&driverMutex);
                                        driver->setOnTrip(true);
                                        pthread_mutex_unlock(&driverMutex);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
                // if we are in a trip we need to make movement
                if (!center->getTrips().empty()) {
                    // if the driver is in a trip
                    if (driver->isOnTrip() == true && trip->getTimeOfStart() <= ourTime) {
                        /*
                         * create next move for driver and serialize new position
                         */
                        serv->receiveData(buffer, sizeof(buffer), data->getAccept());
                        State *end = trip->getdest();
                        Grid *grid = trip->getGrid();
                        Driver *cabDriver = driver;
                        State *cabState = cabDriver->getTaxiCabInfo()->getLocation();
                        pthread_mutex_lock(&taxiMutex);
                        pthread_mutex_lock(&luxMutex);
                        //make move
                        newPosition = cabDriver->getTaxiCabInfo()->move(cabState, route, grid);
                        pthread_mutex_unlock(&luxMutex);
                        pthread_mutex_unlock(&taxiMutex);
                        //serialize newPosition as point
                        Point *position = new Point(newPosition->getState().getX(),
                                                    newPosition->getState().getY());
                        std::string serial_str;
                        boost::iostreams::back_insert_device<std::string> inserter(serial_str);
                        boost::iostreams::stream<boost::iostreams::
                        back_insert_device<std::string> > s(inserter);
                        boost::archive::binary_oarchive oa(s);
                        oa << position;
                        s.flush();
                        serv->sendData(serial_str, accept);
                        serial_str.clear();
                        endWithTrip == false;

                    }
                    //if we have reached end of route for the driver
                    if (ourTime <= (tripTime + startTime) && driver->isOnTrip() == true) {
                        if (trip->getTimeOfStart() <= ourTime) {
                            if (newPosition->getState().getX() == trip->
                                    getdest()->getState().getX() &&
                                newPosition->getState().getY() == trip->
                                        getdest()->getState().getY()) {
                                // after setting to false, next trip will override old trip info
                                pthread_mutex_lock(&driverMutex);
                                driver->setOnTrip(false);
                                pthread_mutex_unlock(&driverMutex);
                                //erase the trip
                                pthread_mutex_lock(&tripsMutex);
                                // find the correct trip to remove
                                for (int i =0; i < center->getTrips().size(); i++){
                                    if(center->getTrips().at(i)->getRide_id() ==
                                            trip->getRide_id()){
                                        if(center->getTrips().at(i)->getHappening() ==
                                                trip->getHappening()) {
                                            if (center->getTrips().at(i)->getStart()->
                                                    getState().getX() ==
                                                trip->getStart()->getState().getX()) {
                                                if (center->getTrips().at(i)->getStart()->
                                                        getState().getY() ==
                                                    trip->getStart()->getState().getY()) {
                                                    if (center->getTrips().at(i)->getdest()->
                                                            getState().getX() ==
                                                        trip->getdest()->getState().getX()) {
                                                        if (center->getTrips().at(i)->getdest()->
                                                                getState().getY() ==
                                                            trip->getdest()->getState().getY()) {
                                                            center->delTrip(i);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                pthread_mutex_unlock(&tripsMutex);
                                delete trip;
                                endWithTrip = true;

                                /*
                                 * deserialize buffer into string "waiting for move"
                                 */
                                string ss;
                                serv->receiveData(buffer, sizeof(buffer), accept);
                                std::string receive(buffer, sizeof(buffer));
                               // break;
                            }
                        }
                    }
                }
            }
            // now we go to the vector of our client and popback to mark a trip was done
            if (!moves[data->getAccept()]->empty()) {
                moves[data->getAccept()]->pop_back();
            }
            ourTime++;
        }
        /**
         * if 7 was pressed we need to quite but if it was in the middle of a trip happening
        we are not sending an empty vector ut a point (-1,-1) to tell us we still
        need to finish everything.
         */
        if(wait2){
            if(endWithTrip == false){
                Point *sof = new Point(-1,-1);
                std::string serial_str;
                boost::iostreams::back_insert_device<std::string> inserter(serial_str);
                boost::iostreams::stream<boost::iostreams::
                back_insert_device<std::string> > s(inserter);
                boost::archive::binary_oarchive oa(s);
                oa << sof;
                s.flush();
                serv->sendData(serial_str, accept);
                serial_str.clear();
                break;
            }
            else{
                break;
            }
        }
    }
    return NULL;
}
