#ifndef FAST_TEXI_GRID_H
#define FAST_TEXI_GRID_H

#include "Point.h"
#include <iostream>
#include "ISearchable.h"
#include "Map.h"
#include <boost/serialization/access.hpp>
#include <string>
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

class Grid: public Map{
public:
    Grid();
    Grid(int width, int height);
    int getHeight();
    int getWidth();
    vector<State*> get_neighbor(State* startS, Grid* ourGrid);
    State* getState(int x, int y);
    void setWasHere(int x, int y);
    vector<int> getSizes();
    void afterAlgoRun();
    virtual ~Grid();
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & height;
        ar & width;
        ar & **myGrid;
    }

private:
    int width;
    int height;
    State** myGrid;

};


#endif //TAXI_GRID_H
