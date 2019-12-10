#pragma once
#include "ObjectPool.hpp"
#include <string>
#include <functional>

namespace trie
{
	static const unsigned short amountChildren = 16;
	unsigned int getIndex(unsigned int hash, unsigned short stage)
	{
		return (hash << (4 * stage)) >> 28;
	}
	
	template <typename T>
	class SubTrie final
	{
		std::pair<const std::string, T> data_;
		unsigned int hash_;
		unsigned short stage_;
		ObjectPool<SubTrie<T>> child_;
		size_t size_;

	public:

		SubTrie(const T& value, const std::string& key, const unsigned int hash, const unsigned short stage, const size_t size_ = 1);
		SubTrie& operator=(const SubTrie& st) = default;
		SubTrie(const SubTrie& st) = default;
		SubTrie(SubTrie&& st) = default;
		SubTrie& operator=(SubTrie&& st) = default;
		~SubTrie() = default;
		
		std::pair<T&,bool> operator[](const std::string& key);
		std::pair<const T&,bool> operator[](const std::string& key)const;
		
		std::pair<std::pair<const std::string, T>, bool> insert(const std::string& key, const T& val, const unsigned int hash);
		
		bool childless() const;
		size_t size() const;
		
		size_t erase(const std::string& key, const unsigned int hash);
		
		const std::pair<const std::string, T>& data() const;
		std::pair<const std::string, T>& data();
		
		std::pair<const std::string, T>* find(const std::string& key,const unsigned int hash);
		const std::pair<const std::string, T>* find(const std::string& key, const unsigned int hash) const;
		std::pair<const std::string, T>* findNext(const std::string& key,const unsigned int hash);
		const std::pair<const std::string, T>* findNext(const std::string& key, const unsigned int hash) const;
		std::pair<const std::string, T>* findFirst();
		const std::pair<const std::string, T>* findFirst() const;
		SubTrie& findNonEmptyChild();
	};

	//-----------------------------------------------------------------SubTrie-----------------------------------------------------------------------//
	
	template <typename T>
	SubTrie<T>::SubTrie(const T& value, const std::string& key, const unsigned int hash, const unsigned short stage, const size_t size)
		: data_{ key, value }
		, hash_(hash)
		, stage_(stage)
		, child_(ObjectPool<SubTrie<T>>(amountChildren))
		, size_(size){}

	template <typename T>
	std::pair<std::pair<const std::string, T>, bool> SubTrie<T>::insert(const std::string& key, const T& val, const unsigned int hash)
	{
		unsigned int recieved_index = getIndex(hash, stage_);
		unsigned int current_index = getIndex(hash_, stage_);
		if (stage_ == 7 || key == data_.first)
		{		
			return { {{}, {}}, false };            
		}
		if (child_.empty_block(current_index) && size_ == 1)
		{
			child_.alloc(current_index, data_.second, data_.first, hash_, stage_ + 1);
		}
		if (child_.empty_block(recieved_index))
		{
			auto ex = child_.alloc(recieved_index, val, key, hash, stage_ + 1);
			++size_;
			return { ex->data(), true };
		}
		return child_[recieved_index].insert(key, val, hash);

	}

	template <typename T>
	std::pair<T&,bool> SubTrie<T>::operator[](const std::string& key)
	{
		if (key == data_.first)
		{
			unsigned int ind = getIndex(hash_, stage_);
			if (child_.empty()) {
				return { data_.second,false };
			}
			if (child_.empty_block(ind))
				insert(key, {}, hash_);
			return child_[ind][key];
		}
		const size_t hash = std::hash<std::string>()(key);
		const unsigned int ind = getIndex(hash, stage_);
		if (child_.empty_block(ind)) {
			auto [data, insertStatus] = insert(key, {}, hash);
			return { child_[ind][key].first, insertStatus };
		}
		return child_[ind][key];
	}

	template <typename T>
	 std::pair<const T&, bool> SubTrie<T>::operator[](const std::string& key) const
	{
		 if (key == data_.first)
		 {
			 const unsigned int ind = getIndex(hash_, stage_);
			 if (!child_.empty() && child_.empty_block(ind)) {
				 throw std::out_of_range("empty block");
			 }
			 if (child_.empty()) {
				 return { data_.second,false };
			 }
			 return child_[ind][key];
		 }
		 const size_t hash = std::hash<std::string>()(key);
		 const unsigned int ind = getIndex(hash, stage_);
		 if (child_.empty_block(ind)) {
			 throw std::out_of_range("empty block");
		 }
		 return child_[ind][key];
	}


