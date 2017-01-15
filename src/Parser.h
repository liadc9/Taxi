//
// Created by liad on 17/11/16.
//

#ifndef FAST_TAXI_PARSER_H
#define FAST_TAXI_PARSER_H
#include "State.h"
#include "Point.h"
#include <vector>
#include <boost/any.hpp>
using namespace std;

class Parser {

public:
    Parser();
    vector<boost::any> DataSplit(string str);

        private:
    string parsed[10];
    int seperator;
    int i;
    int x_coordinate;
    int y_coordinate;
};


#endif //TAXI_PARSER_H
