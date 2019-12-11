#include "Logger.hpp"

Logger::Logger() :os_( "log.txt" ) {}

Logger& Logger::getInstance()
{
	static Logger logger;
	return logger;
}

Logger& Logger::operator<<(const std::string& msg) const
{
	osMutex_.lock();
	os_ << msg << std::endl;
	osMutex_.unlock();
	return getInstance();
}




