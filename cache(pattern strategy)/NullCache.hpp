#pragma once
#include  "BaseCache.hpp"

class NullCache final : public BaseCache
{
public:
	bool has(const std::string& key) override;
	std::string read(const std::string& key) override;
	void write(const std::string& key, const std::string& value) override;
	void erase(const std::string& key) override;
	~NullCache() override = default;
};