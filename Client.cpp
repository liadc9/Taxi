/**
 * This is the Client side application.
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <boost/any.hpp>
#include "src/sockets/Socket.h"
#include "src/sockets/Udp.h"
#include "src/sockets/Tcp.h"
#include "src/Parser.h"
#include "src/Driver.h"
#include "src/BFS.h"
#include <unistd.h>
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
#include <boost/serialization/vector.hpp>


BOOST_CLASS_EXPORT_GUID(LuxuryCab,"LuxuryCab")
BOOST_CLASS_EXPORT_GUID(StandardCab,"StandardCab")

using namespace std;
/**
 * The following method is th main method of the client side
 * it is used to initialize a client connection,
 * parse from user input driver info, serialize info,
 * and send the server side the serialized info.
 * the client expects to receive the correct vehicle
 * and is updates everytime there is movement on the grid
 * @param argc - num of args
 * @param argv - recevied args, the port num
 * @return 0 - end of main no errors
 */
int main(int argc, char *argv[]) {
    int id;
    int age;
    char status;
    int expirience = 0;
    int vehicle;
    int taxi_type;
    int taxiID;
    char buffer[65536];
    vector<Point> tripRoute;
    // open new socket at correct port
    Socket* client = new Tcp(false, atoi(argv[2]));

    // get driver input from user
    string driverString;
    getline (cin, driverString);

    // creates new parser object
    Parser parse;

    // create a list of int data
    vector<boost::any> parsedData;

    // parse the driver data
    parsedData = parse.DataSplit(driverString);

    //create status for driver
    Status stat;

    // properly receive all data from parser
    // get all data from parser accordingly
    try{
        if(parsedData.size() != 5){
            throw id;
        }
        id = boost::any_cast<int>(parsedData[0]);
        if(id < 0){
            throw id;
        }
    } catch(int cabError)
    {
        cout << -1 << endl;
        return 0;
    }
    age = boost::any_cast<int>(parsedData[1]);
    status = boost::any_cast<char>(parsedData[2]);
    try{
        if (status == 'S') {
            stat = Single;
        } else if (status == 'M') {
            stat = Marride;
        } else if (status == 'D') {
            stat = Divorced;
        } else if (status == 'W') {
            stat = Widowed;
        } else {
            throw status;
        }
    } catch (int statusError)
    {
        cout << -1 << endl;
        return 0;
    }

    expirience = boost::any_cast<int>(parsedData[3]);
    vehicle = boost::any_cast<int>(parsedData[4]);
    double satisfaction = 0;
    taxiID = -1;

    // initialize client
    client->initialize();

    //serialize driver
    Driver *driver = new Driver(id, age, expirience, satisfaction, NULL, stat, NULL, false, taxiID);
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    s.flush();
    // send driver to server
    client->sendData(serial_str, 0);
    serial_str.clear();


//deserialize to taxi
    ITaxiCab* taxi;
    client->receiveData(buffer, sizeof(buffer), 0);
    string serial_str2(buffer, sizeof(buffer));
    boost::iostreams::basic_array_source<char> device(serial_str2.c_str(), serial_str2.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> taxi;
    serial_str.clear();


    // if go equals to false, there is no trip
    bool go = false;

    // this loop is used to send the data while we are on a trip
    while( go == false) {
            std::string sttt = "waiting for trip";
            client->sendData(sttt, 0);
            //deserialize to trip
            vector<Point> tripRoute;
            client->receiveData(buffer, sizeof(buffer), 0);
            string serial_str2(buffer, sizeof(buffer));
            boost::iostreams::basic_array_source<char> device(serial_str2.c_str(), serial_str2.size());
            boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
            boost::archive::binary_iarchive ia(s2);
            ia >> tripRoute;
            serial_str.clear();
            // if the vector is empty we delete client and end transmission
            if(tripRoute.empty()){
                break;
            }

            driver->setOnTrip(true);
            taxi->getLocation()->getState().setX(tripRoute.at(0).getX());
            taxi->getLocation()->getState().setY(tripRoute.at(0).getY());

            //if we are on trip then we send a signal for server to keep sending data meaning next location
            while (driver->isOnTrip() == true) {
                go = true;
                //serialize signal for continual sending of location
                string serial3_str;
                boost::iostreams::back_insert_device<std::string> inserter(serial3_str);
                boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
                boost::archive::binary_oarchive oa(s);
                oa << go;
                s.flush();
                client->sendData(serial3_str, 0);
                serial3_str.clear();

                //receiving correct new location from server to diserialize
                client->receiveData(buffer, sizeof(buffer), 0);
                //deserialize location as point
                Point *location;
                std::string locationStr(buffer, sizeof(buffer));
                boost::iostreams::basic_array_source<char> device(locationStr.c_str(), locationStr.size());
                boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s4(device);
                boost::archive::binary_iarchive ia(s4);
                ia >> location;
                if((location->getX() == -1) && (location->getY() == -1)){
                    driver->setOnTrip(false);
                    go = true;
                    break;
                }
                taxi->getLocation()->getState().setX(location->getX());
                taxi->getLocation()->getState().setY(location->getY());
                //check if we reached end of trip
                int length = tripRoute.size();
                if( location->getX() == tripRoute.at(length-1).getX()){
                    if(location->getY() == tripRoute.at(length-1).getY()){
                        driver->setOnTrip(false);
                        go = false;
                    }
                }

            }
    }
    delete client;
}
