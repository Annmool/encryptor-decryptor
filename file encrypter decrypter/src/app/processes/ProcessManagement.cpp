#include "ProcessManagement.hpp"
#include <iostream>
#include <thread>   // For std::thread
#include <utility>  // For std::move
#include "../encryptDecrypt/Cryption.hpp"

ProcessManagement::ProcessManagement() {}

bool ProcessManagement::submitToQueue(std::unique_ptr<Task> task) {
    taskQueue.push(std::move(task));
    return true;
}

void ProcessManagement::executeTasks() {
    while (!taskQueue.empty()) {
        std::unique_ptr<Task> taskToExecute = std::move(taskQueue.front());
        taskQueue.pop();

        std::cout << "Executing task: " << taskToExecute->toString() << std::endl;

        std::thread cryptionThread(executeCryption, taskToExecute->toString());
        cryptionThread.join(); // Wait for task to finish
    }
}
