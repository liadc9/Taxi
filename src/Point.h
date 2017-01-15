
#ifndef FAST_TEXI_POINT_H
#define FAST_TEXI_POINT_H
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

class Point{
private:
    int xVal;
    int yVal;
public:
    Point();
    Point(int x,int y);
    int getX();
    int getY();
    void setX(int xValue);
    void setY(int yValue);
    friend std::ostream& operator<< (std::ostream &out, const Point &s);
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & xVal;
        ar & yVal;
    }
};


#endif //TAXI_POINT_H
