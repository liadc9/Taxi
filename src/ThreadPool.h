//
// Created by gal on 26/01/17.
//

#ifndef TAXI_THREADPOOL_H
#define TAXI_THREADPOOL_H

#include <queue>
#include <pthread.h>
#include "BFS.h"

using namespace std;

class ThreadPool {
private:
    queue<BFS *> bfs_queue;
    int threads_num;
    pthread_t* threads;
    bool stop;
    pthread_mutex_t lock;
public:
    ThreadPool(int threads_num);
    void doJobs();
    void addJob(BFS *bfs);
    void terminate();
    bool isEmpty();
    virtual ~ThreadPool();

};


#endif //TAXI_THREADPOOL_H
