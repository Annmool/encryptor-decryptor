#include "ProcessManagement.hpp"
#include "../encryptDecrypt/Cryption.hpp"
#include <iostream>
#include <thread>
#include <vector>
#include <utility>

ProcessManagement::ProcessManagement() {}

bool ProcessManagement::submitToQueue(std::unique_ptr<Task> task) {
    if (!task) return false;
    taskQueue.push(std::move(task));
    return true;
}

void ProcessManagement::executeTasks(int key) {
    std::vector<std::thread> workerThreads;
    size_t taskCount = taskQueue.size();

    while (!taskQueue.empty()) {
        std::unique_ptr<Task> taskToExecute = std::move(taskQueue.front());
        taskQueue.pop();

        if (!taskToExecute) {
            std::cerr << "Warning: Encountered null task in queue." << std::endl;
            continue;
        }

        std::string taskData = taskToExecute->toString();
        workerThreads.emplace_back(executeCryption, std::move(taskData), key);
    }

    if (taskCount > 0) {
        std::cout << "Waiting for " << taskCount << " tasks to complete..." << std::endl;
        for (auto& t : workerThreads) {
            if (t.joinable()) {
                t.join();
            }
        }
        std::cout << "All tasks finished processing." << std::endl;
    } else {
        std::cout << "No tasks were queued for execution." << std::endl;
    }
}
