/*
 * "Task.h"
 *
 *  Created on: Jan 21, 2017
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/

#ifndef REVERSI_TASK_H
class Task {
public:
    Task(void * (*func)(void *arg), void* arg) :
            func(func), arg(arg) {}
    void execute() {
        func(arg);
    }
    virtual ~Task() {}
private:
    void * (*func)(void *arg);
    void *arg;
};
#define REVERSI_TASK_H

#endif //REVERSI_TASK_H
