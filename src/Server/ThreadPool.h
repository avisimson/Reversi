/*
 * "ThreadPool.h"
 *
 *  Created on: Jan 21, 2017
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/

#ifndef REVERSI_THREADPOOL_H
#include <queue>
#include <pthread.h>
#include "Task.h"
using namespace std;
class ThreadPool {
public:
    ThreadPool(int threadsNum);
    void addTask(Task *task);
    void terminate();
    virtual ~ThreadPool();
private:
    queue<Task *> tasksQueue;
    pthread_t* threads;
    void executeTasks();
    bool stopped;
    pthread_mutex_t lock;
    static void *execute(void *arg);
};
#define REVERSI_THREADPOOL_H

#endif //REVERSI_THREADPOOL_H
