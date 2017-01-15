/**
 * this class holds the grid
 */
#include <iostream>
#include "Point.h"
#include "State.h"
#include "Grid.h"


using namespace std;
class Trip;
/**
 * grid constructor which creates the grid.
 * @param width - grid width
 * @param height - grid height
 */
Grid::Grid(int width, int height){
    this->width = width;
    this->height = height;


    // creates a two dimensional array to make grid.
    State** myGrid = new State*[width];
    for(int i = 0; i < width; ++i)
    {
        //inner array for each row in width array
        myGrid[i] = new State [height];
        for (int j = 0; j < height; j++) {
            //begin all grid info
            //this loop is used to mark all nodes as not visited yet
            Point current;
            current.setX(i);
            current.setY(j);
            myGrid[i][j].setState(current);
            myGrid[i][j].setWasHere(false);
            myGrid[i][j].setComeFrom(NULL);
            myGrid[i][j].setIsObstacle(0);
        }
    }
    this->myGrid = myGrid;
}
Grid::Grid(){}
/**
 * getter for the size of the grid
 * @return vector with info
 */
vector<int>Grid:: getSizes(){
    vector<int>size;
    size.push_back(width);
    size.push_back(height);
    return size;
}
/**
 * setter for was here or not
 * @param x - x position to check
 * @param y - y position to check
 */
void Grid::setWasHere(int x, int y)
{
    myGrid[x][y].setWasHere(true);
}
/**
 * getter for the height of the grid
 * @return grid height
 */
 int Grid::getHeight(){
     return height;
 }
/**
 * getter for the width of the grid
 * @return grid width
 */
int Grid::getWidth(){
    return width;
}
/**
 * getter for the state of position on grid
 * @param x - x position
 * @param y - y position
 * @return state of position
 */
State* Grid::getState(int x, int y)
{
    return &myGrid[x][y];
}
/**
 * This class is used to itearate over the neibours of a position on the grid
 * and check if the neibour is legit: inside grid borders, the neibour wasn't
 * visited yet and there is no obstacle in the position.
 * @param startS - position to check all it's neibours
 * @param ourGrid - the grid
 * @return vector of good neibours.
 */
vector<State*> Grid::get_neighbor(State* startS, Grid* ourGrid) {
    vector<State*> neighbors;
    int a = ourGrid->getHeight();
    int b = ourGrid->getWidth();
    int xAxis = startS->getState().getX();
    int yAxis = startS->getState().getY();
    while (true) {
        //checking first neighbor
        if ((xAxis - 1 >= 0) && (ourGrid->myGrid[xAxis - 1][yAxis].getIsObstacle() == 0)) {
            int newX1 = xAxis - 1;
            neighbors.push_back(&(ourGrid->myGrid[newX1][yAxis]));
        }
        //checking second neighbor
        if ((yAxis + 1 <a) && (ourGrid->myGrid[xAxis][yAxis + 1].getIsObstacle() == 0)) {
            int newY2 = yAxis + 1;
            neighbors.push_back(&(ourGrid->myGrid[xAxis][newY2]));
        }
        //checking third neighbor
        if ((xAxis + 1 < b) && (ourGrid->myGrid[xAxis + 1][yAxis].getIsObstacle() == 0)) {
            int newX3 = xAxis + 1;
            neighbors.push_back(&(ourGrid->myGrid[newX3][yAxis]));
        }
        //checking fourth neighbor
        if ((yAxis - 1 >= 0) && (ourGrid->myGrid[xAxis][yAxis - 1].getIsObstacle() == 0)) {
            int NewY4 = yAxis - 1;
            neighbors.push_back(&(ourGrid->myGrid[xAxis][NewY4]));
        }
        break;
    }
    return neighbors;
}
/**
 * this method is used to go over all grid and reset it
 * for another operation of different needs.
 */
void Grid::afterAlgoRun(){
    for(int i = 0; i < width; ++i) {
        for (int j = 0; j < height; j++) {
            // reset visited
            myGrid[i][j].setWasHere(false);
            // reset father info
            myGrid[i][j].setComeFrom(NULL);
        }
    }
}
/**
 * deconstructor for grid
 */
Grid::~Grid() {}

