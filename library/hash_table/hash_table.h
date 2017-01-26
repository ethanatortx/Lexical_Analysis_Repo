#ifndef __HASH_TABLE_H_INCLUDED__
#define __HASH_TABLE_H_INCLUDED__

#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <utility>
#include "hash\hash.h"
#include "linked_list\linked_list.h"

namespace hash_dec
{
	template <typename T>
	using hash = std::pair<T, std::string>;
	template <typename T>
	using bucket = linked_list<hash<T>>;
}

using namespace hash_dec;
template <class T>
class hash_table: 
	virtual public std::vector<bucket<T>>
{
	std::vector<typename hash_table<T>::bucket> table;
	std::size_t bucket_constant;

	std::vector<T> readin(const hash_table<T>&);

public:

	using iterator = typename std::vector<bucket<T>>::iterator;
	using const_iterator = typename std::vector<bucket<T>>::const_iterator;

	hash_table(std::size_t bucket_constant): 
		bucket_constant(bucket_constant),
		table(new typename std::vector<bucket<T>>()) {}
	hash_table(const hash_table<T>& other):
		bucket_constant(other.bucket_constant),
		table(new typename std::vector<bucket<T>>())
	{
		std::vector<T> data = readin(other);

		typename std::vector<T>::iterator it = data.begin();

		for(; it != data.end(); it++)
		{
			this->add(*it);
		}
	}


	using typename std::vector<bucket<T>>::operator=;
	using assign = typename std::vector<bucket<T>>::assign;

	using at = typename std::vector<bucket<T>>::at;
	using typename std::vector<bucket<T>>::operator[];

	using begin = typename std::vector<bucket<T>>::begin;
	using cbegin = typename std::vector<bucket<T>>::cbegin;
	using rbegin = typename std::vector<bucket<T>>::rbegin;
	using crbegin = typename std::vector<bucket<T>>::crbegin;

	using end = typename std::vector<bucket<T>>::end;
	using cend = typename std::vector<bucket<T>>::cend;
	using rend = typename std::vector<bucket<T>>::rend;
	using crend = typename std::vector<bucket<T>>::crend;

	using empty = typename std::vector<bucket<T>>::empty;
	using size = typename std::vector<bucket<T>>::size;
	using max_size = typename std::vector<bucket<T>>::max_size;
	using reserve = typename std::vector<bucket<T>>::reserve;
	using capacity = typename std::vector<bucket<T>>::capacity;
	using shrink_to_fit = typename std::vector<bucket<T>>::shrink_to_fit;

	using clear = typename std::vector<bucket<T>>::clear;

	void resize(std::size_t);

	void add(const T&);
	void add(T&&);

	inline bool operator==(const hash_table<T>& other) const { return this->table == other.table; }
	inline bool operator!=(const hash_table<T>& other) const { return this->table != other.table; }
	inline bool operator<(const hash_table<T>& other) const { return this->table < other.table; }
	inline bool operator<=(const hash_table<T>& other) const { return this->table <= other.table; }
	inline bool operator>(const hash_table<T>& other) const { return this->table > other.table; }
	inline bool operator>=(const hash_table<T>& other) const { return this->table >= other.table; }
};

template <class T>
std::vector<T> hash_table<T>::readin(const hash_table<T>& other)
{
	hash_table<T>::iterator it = other.begin();
	typename bucket<T>::iterator list_it;

	std::vector<T> input;

	for(; it != other.end(); it++)
	{
		list_it = (*it).begin();
		for(; list_it != (*it).end(); list_it++)
		{
			input.push_back(*list_it);
		}
	}

	return input;
}

template <class T>
void hash_table<T>::resize(std::size_t bc)
{

}

template <class T>
void hash_table<T>::add(const T& val)
{

}

template <class T>
void hash_table<T>::add(T&& val)
{

}

#endif