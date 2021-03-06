#pragma once

#include <functional>
#include <future>
#include <fw/filesystem.hpp>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

struct PendingCommand;
class Reporter;
class Process;

class Executor
{
public:
    Executor(size_t jobcount, Reporter &reporter);
    ~Executor();
    void Run(std::shared_ptr<PendingCommand> cmd);
    std::future<void> Start();

private:
    void RunMoreCommands();
    std::mutex m;
    std::vector<std::shared_ptr<PendingCommand>> commands;
    std::vector<std::unique_ptr<Process>> activeProcesses;
    Reporter &reporter;
    std::promise<void> done;
};
