/**
 * The following class is used to hold all posssible menu options class
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

using namespace std;
int choice;
int timer ;
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
    pthread_t first;
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
    // start time for the trip
    int startTime;
    // string for serialization
    string serial_str;
    Driver *driver;
    Driver *driver1;
    TaxiCenter *taxiCenter;
    taxiCenter = new TaxiCenter();
    // timer used in process online
    bool endOfRoute = false;
    choice = 0;
    timer = 0;
    // while program doesn't terminate
    while (choice != 7) {
        // get user input for choice
        cin >> choice;
        string information;
        cin.ignore();
        switch (choice) {
            // create driver
            case 1 : {

                // get number of drivers to input for server side
                cin >> choice;
                cin.ignore();
                Data *information = new Data(choice, taxiCenter, port, NULL, 0);
                int status = pthread_create(&first, NULL, mainThread, (void *) information);
                if (status) {
                    //error
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
                taxiCenter->AddTrip(trip);
    //mutex//
                int bfsStatus = pthread_create(&first, NULL, tripRoute, (void *) trip);
                if (bfsStatus) {
                    //error
                }
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
                //THIS MUST STAY
                timer++;
                //
                break;
            }

                // no default requirement
        }
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
}

void* Menu::mainThread(void* info){
    Data* data;
    data = (Data*)info;
    int currentPort = data->getPort();
    Socket* server = new Tcp(true, IP, currentPort);
    server->initialize();
    pthread_mutex_init(&driverMutex,0);
    pthread_mutex_init(&taxiMutex,0);
    pthread_mutex_init(&luxMutex,0);
    pthread_mutex_init(&tripsMutex,0);

    for(int i = 0; i < data->getNumOfDrivers(); i++){
        pthread_t t1;
        int clientNum = server->acceptOneClient();
        data->setAccept(clientNum);
        data->setSocket(server);
        int status1 = pthread_create(&t1,NULL, clientRiciever,(void*)data);
        if(status1){
            //error
        }
    }
    return NULL;
}

void* Menu::clientRiciever(void* info){
    State* newPosition;
    char buffer[1024];
    Trip *trip;
    int tripTime;
    int startTime;
    int z;
    int xCor;
    int yCor;
    int first =0;
    Data* data;
    data = (Data*)info;
    Socket* serv = data->getSocket();
    TaxiCenter* center = data->getTaxiCenter();
    Driver *driver = new Driver(0, 0, 0, 0,NULL,
                                Marride,NULL, false, 0);
    serv->receiveData(buffer, sizeof(buffer), 0);
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
    //add driver to taxicenter
    /*do lock mutex*/
    pthread_mutex_lock(&driverMutex);
    center->AddDriver(driver);
    pthread_mutex_unlock(&driverMutex);

    //assign the driver the correct taxi according to Taxi id
    for (int i = 0; i < center->getTaxis().size(); i++) {
        if (center->getTaxis().at(i)->getCab_ID() == driver->getTaxiID()) {
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
            serv->sendData(serial_str, 0);
            serial_str.clear();
        }
    }
    //assign the driver the correct taxi according to Taxi id
    for (int i = 0; i < center->getLuxTaxis().size(); i++) {
        if (center->getLuxTaxis().at(i)->getCab_ID() == driver->getTaxiID()) {
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
            serv->sendData(serial_str, 0);
            serial_str.clear();
        }
    }
    xCor = driver->getTaxiCabInfo()->getLocation()->getState().getX();
    yCor = driver->getTaxiCabInfo()->getLocation()->getState().getY();
    while(choice != 7){
        /*
         * deserialize buffer into string "waiting for move"
         */
        string ss;
        serv->receiveData(buffer, sizeof(buffer), data->getAccept());
        std::string receive(buffer, sizeof(buffer));

        if(choice == 9){
            //if driver has no trip and it is time for a trip to begin assign driver a trip
            if (driver->isOnTrip() == false ) {
                for (int i = 0; i < center->getTrips().size(); i++) {
                    if (center->getTrips().at(i)->getHappening() == false) {
                        if( first == 0){
                            if (center->getTrips().at(i)->getRide_id() == driver->getId()){
                                trip = center->getTrips().at(i);
                                pthread_mutex_lock(&tripsMutex);
                                trip->setHappening(true);
                                pthread_mutex_unlock(&tripsMutex);
                                z = i;
                                first++;
                            }
                        }
                        else if(center->getTrips().at(i)->getStart()->getState().getX() == xCor &&
                                center->getTrips().at(i)->getStart()->getState().getX() == yCor){
                                trip = center->getTrips().at(i);
                                pthread_mutex_lock(&tripsMutex);
                                trip->setHappening(true);
                                pthread_mutex_unlock(&tripsMutex);
                                z = i;
                        }
                    }
                    if (trip->getTimeOfStart() == timer) {
                        pthread_mutex_lock(&driverMutex);
                        driver->setOnTrip(true);
                        pthread_mutex_unlock(&driverMutex);
                        /*
                         * serialize route into buffer in order to send to client
                         */
                        pthread_mutex_lock(&tripsMutex);
                        vector<Point> route = trip->getRoute();
                        pthread_mutex_unlock(&tripsMutex);
                        std::string serial_str;
                        boost::iostreams::back_insert_device<std::string> inserter(serial_str);
                        boost::iostreams::stream<boost::iostreams::
                        back_insert_device<std::string> > s(inserter);
                        boost::archive::binary_oarchive oa(s);
                        oa << route;
                        s.flush();
                        serv->sendData(serial_str, data->getAccept());
                        tripTime = route.size();
                        startTime = trip->getTimeOfStart();
                        break;
                    }
                }
            }
            // if the driver is in a trip
            if (driver->isOnTrip() == true && trip->getTimeOfStart() < timer) {
                /*
                 * create next move for driver and serialize new position
                 */
                State* end = trip->getdest();
                Grid* grid = trip->getGrid();
                Driver* cabDriver =  driver;
                State* cabState = cabDriver->getTaxiCabInfo()->getLocation();
                pthread_mutex_lock(&taxiMutex);
                pthread_mutex_lock(&luxMutex);
                newPosition = cabDriver->getTaxiCabInfo()->move(cabState,end,grid);
                pthread_mutex_unlock(&tripsMutex);
                pthread_mutex_unlock(&luxMutex);
                //serialize newPosition as point
                Point* position = new Point(newPosition->getState().getX(),
                                            newPosition->getState().getY());
                std::string serial_str;
                boost::iostreams::back_insert_device<std::string> inserter(serial_str);
                boost::iostreams::stream<boost::iostreams::
                back_insert_device<std::string> > s(inserter);
                boost::archive::binary_oarchive oa(s);
                oa << position;
                s.flush();
                serv->sendData(serial_str, data->getAccept());
                serial_str.clear();
                serv->receiveData(buffer, sizeof(buffer), data->getAccept());
            }
            //if we have reached end of route for the driver
            if(timer <= (tripTime + startTime) && driver->isOnTrip() == true){
                if (trip->getTimeOfStart() < timer){
                    if (newPosition->getState().getX() == trip->getdest()->getState().getX() &&
                        newPosition->getState().getY() == trip->getdest()->getState().getY()) {
                        // after setting to false, next trip will override old trip info
                        pthread_mutex_lock(&driverMutex);
                        driver->setOnTrip(false);
                        pthread_mutex_unlock(&driverMutex);
                        //erase the trip
                        pthread_mutex_lock(&tripsMutex);
                        center->delTrip(z);
                        pthread_mutex_unlock(&tripsMutex);
                        delete trip;
                    }
                }
            }
        }
    }
    /**
    * deserialize buffer into string "waiting for move"
    */
    string ss;
    serv->receiveData(buffer, sizeof(buffer), data->getAccept());
    std::string receive(buffer, sizeof(buffer));
    // create vector empty of points to assure of end transmission
    vector<Point> endTransmission;
    //send the vector

    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << endTransmission;
    s.flush();
    serv->sendData(serial_str, data->getAccept());
    //close the socket
    delete serv;

    return NULL;
}

void* Menu::tripRoute(void* info){
    Trip* trip;
    trip = (Trip*) info;
    BFS* bfs = new BFS(trip);
    vector<Point> route = bfs->AlgoRun();
    trip->setRoute(route);
    return NULL;
}