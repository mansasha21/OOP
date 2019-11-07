#pragma once
#include "BaseCache.hpp"
#include "unordered_map"
#include "deque"
#include "algorithm"


class PoorManMemoryCache final :public BaseCache
{
	std::unordered_map<std::string, std::string> data_;
	std::deque<std::string> keys;
	size_t size_;
public:
	PoorManMemoryCache(size_t size = 32);
	 ~PoorManMemoryCache() override = default;
	bool has(const std::string& key) override;
	std::string read(const std::string& key) override;
	void write(const std::string& key, const std::string& value) override;
	void erase(const std::string& key) override;
};