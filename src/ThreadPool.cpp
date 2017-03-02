/**
 * The following is the threadpool class
 */

#include "ThreadPool.h"
#include <unistd.h>
#include <iostream>
/**
 * this method is done by the threads that are created in the constructor.
 * @param arg
 * @return
 */
static void *startJobs(void *arg) {
    ThreadPool *pool = (ThreadPool *)arg;
    pool->doJobs();
    return NULL;
}
/**
 * The following method is used to check if we have a trip
 * if we do, this method creates it's route.
 */
void ThreadPool::doJobs() {
    while (!stop) {
        pthread_mutex_lock(&lock);
        if (!trips_queue.empty()) {
            Trip* trip = trips_queue.front();
            trips_queue.pop();
            pthread_mutex_unlock(&lock);
            trip->doRoute();
        }
        else {
            pthread_mutex_unlock(&lock);
            sleep(1);
        }
    }
    pthread_exit(NULL);
}
/**
 * this method adds the rtrips to the queue and the dojobs methods executes the doRoute method
 * in trip that creates his path (vector of points)
 * @param trip - given trip
 */
void ThreadPool::addJob(Trip *trip) {
    trips_queue.push(trip);
}
/**
 * constructor of threadpool
 * @param threads_num - num of threads
 */
ThreadPool::ThreadPool(int threads_num) : threads_num(threads_num), stop(false) {
    // TODO Auto-generated constructor stub
    threads = new pthread_t[threads_num];

    pthread_mutex_init(&lock, NULL);
    for (int i = 0; i < threads_num; i++) {
        pthread_create(threads + i, NULL, startJobs, this);
    }
}
/**
 * method used to exit the while loop in dojobs method.
 */
void ThreadPool::terminate() {
    stop = true;
}
/**
 * deconstructor od threadpool class
 */
ThreadPool::~ThreadPool() {
    // TODO Auto-generated destructor stub
    delete[] threads;
    pthread_mutex_destroy(&lock);
}
/**
 * this method is used when the theradpool is empty
 * @return null
 */
bool ThreadPool::isEmpty() {

}
