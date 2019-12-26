#pragma once
#include "BloomFilter.hpp"
#include "../BloomFilterC/bloom-filter.h"


class BloomFilterAdapter final: public  baseFilter<void*>
{
	BloomFilter* bf;
public:
	BloomFilterAdapter(unsigned int tableSize, BloomFilterHashFunc hashFunc, unsigned int numFunc);
	BloomFilterAdapter(BloomFilter* bf);
	
	~BloomFilterAdapter() override;
	void insert(void* const& value) override;
	int query(void* const& value) override;
	void read(std::vector<unsigned char>& array) override;
	void load(std::vector<unsigned char>& array) override;
	baseFilter<void*>* unionBF(baseFilter* filter2) override;
	baseFilter<void*>* intersection(baseFilter* filter2) override;

	BloomFilter* data();
};

