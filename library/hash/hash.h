#ifndef HASH_H
#define HASH_H

#include <functional>
#include <iterator>
#include <vector>
#include "linked_list\linked_list.h"

template<typename T>
using bucket = linked_list<T>;

template<class Key,
		 class Data = Key,
		 class Hash = std::hash<Key>
		 >
class hash_table
{
	
};

#endif