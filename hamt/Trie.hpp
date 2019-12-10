#pragma once
#include "ObjectPool.hpp"
#include <string>
#include <iterator>
#include <functional>
#include "SubTrie.hpp"

namespace trie {
	template <typename T>
	class Trie final
	{
		ObjectPool<SubTrie<T>> child_;
		size_t size_;
		
	public:
		template<bool Const = false>
		class trie_iterator
		{
		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = std::pair<const std::string, T>;
			using pointer = std::conditional_t<Const, const std::pair<const std::string, T>*, std::pair<const std::string, T>*>;
			using reference = std::conditional_t<Const,const  std::pair<const std::string, T>&, std::pair<const std::string, T>&>;
			
			trie_iterator(std::conditional_t<Const, const Trie<T>&, Trie<T>&> parent, pointer ptr);
			trie_iterator(std::conditional_t<Const, const Trie<T>&, Trie<T>&> parent);

			trie_iterator& operator++();
			trie_iterator operator++(int);
			bool operator!=(const trie_iterator& it) const;
			bool operator==(const trie_iterator& it) const;
			reference operator*();
			reference operator*() const;
		private:
			std::conditional_t<Const, const Trie<T>&, Trie<T>&> parent;
			pointer data_ptr;
			
		};
		using iterator = trie_iterator<false>;
		using const_iterator = trie_iterator<true>;
	public:
		Trie();

		template <typename InputIterator>
		Trie(InputIterator first, InputIterator last);
		Trie(Trie&& st) = default;
		Trie& operator=(Trie && st) = default;
		Trie(const Trie<T>& trie) = default;
		~Trie() = default;
		Trie<T>& operator= (const Trie& trie) = default;

		iterator begin();
		const_iterator cbegin() const;

		iterator end();
		const_iterator cend() const;

		bool empty() const;
		size_t size() const;

		T& operator[] (const std::string& key);
		const T& operator[] (const std::string& key)const;

		std::pair<iterator, bool> insert(const std::string& key, const T& val);

		template <class InputIterator> void insert(InputIterator first, InputIterator last);

		void erase(iterator position);
		size_t erase(const std::string& key);
		
		void erase(iterator first, iterator last);

		void swap(Trie<T>& trie) noexcept;

		void clear();

		iterator find(const std::string& key);
		const_iterator find(const std::string& k) const;
	};

	
	//------------------------------------------------TRIE----------------------------------------------------------------------//
	template <typename T>
	Trie<T>::Trie() : child_{ {amountChildren} }, size_{}{}

	template <typename T>
	template <typename InputIterator>
	Trie<T>::Trie(InputIterator first, InputIterator last) : child_({amountChildren}), size_{}
	{
		insert(first, last);
	}

	template <typename T>
	typename Trie<T>::iterator Trie<T>::begin()
	{
		if (size_ == 0)
			return end();
		for(int i = 0; i!=amountChildren; ++i)
		{
			if(!child_.empty_block(i))
			{
				return trie_iterator(*this, child_[i].findFirst());
			}
		}
	}

	template <typename T>
	typename Trie<T>::const_iterator Trie<T>::cbegin() const
	{
		if (size_ == 0)
			return cend();
		for (int i = 0; i != amountChildren; ++i)
		{
			if (!child_.empty_block(i))
			{
				return const_iterator(*this, child_[i].findFirst());
			}
		}
	}

	template <typename T>
	typename Trie<T>::iterator Trie<T>::end()
	{
		return {*this, nullptr };
	}

	template <typename T>
	typename Trie<T>::const_iterator Trie<T>::cend() const
	{
		return  { *this, nullptr };
	}

	template <typename T>
	bool Trie<T>::empty() const
	{
		return size_ == 0;
	}
	
	template <typename T>
	template <bool Const>
	Trie<T>::trie_iterator<Const>::trie_iterator(std::conditional_t<Const, const Trie<T>&, Trie<T>&> parent, pointer ptr):parent(parent), data_ptr(ptr){}

	template <typename T>
	template <bool Const>
	Trie<T>::trie_iterator<Const>::trie_iterator(std::conditional_t<Const,  const Trie<T>&, Trie<T>&> parent):parent(parent), data_ptr(nullptr){}


	template <typename T>
	std::pair<typename Trie<T>::iterator, bool> Trie<T>::insert(const std::string& key, const T& val)
	{
		const unsigned int hash = std::hash<std::string>()(key);
		const unsigned int ind = getIndex(hash, 0);
		SubTrie<T>* st;
		if (child_.empty_block(ind)) {
			st = child_.alloc(ind, val, key, hash, 1, true);
			++size_;
			return  { iterator(*this, &st->data()),true };                                       
		}
		st = &child_[ind];
		auto res = st->insert(key, val, hash);
		if (res.second)
			++size_;
		return { { *this, &res.first }, res.second };
	};

	template <typename T>
	template <class InputIterator>
	void Trie<T>::insert(InputIterator first, InputIterator last)
	{
		for(auto i = first; i!= last; ++i)
		{
			insert((*i).first, (*i).second);
		}
	}

