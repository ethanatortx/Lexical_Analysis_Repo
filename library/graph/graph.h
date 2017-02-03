#ifndef GRAPH_H
#define GRAPH_H

#include <functional>
#include <memory>
#include <utility>
#include <vector>
#include "linked_list\linked_list.h"
#include "hash\hash.h"

namespace 
{
	template<class dtype>
	class Node
	{
	public:
		inline dtype get_data() const
		{
			return data;
		}
		
		inline std::vector<Node<dtype>* > get_adj() const
		{
			return adjacent;
		}
		
		inline void clear()
		{
			adjacent.clear();
		}
		
		inline bool empty() const 
		{
			return adjacent.empty();
		}
		
		inline void add_edge(Node<dtype>* n)
		{
			adjacent.push_back(n);
		}

		inline void erase_edge(Node<dtype>* n)
		{
			std::vector<Node<dtype>* >::iterator it;
			for (; (*it) != n; ++it) {}
			adjacent.erase(it);
		}

	private:
		dtype data;
		linked_list<Node<dtype>* > adjacent;
	};
}

template<class T,
		 class Hash = std::hash<T> >
class graph
{

public:

};

#endif