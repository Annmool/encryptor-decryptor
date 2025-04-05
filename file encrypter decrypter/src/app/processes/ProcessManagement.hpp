#ifndef PROCESSMANAGEMENT_HPP
#define PROCESSMANAGEMENT_HPP

#include <queue>
#include <memory>
#include "Task.hpp"

class ProcessManagement {
public:
    ProcessManagement();
    bool submitToQueue(std::unique_ptr<Task> task);
    void executeTasks();

private:
    std::queue<std::unique_ptr<Task>> taskQueue;
};

#endif
