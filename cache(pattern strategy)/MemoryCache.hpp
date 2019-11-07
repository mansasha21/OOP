#pragma once
#include "BaseCache.hpp"
#include <unordered_map>

class MemoryCache final: public BaseCache
{
	std::unordered_map<std::string, std::string> data_;
public:
	MemoryCache() = default;
	 ~MemoryCache() override = default;
	bool has(const std::string& key) override;
	std::string read(const std::string& key) override;
	void write(const std::string& key, const std::string& value) override;
	void erase(const std::string& key) override;
};