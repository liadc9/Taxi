/**
 * The following class is the class that is used for the BFS algorithm iteration.
 * The class holds the BFS constructor which creates the algorithms iteration and prints
 * the BFS path accordingly.
 */
#include <iostream>
#include <queue>
#include<vector>
#include "State.h"
#include "ISearchable.h"
#include "BFS.h"
#include "Trip.h"
#include "Grid.h"



using namespace std;



/**
 * This is the constructor of the BFS algorithm to find the shortest path.
 * @param searchable - the searchable object that BFS receives, at this point we only have trip.
 */
BFS::BFS(ISearchable* searchable) {
    mysearch = searchable;
    //get info from grid.
    wid = searchable->getGrid()->getWidth();
    hig = searchable->getGrid()->getHeight();
    // we build the path queue to hold all nodes after we are done with them
    path = new queue<State *>;
    //create new state inorder to compare with final stop point.
    finish = new State(searchable->getdest()->getState(),
                       searchable->getdest()->getComeFrom(), false);
    // create a queue
    nodeQueue = new queue<State *>;
    // receive start position from Isearchable instance
    xCord = searchable->getStart()->getState().getX();
    yCord = searchable->getStart()->getState().getY();
    searchable->getGrid()->setWasHere(xCord, yCord);
}
/**
 * This is the main method used to to run the BFS algorithm for shortest path.
 * when a state node is reached it is pushed to the queue, the neighbors of the state-nodes
 * are recevied from the grid and are iterated upon if we haven't visited them yet
 * or if they have no obstacles.
 * Once the sons are in the queue they have pointers to their father and the father
 * is poped from the queue
 * and pushd into the "path" queue so we can iterate over all state-nods later on.
 * Thus we create a linked list of pointer of connected fathers and sons at the end.
 * @return - a vector of the shortest route we created.
 */
vector<Point> BFS::AlgoRun(){
    // put first node position on grid
    nodeQueue->push((mysearch->getStart()));
    int i = 0;
    //this loop will run until we touch the state we want to reach
    while(true){
        path->push(nodeQueue->front());
        vector<State*> neighborList = mysearch->getGrid()->
                get_neighbor(nodeQueue->front(),mysearch->getGrid());
        /*
         * this for loop is used to check if the state position
         * (or next node) doesn't have a father
         *  which means we didn't get there yet so the nodes father
         *  is our current node and we mark them.
         */
        for(i = 0; i < neighborList.size();i++) {
            // if we didn't visit this neibour yet in the BFS and he
            // isn't equal to our final node.
            if(neighborList[i]->Comparison(*finish)){
                //otherwise it will not reach the last node i the grid.
                i++;
                break;
            }

            if (!neighborList[i]->getWasHere() &&
                !(neighborList[i]->Comparison(*finish))) {
                neighborList[i]->setWasHere(true);
                neighborList[i]->setComeFrom(nodeQueue->front());
                nodeQueue->push((neighborList[i]));
            }
        }
        /*
         * if the neibor of the head of the queue equals to finish
         * (our last node) weached the destination,
         * so we update the comefrom of finish node, we pop the
         * father of finish and we quit the loop.
         */
        if(neighborList[i-1]->Comparison(*finish)){
            // give last point the comefrom pointer to its predeccesor.
            State* grand = nodeQueue->front();
            finish->setComeFrom(grand);
            nodeQueue->pop();
            break;
        }
        //we are done with the current node-state.
        nodeQueue->pop();
    }
    // call the printing recursion method
    VectorReturn(finish);
    // delete all changes made to grid by running algorithm
    mysearch->getGrid()->afterAlgoRun();
    delete finish;
    delete nodeQueue;
    delete path;

    return(BFSreturn);

}
/**
 * This function is sed to recursively print all node in the BFS shortest path
 * by calling all the father nodes begining with our last node and thus printing them.
 * @param finish - the last state-node in the BFS, the end trip node
 */
void BFS::VectorReturn(State *finish) {

    // reursively call as long as we haven't reached the first one in route
    if(finish->getComeFrom() != NULL){
        VectorReturn(finish->getComeFrom());
    }
    // place in vector
    BFSreturn.push_back(finish->getState());
}

vector<Point> BFS::getBFSreturn() {
    return BFSreturn;
}