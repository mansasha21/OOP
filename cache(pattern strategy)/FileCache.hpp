#pragma once
#include "BaseCache.hpp"
#include <set>

class FileCache final : public BaseCache 
{
	inline static std::string format{ ".txt" };
	std::set<std::string> filenames;
	
public:
	bool has(const std::string& key) override;
	std::string read(const std::string& key) override;
	void write(const std::string& key, const std::string& value) override;
	void erase(const std::string& key) override;
	 ~FileCache() override;
	
};