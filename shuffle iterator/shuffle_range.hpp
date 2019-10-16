#pragma once
#include <iterator>
#include  <algorithm>
#include <random>
#include <vector>


template<typename Iter>
class shuffle_range final
{
	Iter begin_;
	Iter end_;
	std::vector<Iter>  sequence;
public:
	shuffle_range(Iter& _begin, Iter& _end);
public:
	template <typename T>
	class shuffle_iterator final
	{
		typename std::conditional<std::is_const<T>::value, const shuffle_range&, shuffle_range&>::type parent;
		Iter current;
		int pos;

	public:
		using iterator_category = std::forward_iterator_tag;
		using  value_type = T;
		using pointer = T*;
		using reference = std::remove_reference_t<T>&;
		using const_reference = const std::remove_reference_t<T>&;
		
		shuffle_iterator(typename std::conditional<std::is_const<T>::value, const shuffle_range&, shuffle_range&>::type parent, Iter cur);
		shuffle_iterator& operator ++();
		shuffle_iterator operator ++(int);
		bool operator ==(const shuffle_iterator& ex) const;
		bool operator !=(const shuffle_iterator& ex) const;
		reference operator*();
		const_reference operator*() const;
	};
	using const_shuffle_iterator = shuffle_iterator<const typename std::iterator_traits<Iter>::value_type>;
public:
	auto begin();
	auto end();
	const_shuffle_iterator begin() const;
	const_shuffle_iterator end() const;
	const_shuffle_iterator cbegin() const;
	const_shuffle_iterator cend() const ;
};

template<typename T>
shuffle_range<T> make_shuffle(T begin, T end)
{
	return shuffle_range<T>(begin, end);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
template<typename Iter>
shuffle_range<Iter>::shuffle_range(Iter& _begin, Iter& _end) :begin_(_begin), end_(_end)
{
	for (auto& i = _begin; i != _end; ++i)
	{
		sequence.push_back(i);
	}
	std::random_device rd;
	std::mt19937 alg(rd());
	std::shuffle(sequence.begin(), sequence.end(), alg);
}


template <typename Iter>
template <typename T>
shuffle_range<Iter>::shuffle_iterator<T>::shuffle_iterator(typename std::conditional<std::is_const<T>::value, 
														   const shuffle_range&, shuffle_range&>::type parent, Iter cur)
														   :parent(parent), current(cur), pos(0) {}

template <typename Iter>
template <typename T>
typename shuffle_range<Iter>::shuffle_iterator<T>& shuffle_range<Iter>::shuffle_iterator<T>::operator++()
 {
	pos++;
	if (pos < parent.sequence.size()) {
		current = parent.sequence[pos];
	}
	else {
		current = parent.end_;
	}
	return *this;
}

template <typename Iter>
template <typename T>
typename shuffle_range<Iter>::shuffle_iterator<T> shuffle_range<Iter>::shuffle_iterator<T>::operator++(int)
{
	shuffle_iterator tmp = *this;
	++(*this);
	return tmp;
}

template <typename Iter>
template <typename T>
bool shuffle_range<Iter>::shuffle_iterator<T>::operator==(const shuffle_iterator& ex) const
{
	return current == ex.current && &parent == &ex.parent;
}

template <typename Iter>
template <typename T>
bool shuffle_range<Iter>::shuffle_iterator<T>::operator!=(const shuffle_iterator& ex) const {
	return !((*this) == ex);
}

template <typename Iter>
template <typename T>
typename shuffle_range<Iter>::shuffle_iterator<T>::reference shuffle_range<Iter>::shuffle_iterator<T>::operator*()
{
	return *current;
}

template <typename Iter>
template <typename T>
typename shuffle_range<Iter>::shuffle_iterator<T>::const_reference shuffle_range<Iter>::shuffle_iterator<T>::operator*() const
{
	return *current;
}


template <typename Iter>
auto shuffle_range<Iter>::begin()
{
	if (sequence.empty())
		return shuffle_iterator<typename std::iterator_traits<Iter>::value_type>(*this, begin_);
	return shuffle_iterator<typename std::iterator_traits<Iter>::value_type>(*this, sequence[0]);
}

template <typename Iter>
auto shuffle_range<Iter>::end()
{
	return shuffle_iterator<typename std::iterator_traits<Iter>::value_type>(*this, end_);
}

template <typename Iter>
typename shuffle_range<Iter>::const_shuffle_iterator shuffle_range<Iter>::begin() const
{
	if (sequence.empty())
		return const_shuffle_iterator(*this, begin_);
	return const_shuffle_iterator(*this, sequence[0]);
}

template <typename Iter>
typename shuffle_range<Iter>::const_shuffle_iterator shuffle_range<Iter>::end() const
{
	return const_shuffle_iterator(*this, end_);
}

template <typename Iter>
typename shuffle_range<Iter>::const_shuffle_iterator shuffle_range<Iter>::cbegin() const
{
	return begin();
}

template <typename Iter>
typename shuffle_range<Iter>::const_shuffle_iterator shuffle_range<Iter>::cend() const
{
	return end();
}




