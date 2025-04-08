#ifndef PROCESSMANAGEMENT_HPP
#define PROCESSMANAGEMENT_HPP

#include <queue>
#include <memory>
#include <vector>   // Include vector for storing threads
#include <thread>   // Include thread for std::thread
#include "Task.hpp"

class ProcessManagement {
public:
    ProcessManagement();
    bool submitToQueue(std::unique_ptr<Task> task);

    // Updated signature to accept the encryption key
    void executeTasks(int key);

private:
    std::queue<std::unique_ptr<Task>> taskQueue;
};

#endif // PROCESSMANAGEMENT_HPP
