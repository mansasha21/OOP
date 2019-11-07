#include "ÑacheApplier.h"

void CacheApplier::set_strategy(std::shared_ptr<BaseCache> strategy)
{
	cache_ = strategy;
}

bool CacheApplier::has_in_cache(const std::string& key) const
{
	return cache_->has(key);
}

std::string CacheApplier::read_from_cache(const std::string& key) const
{
	return cache_->read(key);
}

void CacheApplier::write_from_cache(const std::string& key, const std::string& value)
{
	cache_->write(key, value);
}

void CacheApplier::delete_from_cache(const std::string& key)
{
	cache_->erase(key);
}



