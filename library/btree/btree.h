#ifndef BTREE_H
#define BTREE_H

#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <vector>

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

	template<class E>
	friend std::ostream& operator<<(std::ostream&, const btree<E>&);
	template<class E>
	friend void quicksort(std::vector<E>&, int, int);

	btree();
	btree(const btree<T>&);
	~btree();

	void add(const_reference data);
	void insert(iterator _root, const_reference data);
	iterator search(const_reference data);
	bool remove(const_reference data);
	void clear();
	std::string to_string(iterator pos) const;
	std::string to_string(iterator pos, std::stringstream& ss) const;
	void deltree(iterator pos);
	size_type size(btree<T>::iterator pos) const;


private:
	bool size_is_comparable(btree<T>::iterator _root) const;
	void rebalance(btree<T>::iterator _root);
	void strict_rebalance(btree<T>::iterator _root, const std::vector<T>& vec);
	std::vector<T> data_to_vector(btree<T>::iterator _root);

	node* root;
};

template<class T>
std::ostream& operator<<(std::ostream& os, const btree<T>& b)
{
	os << (b.to_string(b.root));
	return os;
}

template<class T>
void quicksort(std::vector<T>& arr, int left, int right)
{
	int i = left, j = right;
	T tmp;
	T pivot = arr[(left + right) / 2];

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
		quicksort(arr, left, j);
	if (i < right)
		quicksort(arr, i, right);
}

template<class T>
btree<T>::btree():
	root(nullptr)
{}

template<class T>
btree<T>::~btree()
{
	//clear();
}

template<class T>
bool btree<T>::size_is_comparable(btree<T>::iterator _root) const
{
	if(_root == nullptr) return 0;
	int diff = (size(_root->left) - size(root->right));
	return (std::abs(diff) <= 1);
}

template<class T>
void btree<T>::rebalance(btree<T>::iterator _root)
{
	if(_root == nullptr) return;
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
void btree<T>::strict_rebalance(btree<T>::node* _root, const std::vector<T>& vec)
{
	typename std::vector<T>::size_type _size_of_vec = vec.size();
	if(_root != nullptr)
	{
		if(_size_of_vec < 2)
		{
			
		}
		else if ((_size_of_vec % 2) == 0)
		{

		}
		else if ((_size_of_vec % 2) == 1)
		{
			typename std::vector<T>::size_type _median = ((_size_of_vec) / 2);
			T new_root_data = vec[_median];
			std::vector<T> lvec(vec.begin(), vec.begin()+_median-1);
			std::vector<T> rvec(vec.begin()+_median, vec.end());

			_root->data = new_root_data;

			if(lvec.size() > 0)
			{
				node* new_left = new node(T());
				_root->left = new_left;
				strict_rebalance(new_left, lvec);
			}
			if(rvec.size() > 0)
			{
				node* new_right = new node(T());
				_root->right = new_right;
				strict_rebalance(new_right, rvec);
			}
		}
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

	if(root == nullptr && _root == nullptr)
	{
		node* n = new node(_data);
		root = n;
		_root = n;
	}
	else if(_data > _root->data)
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
	else if(_data <= _root->data)
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
inline void btree<T>::add(btree<T>::const_reference _data)
{
	insert(this->root, _data);
}

template<class T>
typename btree<T>::iterator btree<T>::search(btree<T>::const_reference _data)
{

}

template<class T>
bool btree<T>::remove(btree<T>::const_reference _data)
{

}

template<class T>
void btree<T>::clear()
{
	deltree(root);
}

template<class T>
std::string btree<T>::to_string(typename btree<T>::iterator pos) const
{
	std::stringstream ss;
	return to_string(pos, ss);
}

template<class T>
std::string btree<T>::to_string(typename btree<T>::iterator pos, std::stringstream& ss) const
{
	if(pos != nullptr)
	{
		ss << pos->data;
		ss << to_string(pos->left, ss);
		ss << to_string(pos->right, ss);
	}

	return (ss.str());
}

template<class T>
void btree<T>::deltree(iterator pos)
{
	if(pos != nullptr)
	{
		deltree(pos->left);
		deltree(pos->right);

		delete pos;
	}
}

template<class T>
typename btree<T>::size_type btree<T>::size(btree<T>::iterator _root) const
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


#endif
