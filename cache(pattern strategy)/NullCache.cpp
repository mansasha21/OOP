#include "NullCache.hpp"

void NullCache::erase(const std::string& key)
{
	
}
bool NullCache::has(const std::string& key)
{
	return false;
}
std::string NullCache::read(const std::string& key)
{
	return {};
}
void NullCache::write(const std::string& key, const std::string& value)
{
	
}

