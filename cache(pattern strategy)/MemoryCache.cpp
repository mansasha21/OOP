#include "MemoryCache.hpp"

bool MemoryCache::has(const std::string& key)
{
	return data_.find(key) != data_.end();
}

std::string MemoryCache::read(const std::string& key)
{
	auto it = data_.find(key);
	if (it == data_.end())
		return {};
	return it->second;
}

void MemoryCache::write(const std::string& key, const std::string& value)
{
	data_[key] = value;
}

void MemoryCache::erase(const std::string& key)
{
	data_.erase(key);
}


