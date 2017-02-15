#ifndef HASH_H
#define HASH_H

#include <functional>

template<class T,
		 class Hash = std::hash<T*>>
class hash_map
{

	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef Hash hasher;

public:
	hash_map() {}

	void clear();
	bool empty() const;

private:
	hash_map(const hash_map<T, Hash>& rhs) {}
};

#endif