#pragma once
#include <vector>
#include <array>
#include <stdexcept>
#include <algorithm>
#include <memory>

template <typename T>
class baseFilter
{
public:
	virtual void insert(const T& value) = 0;
	virtual int query(const T& value) = 0;
	virtual void read(std::vector<unsigned char>& array) = 0;
	virtual void load(std::vector<unsigned char>& array) = 0;

	virtual baseFilter<T>* unionBF(baseFilter* filter2) = 0;
	virtual baseFilter<T>* intersection(baseFilter* filter2) = 0;
	
	virtual ~baseFilter() = default;
	
};

template <typename T>
class nullFilter final :  public baseFilter<T>
{
public:
	nullFilter() {};
	~nullFilter() {};
	void insert(const T& value) override {}
	int query(const T& value) override { return 0; }
	void read(std::vector<unsigned char>& array) override {}
	void load(std::vector<unsigned char>& array) override {}

	baseFilter<T>* unionBF (baseFilter<T>* filter2) override { return new nullFilter(); }
	baseFilter<T>* intersection(baseFilter<T>* filter2) override { return new nullFilter(); }
};

template <typename Hash, typename T>
class bloomFilter final : public baseFilter<T> 
{
	Hash hashFunc_;
	std::vector<unsigned char> table_;
	unsigned int tableSize_;
	unsigned int numFunctions_;
	const std::array<unsigned int,64> salts = {
	0x1953c322, 0x588ccf17, 0x64bf600c, 0xa6be3f3d,
	0x341a02ea, 0x15b03217, 0x3b062858, 0x5956fd06,
	0x18b5624f, 0xe3be0b46, 0x20ffcd5c, 0xa35dfd2b,
	0x1fc4a9bf, 0x57c45d5c, 0xa8661c4a, 0x4f1b74d2,
	0x5a6dde13, 0x3b18dac6, 0x05a8afbf, 0xbbda2fe2,
	0xa2520d78, 0xe7934849, 0xd541bc75, 0x09a55b57,
	0x9b345ae2, 0xfc2d26af, 0x38679cef, 0x81bd1e0d,
	0x654681ae, 0x4b3d87ad, 0xd5ff10fb, 0x23b32f67,
	0xafc7e366, 0xdd955ead, 0xe7c34b1c, 0xfeace0a6,
	0xeb16f09d, 0x3c57a72d, 0x2c8294c5, 0xba92662a,
	0xcd5b2d14, 0x743936c8, 0x2489beff, 0xc6c56e00,
	0x74a4f606, 0xb244a94a, 0x5edfc423, 0xf1901934,
	0x24af7691, 0xf6c98b25, 0xea25af46, 0x76d5f2e6,
	0x5e33cdf2, 0x445eb357, 0x88556bd2, 0x70d1da7a,
	0x54449368, 0x381020bc, 0x1c0520bf, 0xf7e44942,
	0xa27e2a58, 0x66866fc5, 0x12519ce7, 0x437a8456,
	};

	bool isCorrectAmountOfNumFunc(unsigned int numFunctions) const;
	bool isCorrectParams(unsigned int tableSz1, unsigned int tableSz2, unsigned int numFunc1, unsigned int numFunc2) const;
public:
	bloomFilter(unsigned int tableSize, const Hash& hashFunc, unsigned int numFunctions);
	~bloomFilter() override = default;
	
	void insert(const T& value) override;
	int query(const T& value) override;
	void read(std::vector<unsigned char>& array) override;
	void load(std::vector<unsigned char>& array) override;

	unsigned int tableSize() const;
	unsigned int numFunctions() const;
	std::vector<unsigned char>& table();
	
	baseFilter<T>* unionBF(baseFilter<T>* filter2 ) override;
	baseFilter<T>* intersection(baseFilter<T>* filter2 ) override;
	
};

template <typename Hash, typename T>
bool bloomFilter<Hash, T>::isCorrectAmountOfNumFunc(unsigned int numFunctions) const
{
	return numFunctions <= (salts.size() / sizeof(*(salts.data())));
}

