#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

template<class T>
class btree {

public:
	class const_iterator;
	class iterator;

private:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef std::size_t size_type;

	class Node {
	public:
		Node( T _data,
			  Node* _left = nullptr,
			  Node* _right = nullptr ):
		data(_data), left(_left), right(_right) {}
		
		template<class E>
		friend std::ostream& operator<<(std::ostream&, typename btree<E>::Node*);
		template<class E>
		friend std::istream& operator>>(std::istream&, typename btree<E>::Node*);

		T data;
		Node* prev;
		Node* left;
		Node* right;
	};

	// construct from initializer list
	btree(std::initializer_list<T>);

	// return count of nodes
	size_type count_nodes(Node*);

	// get string stream of data
	template<class E>
	friend std::stringstream to_string(typename btree<E>::Node*);

	// insert element at position
	void insert(iterator&, const T& data);
	void insert(const_reference, Node*);
	void insert(value_type&&, Node* = root);

	// erase element
	void erase(iterator&);

public:
	btree();
	btree(const btree<T>&);

	// return true if contains no elements
	bool empty() const;

	// clear data from the tree
	void clear();

	template<class E>
	friend bool operator==(const btree<E>&, const btree<E>&);
	template<class E>
	friend bool operator!=(const btree<E>&, const btree<E>&);
	template<class E>
	friend std::ostream& operator<<(std::ostream&, const btree<E>&);
	template<class E>
	friend std::istream& operator>>(std::istream&, const btree<E>&);

	// insert data into the tree
	void insert(const_reference);
	void insert(value_type&&);
	void insert(const_reference, size_type);
	void insert(const std::vector<const_reference>&);

	// erase first element with data
	void erase(const T&);
	// erase all elements with data
	void erase_with(const T&);

	// return iterator to first element with data
	iterator find(const T&);
	const_iterator find(const T&) const;

	// return iterator to beginning
	iterator begin();
	const_iterator begin() const;
	const_iterator cbegin() const;

	// return iterator to end
	iterator end();
	const_iterator end() const;
	const_iterator cend() const;

private:
	Node* root;
};

// constructors
template<class T>
btree<T>::btree():
	root(new typename btree<T>::Node(T()))
{

}
template<class T>
btree<T>::btree(const btree<T>& other)
{

}

// non-member functions
template<class T>
inline bool operator==(const btree<T>& lhs, const btree<T>& rhs)
{
	std::stringstream is_lhs, is_rhs;
	is_lhs << lhs;
	is_rhs << rhs;

	return (is_lhs.str()) == (is_rhs.str());
}

template<class T>
inline bool operator!=(const btree<T>& lhs, const btree<T>& rhs)
{
	std::stringstream is_lhs, is_rhs;
	is_lhs << lhs;
	is_rhs << rhs;

	return (is_lhs.str()) != (is_rhs.str());
}

template<class T>
inline std::ostream& operator<<(std::ostream& os, const btree<T>& rhs)
{
	os << to_string(rhs.root);
	return os;
}

template<class T>
inline std::istream& operator>>(std::istream& is, btree<T>& rhs)
{

}

template<class T>
inline std::stringstream to_string(typename btree<T>::Node* root)
{
	if(root == nullptr) return NULL;

	std::stringstream ss;

	ss << root->data;
	ss << to_string(root->left);
	ss << to_string(root->right);

	return ss;
}

template<class T>
void btree<T>::insert(typename btree<T>::const_reference data, typename btree<T>::iterator& pos)
{

}
template<class T>
void btree<T>::insert(typename btree<T>::const_reference data, typename btree<T>::Node* root)
{
	
}
template<class T>
void btree<T>::insert(typename btree<T>::value_type&& data, typename btree<T>::Node* root)
{

}

// member functions
// return total count of nodes in graph
template<class T>
typename btree<T>::size_type btree<T>::count_nodes(btree<T>::Node* root) // PRIVATE FUNC
{
	if(root == nullptr) return 0;

	typename btree<T>::size_type count = 1;
	count += count_nodes(root->left);
	count += count_nodes(root->right);

	return count;
}

// insert data into the graph
template<class T>
inline void btree<T>::insert(typename btree<T>::const_reference data)
	{ insert(data, this->root); }
template<class T>
inline void btree<T>::insert(typename btree<T>::value_type&& data)
	{ insert(data, this->root); }
template<class T>
void btree<T>::insert(typename btree<T>::const_reference data, typename btree<T>::size_type count)
{

}
template<class T>
void btree<T>::insert(const std::vector<typename btree<T>::const_reference>& data)
{

}

// erase first element with data
template<class T>
void btree<T>::erase(typename btree<T>::const_reference data)
{

}

// erase element
template<class T>
void btree<T>::erase(typename btree<T>::iterator& pos) // PRIVATE FUNC
{

}

// erase all elements with data
template<class T>
void btree<T>::erase_with(typename btree<T>::const_reference data)
{

}

// return iterator to beginning
template<class T>
inline typename btree<T>::iterator btree<T>::begin()
	{ return btree<T>::iterator(this->root); }
