#pragma once
#include "BaseCache.hpp"
#include <memory>

class CacheApplier final {
	std::shared_ptr<BaseCache> cache_;
	
public:
	void set_strategy(std::shared_ptr<BaseCache> strategy);
	bool has_in_cache(const std::string& key) const;
	std::string read_from_cache(const std::string& key) const;
	void write_from_cache(const std::string& key, const std::string& value);
	void delete_from_cache(const std::string& key);
};