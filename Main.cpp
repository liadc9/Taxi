/**
 * This is the main Class which is used in order to run the BFS algorithm on the grid.
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include "src/Point.h"
#include <iostream>
#include <vector>
#include <string>
#include "src/Parser.h"
#include "src/Trip.h"
#include "src/Grid.h"
#include "src/BFS.h"
#include "src/TaxiCenter.h"
#include <boost/any.hpp>
#include "src/Menu.h"
#include "src/sockets/Tcp.h"
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
using namespace std;

BOOST_CLASS_EXPORT_GUID(StandardCab,"StandardCab")
BOOST_CLASS_EXPORT_GUID(LuxuryCab,"LuxuryCab")

/**
 * This is the main function, it is used to control the flow of the program.
 * it calls the parser to parse arguments, calls the grid class to create a grid.
 * it creates all obstacles for the grid.
 * it then calls the menu to continue the flow.
 * @param argc - args recceived from user
 * @param argv - args received from user
 * @return null;
 */
int main(int argc, char *argv[]) {
    int port = atoi(argv[1]);
    char buffer[65536];
    bool input = false;
    Grid *grid;

    while(!input) {
        // get grid input from user
        string gridInput;
        getline (cin, gridInput);
        int xSize;
        int ySize;
        int xObstacle;
        int yObstacle;

        // creates new parser object
        Parser parse;

        // create a list of int data
        vector<boost::any> parsedData;

        // parse grid info
        parsedData = parse.DataSplit(gridInput);

        // creates list for grid coordinates
        vector<Point*> parsedPoints;

        // loops as long as data isn't valid

        try {
            //enters the data for grid size to be understandable.
            xSize = boost::any_cast<int>(parsedData[0]);

            if (xSize <= 0) {
                gridInput.clear();
                throw xSize;
            }

            ySize = boost::any_cast<int>(parsedData[1]);

            if (ySize <= 0) {
                throw ySize;
            }

        } catch (int x) {
            cout << -1 << endl;
            continue;
        }

        // get number of obstacles
        char obstacles;
        cin.get(obstacles);
        if(!isdigit(obstacles)){
            cout << -1 << endl;
            gridInput.clear();
            cin.ignore();
            continue;
        }
        // grid creation:
        grid = new Grid(xSize, ySize);
        int numOfObstacles = ((int) obstacles - 48);
        // to ignore white space
        cin.ignore();
        try {
            if (numOfObstacles > 0) {
                // for each obstacle:

                for (int i = 0; i < numOfObstacles; i++) {
                    //an obstacle string
                    string object;
                    getline(cin, object);

                    vector<boost::any> parsedObstacle;
                    parsedObstacle = parse.DataSplit(object);

                    xObstacle = boost::any_cast<int>(parsedObstacle[0]);
                    if (xObstacle < 0) {
                        throw xObstacle;
                    }
                    yObstacle = boost::any_cast<int>(parsedObstacle[1]);
                    if (yObstacle < 0) {
                        throw yObstacle;
                    }
                    // set the grid position to hold an obstacle.
                    grid->getState(xObstacle, yObstacle)->setIsObstacle(1);
                }
            } else {
                throw numOfObstacles;
            }
        } catch (int y) {
            cout << -1 << endl;
            continue;
        }
        input = true;

    }

    // call the menu for different input options
    Menu* menu = new Menu();
    menu->online(grid, port);

    // frees memory before exiting the program.
    delete grid;
    delete menu;
    return 0;
}