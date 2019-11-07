#pragma once
#include <string>


class BaseCache {
public:
	virtual bool has(const std::string& key) = 0;
	virtual std::string read(const std::string& key) = 0;
	virtual void write(const std::string& key, const std::string& value) = 0;
	virtual void erase(const std::string& key) = 0;
	virtual ~BaseCache() = default;
};