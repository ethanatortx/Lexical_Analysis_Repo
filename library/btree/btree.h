#ifndef BTREE_H
#define BTREE_H

#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include "error\error.h"

template<class T>
class btree
{
public:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef T const& const_reference;
	typedef std::size_t size_type;

	struct node;

	typedef node* iterator;
	typedef node const* const_iterator;

	struct node
	{
		node(const T& x, node* _left = nullptr, node* _right = nullptr):
			data(x), left(_left), right(_right) {}
		
		T data;
		node* left;
		node* right;
	};

	btree();
	btree(const btree<T>&);

	void insert(T data);
	iterator search(T data);
	bool remove(T data);
	void clear();
	std::stringstream& to_string(std::stringstream& ss, iterator pos);
	void deltree(iterator pos);
	size_type size(btree<T>::iterator pos);

	template<class E>
	friend std::ostream& operator<<(std::ostream&, const btree<E>&);
	template<class E>
	friend void quicksort(T arr[]);

private:
	bool size_is_comparable(btree<T>::iterator _root) const;
	void rebalance(btree<T>::iterator _root);
	void strict_rebalance(btree<T>::iterator _root);
	std::vector<T> data_to_vector(btree<T>::iterator _root);

	node* root;
};

template<class T>
btree<T>::btree():
	root(new node(T()))
{}

template<class T>
bool btree<T>::size_is_comparable(btree<T>::iterator _root) const
{
	int diff = (size(_root->left) - size(root->right));
	return std::abs(diff) <= 1;
}

template<class T>
void btree<T>::rebalance(btree<T>::iterator _root)
{
	if(size_is_comparable(_root))
	{
		rebalance(_root->left);
		rebalance(_root->right);
	}
	else
	{
		std::vector<T> vec = data_to_vector(_root);
		deltree(_root->left);
		deltree(_root->right);
		quicksort(vec, 0, vec.size());
		strict_rebalance(_root, vec);
	}
}

template<class T>
void btree<T>::strict_rebalance(btree<T>::node* _root, std::vector<T>& vec)
{
	if(vec.size() == 0)
	{
		return;
	}
	else if(vec.size() == 1)
	{
		_root->data = vec[0];
	}
	else if(vec.size() == 2)
	{
		_root->data = vec[0];
		node *left;
		left = new node(vec[1]);
		_root->left = left;
	}
	else
	{
		size_type median = vec.size()/2;

		_root->data = vec[median];
	
		std::vector<T> left_vec, right_vec;
		node *left, *right;

		left = new node();
		right = new node();

		_root->left = left;
		_root->right = right;

		left_vec.insert(left_vec.begin(), vec.begin(), vec.begin()+median);
		right_vec.insert(right_vec.begin(), vec.begin()+median+1, vec.end());

		strict_rebalance(_root->left, left_vec);
		strict_rebalance(_root->right, right_vec);
	}
}

template<class T>
std::vector<T> btree<T>::data_to_vector(btree<T>::iterator _root)
{
	std::vector<T> vec;

	if(_root != nullptr)
	{
		std::vector<T> tmp;

		vec.push_back(_root->data);

		tmp = data_to_vector(_root->left);
		vec.insert(vec.end(), tmp.begin(), tmp.end());

		tmp = data_to_vector(_root->right);
		vec.insert(vec.end(), tmp.begin(), tmp.end());
	}

	return vec;
}

template<class T>
void btree<T>::insert(btree<T>::iterator _root, btree<T>::const_reference _data)
{

	rebalance(_root);

	if(_data > _root->data)
	{
		if(_root->right == nullptr)
		{
			node* n = new node(_data);
			_root->right = n;
		}
		else
		{
			insert(_root->right, _data);
		}
	}
	else if (_data <= _root->data)
	{
		if(_root->left == nullptr)
		{
			node* n = new node(_data);
			_root->left = n;
		}
		else
		{
			insert(_root->left, _data);
		}
	}

	rebalance(_root);
}

template<class T>
btree<T>::iterator btree<T>::search(btree<T>::const_reference _data)
{

}

template<class T>
bool btree<T>::remove(btree<T>::const_reference _data)
{

}

template<class T>
void btree<T>::clear()
{

}

template<class T>
std::stringstream& to_string(std::stringstream& ss, iterator pos)
{

}

template<class T>
void btree<T>::deltree(iterator pos)
{

}

template<class T>
typename btree<T>::size_type btree<T>::size(btree<T>::iterator _root)
{
	btree<T>::size_type count = 0;
	if(_root != nullptr)
	{
		++count;
		count += size(_root->left);
		count += size(_root->right);
	}

	return count;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const btree<T>& B)
{
	os << (B.to_string());
	return os;
}

template<class T>
void quicksort(std::vector<T>& arr, int left, int right)
{
	int i = left, j = right;
	int tmp;
	int pivot = arr[(left + right) / 2];

	/* partition */
	while (i <= j) {
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j) {
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

#endif