	template <typename T>
	bool SubTrie<T>::childless() const
	{
		return child_.empty();
	}

	template <typename T>
	size_t SubTrie<T>::erase(const std::string& key, const unsigned hash)
	{
		const unsigned int index = getIndex(hash, stage_);
		if (child_.empty_block(index))
		{
			return 0;
		}
		auto& leaf = child_[index];
		if (leaf.childless())
		{
			if (leaf.data().first != key)
			{
				return 0;
			}
			--size_;
			child_.delete_obj(&leaf);
			return 1;
		}
		auto res = leaf.erase(key, hash);
		if (leaf.childless())
			child_.delete_obj(&leaf);
		else if(leaf.size() == 1)
		{
			auto tmp = leaf.findNonEmptyChild();
			child_.delete_obj(&leaf);
			child_.alloc(index, tmp);
		}
		return res;
	}

	template <typename T>
	const std::pair<const std::string, T>& SubTrie<T>::data() const
	{
		return data_;
	}

	template <typename T>
	std::pair<const std::string, T>& SubTrie<T>::data()
	{
		return data_;
	}

	
	template <typename T>
	std::pair<const std::string, T>* SubTrie<T>::findNext(const std::string& key, const unsigned hash)
	{
		const unsigned int ind = getIndex(hash, stage_);
		if (child_.empty_block(ind))												//non valid -  idc
			return nullptr;
		if (!child_[ind].childless())
			return child_[ind].findNext(key, hash);                               //next not in this sub
		for (unsigned int i = ind + 1; i != amountChildren; ++i)
		{
			if (!child_.empty_block(i))
				return child_[i].findFirst();
		}
		return nullptr;
	}

	template <typename T>
	std::pair<const std::string, T>* SubTrie<T>::findFirst()
	{
		if (child_.empty())
			return &data_;

		for (int i = 0; i < amountChildren; ++i)
		{
			if (!child_.empty_block(i))
				return child_[i].findFirst();
		}
	}

	template <typename T>
	std::pair<const std::string, T>* SubTrie<T>::find(const std::string& key, const unsigned hash)
	{
		if (key == data_.first)
		{
			const unsigned int ind = getIndex(hash_, stage_);;
			if (child_.empty() || child_.empty_block(ind)) {
				return &data_;
			}
			return child_[ind].find(key, hash);
		}
		const unsigned int ind = getIndex(hash, stage_);;
		if (child_.empty() || child_.empty_block(ind))
		{
			if (stage_ == 7)
			{
				throw std::length_error("");
			}
			return nullptr;
		}
		return child_[ind].find(key, hash);
	}

	template <typename T>
	size_t SubTrie<T>::size() const
	{
		return size_;
	}

	template <typename T>
	SubTrie<T>& SubTrie<T>::findNonEmptyChild()
	{
		return child_.firstNonEmpty();
	}

	template <typename T>
	const std::pair<const std::string, T>* SubTrie<T>::find(const std::string& key, const unsigned hash) const
	{
		if (key == data_.first)
		{
			const unsigned int ind = getIndex(hash_, stage_);;
			if (child_.empty() || child_.empty_block(ind)) {
				return &data_;
			}
			return child_[ind].find(key, hash);
		}
		const unsigned int ind = getIndex(hash, stage_);;
		if (child_.empty() || child_.empty_block(ind))
		{
			if (stage_ == 7)
			{
				throw std::length_error("");
			}
			return nullptr;
		}
		return child_[ind].find(key, hash);
	}

	template <typename T>
	const std::pair<const std::string, T>* SubTrie<T>::findNext(const std::string& key, const unsigned hash) const
	{
		unsigned int ind = getIndex(hash, stage_);
		if (child_.empty_block(ind))												//non valid -  idc
			return nullptr;
		if (!child_[ind].childless())
			return child_[ind].findNext(key, hash);                               //next not in this sub
		for (unsigned int i = ind + 1; i != amountChildren; ++i)
		{
			if (!child_.empty_block(i))
				return child_[i].findFirst();
		}
		return nullptr;
	}

	template <typename T>
	const std::pair<const std::string, T>* SubTrie<T>::findFirst() const
	{
		if (child_.empty())
			return &data_;

		for (int i = 0; i < amountChildren; ++i)
		{
			if (!child_.empty_block(i))
				return child_[i].findFirst();
		}
	}


}