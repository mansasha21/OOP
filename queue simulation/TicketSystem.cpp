#include "TicketSystem.hpp"
#include <random>
#include <sstream>

std::string TicketSystem::getThreadId() const
{
	const auto id = std::this_thread::get_id();
	std::stringstream ss;
	ss << id;
	return ss.str();
}



TicketSystem::TicketSystem(const config& conf): conf_(conf), tm_(conf_.beginTicketNum),
                                                unservedAmount_(conf_.amountOfCustomers)
{
	Logger::getInstance();
	for(auto i = 0; i < conf_.amountOfThreads; ++i)
	{
		tables_.emplace_back(std::thread([=] {simulateTableWork(); }));
	}
}

void TicketSystem::simulate()
{
	for(auto i = 0; i < conf_.amountOfCustomers; ++i)
	{
		std::uniform_int_distribution<int> d(conf_.minDelay, conf_.maxDelay);
		std::random_device rd;
		std::this_thread::sleep_for(static_cast<std::chrono::milliseconds>(d(rd)));
		queueMutex_.lock();
		queue_.push({ conf_.minSolvingTime,conf_.maxSolvingTime,tm_.getNext() });
		queueMutex_.unlock();
		cv_.notify_one();
	}
	cv_.notify_all();
	for (auto& i : tables_)
	{
		if (i.joinable())
			i.join();
	}
}

void TicketSystem::simulateTableWork()
{
	const auto id = getThreadId();
	int ticket;
	while(unservedAmount_!=0)
	{
		Customer customer(0,0,0);
		{
			std::unique_lock<std::mutex> lk(queueMutex_);
			cv_.wait(lk, [&] {return !queue_.empty() || unservedAmount_ == 0; });
			if (unservedAmount_ == 0)
			{
				return;
			}
			ticket = queue_.front().getTicket();
			Logger::getInstance() << std::to_string(ticket) + " customer taken by " + id;
			customer = queue_.front();
			queue_.pop();
			--unservedAmount_;
		}
		customer.solve();
		Logger::getInstance() << std::to_string(ticket) + " customer served by " + id;
	}
}
