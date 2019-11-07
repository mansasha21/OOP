#include "PoorManMemoryCache.hpp"

PoorManMemoryCache::PoorManMemoryCache(size_t size) :size_(size) {}

bool PoorManMemoryCache::has(const std::string& key)
{
	return data_.find(key) != data_.end();
}

std::string PoorManMemoryCache::read(const std::string& key)
{
	auto res = data_.find(key);
	if (res != data_.end())
		return res->second;
	return {};
}

void PoorManMemoryCache::write(const std::string& key, const std::string& value)
{
	auto existing_el = data_.find(key);
	if (existing_el != data_.end())
	{
		keys.erase(std::find(keys.begin(), keys.end(), key));
	}
	else if (data_.size() == size_)
	{
		data_.erase(*keys.begin());
		keys.pop_front();
	}
	keys.push_back(key);
	data_[key] = value;
}

void PoorManMemoryCache::erase(const std::string& key)
{
	data_.erase(key);
	keys.erase(std::find(keys.begin(), keys.end(), key));
}



