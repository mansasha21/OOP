#include <iostream>
#include <chrono>
#include <fstream>
#include "TicketSystem.hpp"

int main()
{
	config conf{ 0,0,0,0,0,0,0 };
	std::ifstream is("config.txt");
	if (!(is >> conf.amountOfThreads >> conf.amountOfCustomers >> conf.minDelay
		>> conf.maxDelay >> conf.minSolvingTime >> conf.maxSolvingTime >> conf.beginTicketNum))
		return -1;
	TicketSystem ts(conf);
	std::cout << "simulation begins" << std::endl;
	auto b = std::chrono::high_resolution_clock::now();
	ts.simulate();
	auto e = std::chrono::high_resolution_clock::now();
	auto dif = e - b;
	std::cout << "simulation ends\nduration = " << std::chrono::duration_cast<std::chrono::milliseconds>(dif).count()<<" milliseconds" << std::endl;
	system("pause");
	return 0;
}