template <typename Hash, typename T>
bool bloomFilter<Hash, T>::isCorrectParams(unsigned int tableSz1, unsigned int tableSz2, unsigned int numFunc1, unsigned int numFunc2) const
{
	return tableSz1 == tableSz2 && numFunc1 == numFunc2;
}

template <typename Hash, typename T>
unsigned int bloomFilter<Hash, T>::numFunctions() const
{
	return numFunctions_;
}

template <typename Hash, typename T>
unsigned int bloomFilter<Hash, T>::tableSize() const
{
	return tableSize_;
}

template <typename Hash, typename T>
std::vector<unsigned char>& bloomFilter<Hash, T>::table()
{
	return table_;
}



template <typename Hash, typename T>
bloomFilter<Hash, T>::bloomFilter(unsigned int tableSize, const Hash& hash, unsigned int numFunctions)
{
	if (!isCorrectAmountOfNumFunc(numFunctions))
		throw std::invalid_argument("Bad amount of numFunction");
	table_ = std::vector<unsigned char>(((tableSize + 7) / 8),0);
	hashFunc_ = hash;
	numFunctions_ = numFunctions;
	tableSize_ = tableSize;
}

template <typename Hash, typename T>
void bloomFilter<Hash, T>::insert(const T& value)
{
	const unsigned int hash = hashFunc_(value);
	
	for(int i = 0;i < numFunctions_; ++i)
	{
		const unsigned int subhash = hash ^ salts[i];
		const unsigned int index = subhash % tableSize_;
		const unsigned char byte = static_cast<unsigned char>(1 << (index % 8));
		table_[index / 8] |= byte;
	}
}

template <typename Hash, typename T>
int bloomFilter<Hash, T>::query(const T& value)
{
	const unsigned int hash = hashFunc_(value);

	for (int i = 0; i < numFunctions_; ++i)
	{
		const unsigned int subhash = hash ^ salts[i];
		const unsigned int index = subhash % tableSize_;
		const unsigned char byte = table_[index / 8];
		const int bit = 1 << (index % 8);
		if ((byte & bit) == 0)
			return 0;
	}
	return 1;
}

template <typename Hash, typename T>
void bloomFilter<Hash, T>::read(std::vector<unsigned char>& array)
{
	const int arraySz = (tableSize_ + 7) / 8;
	std::copy(table_.begin(), table_.begin() + arraySz, array.begin());
}

template <typename Hash, typename T>
void bloomFilter<Hash, T>::load(std::vector<unsigned char>& array)
{
	const int arraySz = (tableSize_ + 7) / 8;
	std::copy(array.begin(), array.begin() + arraySz, table_.begin());
}

template <typename Hash, typename T>
baseFilter<T>* bloomFilter<Hash, T>::unionBF(baseFilter<T>* filter2_)
{
	auto filter2 = dynamic_cast<bloomFilter<Hash, T>*>(filter2_);
	if (!isCorrectParams(tableSize(), filter2->tableSize(), numFunctions(), filter2->numFunctions()))
		return new nullFilter<T>();

	auto res = new bloomFilter(tableSize_, hashFunc_, numFunctions_);
	const unsigned int arraySz = (tableSize_ + 7) / 8;
	
	for(int i = 0; i < arraySz; ++i)
	{
		res->table()[i] = table_[i] | filter2->table()[i];
	}
	return res;
}

template <typename Hash, typename T>
baseFilter<T>* bloomFilter<Hash, T>::intersection(baseFilter<T>* filter2_)
{
	auto filter2 = dynamic_cast<bloomFilter<Hash,T>*>(filter2_);
	if (!isCorrectParams(tableSize(), filter2->tableSize(), numFunctions(), filter2->numFunctions()))
	{
		return new nullFilter<T>();
	}

	auto res = new bloomFilter( tableSize_, hashFunc_, numFunctions_ );
	const unsigned int arraySz = (tableSize_ + 7) / 8;

	for (int i = 0; i < arraySz; ++i)
	{
		res->table()[i] = table_[i] & filter2->table()[i];
	}
	return res;
}





