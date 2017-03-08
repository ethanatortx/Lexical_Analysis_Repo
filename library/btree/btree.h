#ifndef BTREE_H
#define BTREE_H

#include <vector>
#include <array>
#include <iostream>

template<class T>
class btree
{

public:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef T const& const_reference;
	typedef std::size_t size_type;

	class node;

	typedef node* iterator;
	typedef node const* const_iterator;

	struct node
	{
		friend class btree;
		const unsigned element_constant;

		node(std::array<T, element_constant> _data, std::array<node*, element_constant+1> _children = std::array<node*, element_constant+1>()):
			data(_data), children(_children), element_constant(node_element_constant) {}

		std::array<T, element_constant> data;
		std::array<node*, element_constant> children;
	};

	btree(const unsigned n_e_const = 2);
	btree(const btree& bt);
	~btree();

	btree<T>& operator=(const btree<T>&);

	bool empty() const;
	void clear();

	iterator erase(const T& data);
	size_type deltree(iterator root);

	iterator insert(const T& data);
	iterator insert(const T& data, unsigned count);
	iterator insert(iterator root, const T& data);
	iterator insert(const_iterator root, const T& data);
	iterator insert(iterator root, const T& data, unsigned count);
	iterator insert(const_iterator root, const T& data, unsigned count);

	size_type size() const;

	std::pair<iterator, size_type> search(const T& data);

	std::string to_string() const;
	std::string to_string(iterator root) const;
	std::string to_string(std::stringstream& ss, iterator root) const;

	template<class E>
	friend std::ostream& operator<<(std::ostream&, const btree<E>&);
	template<class E>
	friend std::istream& operator>>(std::istream&, btree<E>&);
	template<class E>
	friend void quicksort(std::vector<E>& arr, int left, int right);

private:
	void rebalance(iterator root);
	void strict_rebalance(iterator root, typename std::vector<T>::iterator first, typename std::vector<T>::iterator last);

	std::vector<T> data_to_vector(iterator root);

	bool comp_child_nodes(iterator root) const;
	bool comp_child_nodes(const_iterator root) const;
	size_type size(iterator root) const;
	size_type size(const_iterator root) const;

	const unsigned node_element_constant;
	node* root;
};

template<class T>
std::ostream& operator<<(std::ostream& os, const btree<T>& ref)
{
	os << (ref.to_string());
	return os;
}

template<class T>
std::istream& operator>>(std::istream& is, btree<T>& ref)
{
	T data;
	is >> data;
	ref.insert(data);
	return is;
}

template<class T>
void quickSort(std::vector<T>& arr, int left, int right) {
	int i = left, j = right;
	int tmp;
	T pivot = arr[(left + right) / 2];
 
	/* partition */
	while (i <= j)
	{
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j)
		{
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	};
 
	/* recursion */
	if (left < j)
		quickSort(arr, left, j);
	if (i < right)
		quickSort(arr, i, right);
}

template<class T>
btree<T>::btree(const unsigned n_e_const = 2):
	root(nullptr), node_element_constant(n_e_const)
{}

template<class T>
btree<T>::btree(const btree<T>& bt):
	root(nullptr)
{
	this->operator=(bt);
}

template<class T>
bool btree<T>::empty() const
{
	return size()==0;
}

template<class T>
void btree<T>::clear()
{
	deltree(root);
}

template<class T>
btree<T>::~btree()
{
	clear();
}

template<class T>
void btree<T>::rebalance(typename btree<T>::iterator root)
{
	if(root != nullptr)
	{
		if(comp_child_nodes(root))
		{
			for (typename std::array<node*, node_element_constant+1>::iterator it = (root->children).begin(); it != (root->children).end(); ++it)
			{
				rebalance(*it);
			}
		}
		else
		{
			std::vector<T> _data = data_to_vector(root);
			quicksort(_data, 0, _data.size());
			deltree(root->left);
			deltree(root->right);
			strict_rebalance(root, _data.begin(), _data.end());
		}
	}
}

template<class T>
void btree<T>::strict_rebalance(typename btree<T>::iterator root, typename std::vector<T>::iterator first, typename std::vector<T>::iterator last)
{
	if((root != nullptr) && (last > first))
	{
		typename std::vector<T>::size_type break_delim = (last - first) / node_element_constant;
		unsigned delim_marker = 0;
		for(typename std::array<node*, node_element_constant+1>::iterator it = (root->children).begin(); it != (root->children).end(); ++it)
		{
			(root->data)[break_delim] = *(first + ((break_delim + 1) * delim_marker));
			if((*it) == nullptr)
			{
				node* n = new node(std::array<T, node_element_constant>());
				(root->children)[it] = n;
			}

			strict_rebalance(*it, first + (break_delim * delim_marker), first + ((++break_delim) * delim_marker) -1);
		}
	}
}

template<class T>
std::vector<T> btree<T>::data_to_vector(typename btree<T>::iterator root)
{
	std::vector<T> vec;

	if(root != nullptr)
	{
		vec.push_back(root->data);
		
		for(typename std::array<node*, node_element_constant+1>::iterator it = (root->children).begin(); it != (root->children).end(); ++it)
		{
			vec.insert(vec.end(), data_to_vector(*it).begin(), data_to_vector(*it).end());
		}
	}

	return vec;
}

template<class T>
bool btree<T>::comp_child_nodes(typename btree<T>::iterator root) const
{
	typename btree<T>::size_type min, max;
	min = size(root);
	max = 0;
	for(typename std::array<node*, node_element_constant+1>::iterator it = (root->children).begin(); it != (root->children).end(); ++it)
	{
		if (size(*it) < min) min = size(*it);
		if (size(*it) > max) max = size(*it);
	}

	return (max - min) <= 1;
}

template<class T>
bool btree<T>::comp_child_nodes(typename btree<T>::const_iterator root) const
{
	typename btree<T>::size_type min, max;
	min = size(root);
	max = 0;
	for(typename std::array<node*, node_element_constant+1>::const_iterator it = (root->children).begin(); it != (root->children).end(); ++it)
	{
		if (size(*it) < min) min = size(*it);
		if (size(*it) > max) max = size(*it);
	}

	return (max - min) <= 1;
}

template<class T>
typename btree<T>::size_type btree<T>::size() const
{
	return size(root);
}

template<class T>
typename btree<T>::size_type btree<T>::size(typename btree<T>::iterator root) const
{
	int count = 0;
	if(root != nullptr)
	{
		++count;
		for(typename std::array<node*, node_element_constant>::iterator it = (root->children).begin(); it != (root->children).end(); ++it)
		{
			count += size(*it);
		}
	}

	return count;
}

template<class T>
typename btree<T>::size_type btree<T>::size(typename btree<T>::const_iterator root) const
{
	int count = 0;
	if(root != nullptr)
	{
		++count;
		for(typename std::array<node*, node_element_constant>::const_iterator it = (root->children).begin(); it != (root->children).end(); ++it)
		{
			count += size(*it);
		}
	}

	return count;
}

#endif