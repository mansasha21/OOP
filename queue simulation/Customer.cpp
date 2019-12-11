#include "Customer.h"
#include <thread>
#include <random>

Customer::Customer(int minSolvingTime, int maxSolvingTime, int ticketNum):ticketNum(ticketNum)
{
	const std::uniform_int_distribution<int> d(minSolvingTime, maxSolvingTime);
	std::random_device rd;
	duration_ = static_cast<std::chrono::milliseconds>(d(rd));
}


void Customer::solve() const
{
	std::this_thread::sleep_for(duration_);
}

int Customer::getTicket() const
{
	return ticketNum;
}


