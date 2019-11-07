#include "FileCache.hpp"
#include <fstream>
#include <vector>
#include <cstdio>

void FileCache::erase(const std::string& key)
{
	auto hash = std::hash<std::string>()(key);

	std::string key_, value;
	std::fstream file;
	std::vector < std::pair<std::string, std::string>> data;
	file.open(std::to_string(hash) + format, std::fstream::in);
	if (!file.is_open())
		return;
	bool contains = false;
	while (file >> key_ >> value)
	{
		if (key_ == key)
			contains = true;
		else
			data.emplace_back(key_, value);
	}
	file.close();
	if (!contains)
	{
		return;
	}
	file.open(std::to_string(hash) + format, std::fstream::out);
	for (auto& [k, val] : data)
	{
		file << k << "\t" << val << std::endl;
	}
	file.close();
}

void FileCache::write(const std::string& key, const std::string& value)
{
	auto hash = std::hash<std::string>()(key);
	std::fstream file;
	file.open(std::to_string(hash) + format, std::fstream::app);
	if (!file.is_open())
		return;
	file << key << "\t" << value << std::endl;
	filenames.insert(std::to_string(hash) + format);
	file.close();
}

std::string FileCache::read(const std::string& key)
{
	 auto hash = std::hash<std::string>()(key);

	std::string key_, value;
	std::fstream file;
	file.open(std::to_string(hash) + format, std::fstream::in);
	if (!file.is_open())
		return {};
	while (file >> key_ >> value)
	{
		if (key_ == key)
			return value;
	}
	file.close();
	return {};
}

bool FileCache::has(const std::string& key)
{
	auto hash = std::hash<std::string>()(key);

	std::string key_, value;
	std::fstream file;
	file.open(std::to_string(hash) + format, std::fstream::in);
	if (!file.is_open())
		return false;
	while (file >> key_ >> value)
	{
		if (key_ == key)
			return true;
	}
	file.close();
	return false;
}

FileCache::~FileCache()
{
	for (const auto& i : filenames)
		remove(i.data());
}


