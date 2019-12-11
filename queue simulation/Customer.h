#pragma once
#include <chrono>
class Customer final
{
	int ticketNum;
	std::chrono::milliseconds duration_;
public:
	Customer(int minSolvingTime, int maxSolvingTime , int ticketNum);
	void solve() const;
	int getTicket() const;
};

