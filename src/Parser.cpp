/*
 * This class contains the parser of the string input
 */

#include "Parser.h"
#include <math.h>
#include <sstream>
#include <cstring>
#include <vector>
#include <boost/any.hpp>
#include <stdlib.h>

using namespace std;

class Point;
class State;


Parser:: Parser(){

}
/**
 * The following method is used to devide the input into 3 parts according to
 * grid size, start and end positions.
 * @param str
 * @return
 */
vector<boost::any> Parser:: DataSplit(string str) {

    int isNum = NULL;
    char isChar = NULL;
    int curentNum = 0;
    double dub = 0;
    vector<boost::any> info;
    boost::any variable;


    // as long as string isn't empty
    while (str != "\0") {
        seperator = (int) str.find(" ");
        if (seperator == -1) {
            seperator = (int) str.find(",");
            if (seperator == -1) {
                seperator = str.size();
            }
        }

        // iterates over each part of the string looking for next num or char
        for (int j = 0; j < seperator+1; j++) {
            if (j == seperator) {

                if(isChar != '\0'){
                    //convert variable to correct type
                    variable = isChar;
                    // push variable
                    info.push_back(variable);
                    isChar = NULL;
                } else if(dub > 0) {
                    variable = dub;
                    // push variable
                    info.push_back(variable);
                    dub = 0;
                } else {
                    //convert variable to correct type
                    variable = isNum;
                    // push variable
                    info.push_back(variable);
                    isNum = 0;
                }
                continue;
            } else if (isalpha(str[j])) {
                isChar = str[j];
            } else if (isdigit(str[j]) && curentNum != 6) {
                // -48 for ASCII value, uses power to get the exct size
                isNum = isNum + ((int) str[j] - 48);
                isNum = isNum * (int) (pow(10, seperator - j - 1));
                // the only case we need a double is one specific time:
            } else if (isdigit(str[j]) && curentNum == 6){
                string dummy = str;
                dummy.erase((unsigned long) seperator, dummy.size()-1);
                dub = atof(dummy.c_str());
                j = j + dummy.size() - 1;
            }
        }
        // remove all part of the string we already parsed
        str.erase(0, (unsigned long) (seperator + 1));
        curentNum++;
    }

    return info;

}