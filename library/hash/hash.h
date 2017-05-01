#ifndef HASH_H
#define HASH_H

#include <functional>
#include <iostream>
#include <exception>
#include <memory>
#include "math_utility\math_utility.h"
#include "vector\vector.h"

namespace hash
{
	template<class Key,
			 class MappedValue,
			 class Hash = std::hash<Key> >
	class hash_map
	{
		struct Node
		{
			Node(const Key& _key, const MappedValue& _value):
				value(_value)
			{
				hash = Hash(_key);
			}
			std::size_t hash;
			MappedValue value;
		};

		typedef Key key_type;
		typedef MappedValue mapped_value;
		typedef Hash hasher;
		typedef std::size_t size_type;

	public:
		hash_map(size_type = 101, size_type = 1);
		hash_map(const hash_map<Key, MappedValue, Hash>&);

		hash_map<key_type, mapped_value, hasher>& operator=(const hash_map<key_type, mapped_value, hasher>&);

		bool empty() const;

		bool is_node(const key_type&) const;
		
		mapped_value get(const key_type&) const;

		void clear();

		void emplace(const key_type&, const mapped_value&);

		void erase(const key_type&, const mapped_value&);

		size_type elements() const;

		template<class A, class B, class C>
		friend bool operator==(const hash_map<A, B, C>&, const hash_map<A, B, C>&);
		template<class A, class B, class C>
		friend bool operator!=(const hash_map<A, B, C>&, const hash_map<A, B, C>&);
		template<class A, class B, class C>
		friend void swap(hash_map<A, B, C>&, hash_map<A, B, C>&);

		std::string to_string() const;

		template<class A, class B, class C>
		friend std::ostream& operator<<(std::ostream&, const hash_map<A, B, C>&);
		template<class A, class B, class C>
		friend std::istream& operator>>(std::istream&, hash_map<A, B, C>&);

	private:
		Node*** map;
		size_type _size;
		size_type _bucket_constant;
	};

	template<class Key, class MappedValue, class Hash>
	hash_map<Key, MappedValue, Hash>::hash_map(hash_map<Key, MappedValue, Hash>::size_type S, hash_map<Key, MappedValue, Hash>::size_type BC):
		_size(S), _bucket_constant(BC)
	{
		map = new Node*[_size];
		for(int i = 0; i < _size; ++i)
		{
			map[i] = new Node[_bucket_constant];
		}
	}

	template<class Key, class MappedValue, class Hash>
	inline hash_map<Key, MappedValue, Hash>::hash_map(const hash_map<Key, MappedValue, Hash>& other)
	{
		this->operator=(other);
	}

	template<class Key, class MappedValue, class Hash>
	inline hash_map<Key, MappedValue, Hash>& hash_map<Key, MappedValue, Hash>::operator=(const hash_map<Key, MappedValue, Hash& rhs)
	{

	}

	template<class Key, class MappedValue, class Hash>
	inline bool hash_map<Key, MappedValue, Hash>::empty() const
		{ return (elements() == 0); }

	template<class Key, class MappedValue, class Hash>
	inline bool hash_map<Key, MappedValue, Hash>::is_node(const Key& _key) const
	{
		index = (Hash(_key) % _size);
		for(int i = 0; i < _bucket_constant; ++i)
		{
			if(map[index][i]->hash = Hash(_key)) return true;
		}

		return false;
	}

	template<class Key, class MappedValue, class Hash>
	inline MappedValue hash_map<Key, MappedValue, Hash>::get(const Key& _key)
	{
		hash_map<Key, MappedValue, Hash>::size_type key_hash = Hash(_key);
		hash_map<Key, MappedValue, Hash>::size_type index = key_hash % _size;

		std::cout << "Checking bucket " << index << " for node with key: " << _key << " key hash: " << key_hash << std::endl;
		for(hash_map<Key, MappedValue, Hash>::size_type i = 0; i < _bucket_constant; ++i)
		{
			std::cout << map[index][i]->data;
			if(map[index][i]->hash == key_hash) return map[index][i]->data;
		}
	}

	template<class Key, class MappedValue, class Hash>
	inline void hash_map<Key, MappedValue, Hash>::clear()
	{
		for(hash_map<Key, MappedValue, Hash>::size_type p = 0; p < _size; ++p)
		{
			for(hash_map<Key, MappedValue, Hash>::size_type q = 0; q < _bucket_constant; ++q)
			{
				delete map[p][q];
			}
			delete map[p];
		}
		delete map;
	}

	template<class Key, class MappedValue, class Hash>
	void hash_map<Key, MappedValue, Hash>::emplace(const Key& _key, const MappedValue& _value)
	{
		hash_map<Key, MappedValue, Hash>::Node* n = new hash_map<Key, MappedValue, Hash>::Node(_key, _value);
		hash_map<Key, MappedValue, Hash>::size_type index = (n->hash) % _size;
		hash_map<Key, MappedValue, Hash>::size_type index_inner = (n->hash) % _bucket_constant;

		if(map[index][index_inner]->hash == n->hash)
		{
			throw hash::exception::key_value_pair_already_exists();
			delete n;
			return;
		}

		map[index][index_inner] = n;
	}

	template<class Key, class MappedValue, class Hash>
	void 
};


#endif