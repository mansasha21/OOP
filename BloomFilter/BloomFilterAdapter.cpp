#include "BloomFilterAdapter.hpp"
#include <stdexcept>

BloomFilterAdapter::BloomFilterAdapter(unsigned tableSize, BloomFilterHashFunc hashFunc, unsigned numFunc)
{
	bf = bloom_filter_new(tableSize, hashFunc, numFunc);
	if (bf == NULL)
		throw std::invalid_argument("bad params");
}

BloomFilterAdapter::BloomFilterAdapter(BloomFilter* bf_)
{
	if (bf)
		bloom_filter_free(bf);
	bf = bf_;
}


BloomFilterAdapter::~BloomFilterAdapter()
{
	bloom_filter_free(bf);
}

void BloomFilterAdapter::insert(void* const& value)
{
	bloom_filter_insert(bf, value);
}



BloomFilter* BloomFilterAdapter::data()
{
	return bf;
}

void BloomFilterAdapter::load(std::vector<unsigned char>& array)
{
	bloom_filter_load(bf, array.data());
}

int BloomFilterAdapter::query(void* const& value)
{
	return bloom_filter_query(bf, value);
}

void BloomFilterAdapter::read(std::vector<unsigned char>& array)
{
	bloom_filter_read(bf, array.data());
}


baseFilter<void*>* BloomFilterAdapter::intersection(baseFilter* filter2)
{
	auto bf2 = dynamic_cast<BloomFilterAdapter*>(filter2)->data();
	auto res = bloom_filter_intersection(bf, bf2);
	if(!res)
	{
		return new nullFilter<void*>;
	}
	return new BloomFilterAdapter(res);
}

baseFilter<void*>* BloomFilterAdapter::unionBF(baseFilter* filter2)
{
	auto bf2 = dynamic_cast<BloomFilterAdapter*>(filter2)->data();
	auto res = bloom_filter_union(bf, bf2);
	if (!res)
	{
		return new nullFilter<void*>;
	}
	return new BloomFilterAdapter(res);
}
