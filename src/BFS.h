
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
#include <cstring>
#include <boost/serialization/access.hpp>
#include "State.h"
#include "ISearchable.h"
#include <iostream>
#include<queue>

#ifndef FAST_TEXI_BFS_H
#define FAST_TEXI_BFS_H

using namespace std;

class Isearchable;
class Trip;
class State;

class BFS {
public:
    BFS(ISearchable* searchable);
    vector<Point> AlgoRun();
    void VectorReturn(State* finish);
    vector<Point> getBFSreturn();

private:
    int wid;
    int hig;
    int xCord;
    int yCord;
    ISearchable* mysearch;
    queue<State*> *nodeQueue;
    queue<State*> *path;
    State *finish;
    vector<Point> BFSreturn;

};


#endif //TAXI_BFS_H