template<class T>
inline typename btree<T>::const_iterator btree<T>::begin() const
	{ return btree<T>::const_iterator(this->root); }
template<class T>
inline typename btree<T>::const_iterator btree<T>::cbegin() const
	{ return btree<T>::const_iterator(this->root); }

// return iterator to end
template<class T>
inline typename btree<T>::iterator btree<T>::end()
{

}
template<class T>
inline typename btree<T>::const_iterator btree<T>::end() const
{

}
template<class T>
inline typename btree<T>::const_iterator btree<T>::cend() const
{

}

template<class T>
class btree<T>::const_iterator:
	virtual public std::iterator<std::bidirectional_iterator_tag, T>
{
	typedef T value_type;
	typedef const typename btree<T>::Node* pointer;
	typedef T& reference;
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef std::ptrdiff_t difference_type;

	friend class btree;
	friend class btree<T>::iterator;

public:
	const_iterator(const typename btree<T>::Node* _ref = nullptr):
		ref(_ref) {}
	const_iterator(const typename btree<T>::iterator& other):
		ref(other.ref) {}
	const_iterator(const typename btree<T>::const_iterator& other):
		ref(other.ref) {}

	template<class E>
	friend bool operator==(const typename btree<E>::const_iterator&, const typename btree<E>::const_iterator&);
	template<class E>
	friend bool operator!=(const typename btree<E>::const_iterator&, const typename btree<E>::const_iterator&);
	template<class E>
	friend bool operator<=(const typename btree<E>::const_iterator&, const typename btree<E>::const_iterator&);
	template<class E>
	friend bool operator<(const typename btree<E>::const_iterator&, const typename btree<E>::const_iterator&);
	template<class E>
	friend bool operator>=(const typename btree<E>::const_iterator&, const typename btree<E>::const_iterator&);
	template<class E>
	friend bool operator>(const typename btree<E>::const_iterator&, const typename btree<E>::const_iterator&);

	inline typename btree<T>::const_iterator& operator=(const typename btree<T>::iterator& other)
	{
		this->ref = other.ref;
		return *this;
	}
	inline typename btree<T>::const_iterator& operator=(const typename btree<T>::const_iterator& other)
	{
		this->ref = other.ref;
		return *this;
	}

	const_iterator& operator++()
	{

	}
	const_iterator operator++(int)
	{

	}

	const_iterator& operator--()
	{
		ref = ref->prev;
		return *this;
	}
	const_iterator operator--(int)
	{
		typename btree<T>::const_iterator tmp(*this);
		ref = ref->prev;
		return tmp;
	}

	typename btree<T>::const_iterator::reference operator*() const
		{ return ref->data; }
	typename btree<T>::const_iterator::pointer operator->() const
		{}

	~const_iterator() {}

private:
	const typename btree<T>::Node* ref;
};

template<class T>
class btree<T>::iterator:
	virtual public std::iterator<std::bidirectional_iterator_tag, T>,
	public btree<T>::const_iterator
{
	typedef T value_type;
	typedef typename btree<T>::Node* pointer;
	typedef T& reference;
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef std::ptrdiff_t difference_type;

	friend class btree;
	friend class btree<T>::const_iterator;

public:
	iterator(typename btree<T>::Node* _ref):
		ref(_ref) {}
	iterator(const typename btree<T>::iterator& other):
		ref(other.ref) {}

	template<class E>
	friend bool operator==(const typename btree<E>::iterator&, const typename btree<E>::iterator&);
	template<class E>
	friend bool operator!=(const typename btree<E>::iterator&, const typename btree<E>::iterator&);
	template<class E>
	friend bool operator<=(const typename btree<E>::iterator&, const typename btree<E>::iterator&);
	template<class E>
	friend bool operator<(const typename btree<E>::iterator&, const typename btree<E>::iterator&);
	template<class E>
	friend bool operator>=(const typename btree<E>::iterator&, const typename btree<E>::iterator&);
	template<class E>
	friend bool operator>(const typename btree<E>::iterator&, const typename btree<E>::iterator&);

	inline typename btree<T>::iterator& operator=(const typename btree<T>::iterator& other)
	{

	}

	inline typename btree<T>::iterator& operator++()
	{

	}
	inline typename btree<T>::iterator operator++(int)
	{

	}

	inline typename btree<T>::iterator& operator--()
	{
		ref = ref->prev;
		return *this;
	}
	inline typename btree<T>::iterator operator--(int)
	{
		typename btree<T>::iterator tmp(*this);
		ref = ref->pref;
		return tmp;
	}

	inline typename btree<T>::iterator::reference operator*() const
		{ return ref->data; }
	inline typename btree<T>::iterator::pointer operator->() const
		{ return ref->left; }

private:
	typename btree<T>::Node* ref;
};

template<class T>
inline bool operator==(const typename btree<T>::iterator& lhs, const typename btree<T>::iterator& rhs)
{

}
template<class T>
inline bool operator!=(const typename btree<T>::iterator& rhs, const typename btree<T>::iterator& rhs)
{

}

#endif