#pragma once
#include <fstream>
#include <string>
#include <mutex>


class Logger final
{
	mutable std::mutex osMutex_;
	mutable std::ofstream os_;	
	explicit Logger();
	~Logger() = default;
public:
	void operator=(const Logger&) = delete;
	void operator=(const Logger&&) = delete;
	Logger(const Logger&) = delete;
	Logger(const Logger&&) = delete;
	Logger& operator<<(const std::string& msg) const;
	static Logger& getInstance();
};


