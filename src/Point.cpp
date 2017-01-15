/**
 * This class is used to represent class point.
 */
#include <iostream>
#include "Point.h"
/**
 * empty constructor for class point
 */
Point::Point(){
    xVal = 0;
    yVal = 0;
}
/**
 * constructor with values for point
 * @param x - xvalue received
 * @param y - yvalue received
 */
Point::Point(int x, int y) {
    xVal = x;
    yVal = y;
}
/**
 * getter for x value
 * @return x value
 */
int Point::getX(){
    return xVal;
}
/**
 * getter for y value
 * @return y value
 */
int Point::getY(){
    return yVal;
}
/**
 * setter for x value
 * @param xValue
 */
void Point::setX(int xValue)
{
    xVal = xValue;
}
/**
 * setter for y value
 * @param yValue
 */
void Point::setY(int yValue)
{
    yVal = yValue;
}
/**
 * this methoc is used overload the print function of
 * c++ to print points accordingly
 * @param out - the out stream
 * @param s - the point to print
 * @return the out stream.
 */
std::ostream& operator<< (std::ostream &out, const Point &s)
{

    out << "(" << s.xVal <<"," << s.yVal<< ")";
    return out;
}
