#pragma once
#include "Logger.hpp"
#include "TicketMachine.h"
#include "Customer.h"
#include <queue>
#include <vector>
#include <thread>
#include <condition_variable>
#include <atomic>

struct config
{
	int amountOfThreads;
	int amountOfCustomers;
	int minDelay;
	int maxDelay;
	int minSolvingTime;
	int maxSolvingTime;
	int beginTicketNum;
};

class TicketSystem final
{
	config conf_;
	TicketMachine tm_;
	std::atomic<int> unservedAmount_;
	
	std::condition_variable cv_;
	std::mutex queueMutex_;
	
	std::queue<Customer> queue_;
	std::vector<std::thread> tables_;
private:
	std::string getThreadId() const;
	void simulateTableWork();
public:
	TicketSystem(const config& conf);
	void simulate();
};

