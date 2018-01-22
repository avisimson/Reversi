/*
 * "ThreadPool.h"
 *
 *  Created on: Jan 21, 2017
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#include "ThreadPool.h"
#include <unistd.h>
//constructor-get number of threads to open.
ThreadPool::ThreadPool(int threadsNum) :
        stopped(false) {
    threads = new pthread_t[threadsNum];
    for (int i = 0; i < threadsNum; i++) {
        pthread_create(threads + i, NULL, execute,
                       this);
    }
    pthread_mutex_init(&lock, NULL);
}
//method gets a threadpool instance and execute task for current thread.
void* ThreadPool::execute(void *arg) {
    ThreadPool *pool = (ThreadPool *)arg;
    pool->executeTasks();
}
//add task from parameter to tasks queue variable.
void ThreadPool::addTask(Task *task) {
    tasksQueue.push(task);
}
//method take the front task from tasks queue and put it in an empty thread.
void ThreadPool::executeTasks() {
    while (!stopped) {
        pthread_mutex_lock(&lock);
        if (!tasksQueue.empty()) {
            Task* task = tasksQueue.front();
            tasksQueue.pop();
            pthread_mutex_unlock(&lock);
            task->execute();
        }
        else {
            pthread_mutex_unlock(&lock);
            sleep(1);
        }
    }
}
//stop all threads, and kill mutex variable.
void ThreadPool :: terminate() {
    pthread_mutex_destroy(&lock);
    stopped = true;
}
//delete threads dynamic array.
ThreadPool :: ~ThreadPool() {
    delete[] threads;
}