	template <typename T>
	T& Trie<T>::operator[](const std::string& key)
	{
		const size_t hash = std::hash<std::string>()(key);
		const unsigned int ind = getIndex(hash, 0);
		if(child_.empty_block(ind))
		{
			auto st = child_.alloc(ind, T(), key, hash, 1, true);
			++size_;
			return st->operator[](key).first;
		}
		auto [res, insertStatus] = child_[ind][key];
		if (insertStatus)
			++size_;
		return res;
	}

	template <typename T>
	const T& Trie<T>::operator[](const std::string& key) const
	{
		const size_t hash = std::hash<std::string>()(key);
		const unsigned int ind = getIndex(hash, 0);
		if (child_.empty_block(ind))
		{
			throw std::out_of_range("empty block");
		}
		auto [res, insertStatus] = child_[ind][key];
		return res;
	}


	template <typename T>
	size_t Trie<T>::size() const
	{
		return size_;
	}

	template <typename T>
	size_t Trie<T>::erase(const std::string& key)
	{
		const size_t hash = std::hash<std::string>()(key);
		const unsigned int index = getIndex(hash, 0);
		if(child_.empty_block(index))
		{
			return 0;
		}
		auto& leaf = child_[index];
		if(leaf.childless())
		{
			if(child_[index].data().first != key)
			{
				return 0;
			}
			child_.delete_obj(&leaf);
			--size_;
			return 1;
		}
		if(leaf.erase(key, hash) == 1)
		{
			--size_;
			if (leaf.childless() && leaf.data().first == key)
				child_.delete_obj(&leaf);
			else if(leaf.data().first == key && leaf.size() == 1)
			{
				auto tmp = leaf.findNonEmptyChild();
				child_.delete_obj(&leaf);
				child_.alloc(index, tmp);
			}
			return 1;
		}
		if (empty())
			clear();
		return 0;
	}

	template <typename T>
	template <bool Const>
	typename Trie<T>::trie_iterator<Const>& Trie<T>::trie_iterator<Const>::operator++()
	{
		if (!data_ptr)
			return *this;
		const unsigned int hash = std::hash<std::string>()(data_ptr->first);
		const unsigned short index = getIndex(hash,0);

		if (parent.child_.empty_block(index))				//non-valid iterator
		{
			data_ptr = nullptr;
			return *this;
		}

		if(!parent.child_[index].childless())
		{
			data_ptr = parent.child_[index].findNext(data_ptr->first, hash);
			if (data_ptr)																			//iterator is not last in sub
				return *this;
		}
		
		for(int i = index+1 ;i != amountChildren; ++i)
		{
			if (!parent.child_.empty_block(i))
			{
				data_ptr = parent.child_[i].findFirst();
				return *this;
			}
		}
		data_ptr = nullptr;
		return *this;
	}

	template <typename T>
	template <bool Const>
	typename Trie<T>::trie_iterator<Const> Trie<T>::trie_iterator<Const>::operator++(int)
	{
		auto tmp = *this;
		++(*this);
		return tmp;
	}


	template <typename T>
	void Trie<T>::clear()
	{
		child_.clear();
		size_ = 0;
	}

	template <typename T>
	void Trie<T>::erase(iterator position)
	{
		if (position == end())
			return;
		erase((*position).first);
	}

	template <typename T>
	void Trie<T>::erase(iterator first, iterator last)
	{
		auto tmp = first;
		while (tmp != last) {
			erase(tmp++);
		}
	}


	template <typename T>
	template <bool Const>
	typename Trie<T>::trie_iterator<Const>::reference Trie<T>::trie_iterator<Const>::operator*()
	{
		return *data_ptr;
	}

	template <typename T>
	template <bool Const>
	typename Trie<T>::trie_iterator<Const>::reference Trie<T>::trie_iterator<Const>::operator*() const
	{
		return *data_ptr;
	}


	template <typename T>
	template <bool Const>
	bool Trie<T>::trie_iterator<Const>::operator!=(const trie_iterator& it) const
	{
		return !((*this) == it);
	}
	
	template <typename T>
	template <bool Const>
	bool Trie<T>::trie_iterator<Const>::operator==(const trie_iterator& it) const
	{
		return (data_ptr == it.data_ptr && &parent == &it.parent);
	}

	template <typename T>
	typename Trie<T>::iterator Trie<T>::find(const std::string& key)
	{
		const size_t hash = std::hash<std::string>()(key);
		const unsigned int ind = getIndex(hash,0);
		if (child_.empty_block(ind))
		{
			return end();
		}
		return { *this, child_[ind].find(key, hash) };
	}

	template <typename T>
	typename Trie<T>::const_iterator Trie<T>::find(const std::string& key) const
	{
		const size_t hash = std::hash<std::string>()(key);
		unsigned int ind = getIndex(hash,0);
		if (child_.empty_block(ind))
		{
			return cend();
		}
		return { *this, child_[ind].find(key, hash) };
	}


	template <typename T>
	void Trie<T>::swap(Trie<T>& trie) noexcept
	{
		std::swap(trie, *this);
	}



}

