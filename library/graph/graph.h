#ifndef GRAPH_H
#define GRAPH_H

#include <functional>
#include <iostream>
#include <utility>

//////////////////////////////////////////////////////////////////
//																//
//					Graph Base Class							//
//																//
//////////////////////////////////////////////////////////////////
template<class T,
		 class Hash = std::hash<T>>
class graph
{
public:
};

//////////////////////////////////////////////////////////////////
//																//
//					Graph List Implementation					//
//																//
//////////////////////////////////////////////////////////////////
template<class T,
		 class Hash = std::hash<T>>
class graph_list:
	public graph<T, Hash>
{
public:
	class iterator;
	class const_iterator;
	class Node;

private:
	friend class graph_list<T, Hash>::iterator;
	friend class graph_list<T, Hash>::const_iterator;

	void insert(const T&, Node**, graph_list<T, Hash>::iterator&);
	void insert(const T&, Node**, graph_list<T, Hash>::const_iterator&);

public:
	void insert(const T&, Node**);
	void insert(T&&, Node**);

private:

};

//////////////////////////////////////////////////////////////////
//																//
//					Graph Matrix Implementation					//
//																//
//////////////////////////////////////////////////////////////////
template<class T,
		 class Hash = std::hash<T>>
class graph_matrix:
	public graph<T, Hash>
{
	class Node;

protected:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef std::size_t size_type;

public:
	graph_matrix();

	class iterator;
	class const_iterator;

private:
	void insert(const T&, Node**, graph_matrix<T, Hash>::iterator&);
	void insert(const T&, Node**, graph_matrix<T, Hash>::const_iterator&);

public:
	bool empty() const;

	void clear();

	void insert(const T&, Node**);
	void insert(T&&, Node**);

	bool is_edge(Node*, Node*);
	bool is_edge(const graph_matrix<T, Hash>::iterator&, const graph_matrix<T, Hash>::iterator&);
	bool is_edge(const graph_matrix<T, Hash>::const_iterator&, const graph_matrix<T, Hash>::const_iterator&);

	void set_edge(Node*, Node*, bool);
	void set_edge(const graph_matrix<T, Hash>::iterator&, const graph_matrix<T, Hash>::iterator&, bool);
	void set_edge(const graph_matrix<T, Hash>::const_iterator&, const graph_matrix<T, Hash>::const_iterator&, bool);

	void erase(Node*);
	void erase(const Node*);
	void erase(const graph_matrix<T, Hash>::iterator&);
	void erase(const graph_matrix<T, Hash>::const_iterator&);

	typename graph_matrix<T, Hash>::size_type path(Node*, Node*);
	typename graph_matrix<T, Hash>::size_type path(const Node*, const Node*);
	typename graph_matrix<T, Hash>::size_type path(const graph_matrix<T, Hash>::iterator&, const graph_matrix<T, Hash>::iterator&);
	typename graph_matrix<T, Hash>::size_type path(const graph_matrix<T, Hash>::const_iterator&, const graph_matrix<T, Hash>::const_iterator&);

	~graph_matrix();

private:
	bool** chk_arr;
};


template<class T,
		 class Hash>
class graph_matrix<T, Hash>::const_iterator
{
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef std::ptrdiff_t difference_type;

public:
	const_iterator(const graph_matrix<T, Hash>::Node* _ref):
		ref(_ref) {}
	const_iterator(const graph_matrix<T, Hash>::iterator& other):
		ref(other.ref) {}
	const_iterator(const graph_matrix<T, Hash>::const_iterator& other):
		ref(other.ref) {}

	template<class E, class Hash_E>
	friend bool operator==(const typename graph_matrix<E, Hash_E>::const_iterator&, const typename graph_matrix<E, Hash_E>::const_iterator&);
	template<class E, class Hash_E>
	friend bool operator!=(const typename graph_matrix<E, Hash_E>::const_iterator&, const typename graph_matrix<E, Hash_E>::const_iterator&);

	typename graph_matrix<T, Hash>::const_iterator& operator=(const typename graph_matrix<T, Hash>::const_iterator& other) {}

	typename graph_matrix<T, Hash>::const_iterator& operator++() {}
	typename graph_matrix<T, Hash>::const_iterator operator++(int) {}

	typename graph_matrix<T, Hash>::const_iterator& operator--() {}
	typename graph_matrix<T, Hash>::const_iterator operator--(int) {}

	typename graph_matrix<T, Hash>::const_iterator::reference operator*() const {}
	std::pair<const typename graph_matrix<T, Hash>::Node*, const typename graph_matrix<T, Hash>::Node**> * operator->() const {}

private:
	const typename graph_matrix<T, Hash>::Node* ref;
};

template<class T, class Hash = std::hash<T>>
bool operator==(const typename graph_matrix<T, Hash>::const_iterator& lhs, const typename graph_matrix<T, Hash>::const_iterator& rhs) {}
template<class T, class Hash = std::hash<T>>
bool operator!=(const typename graph_matrix<T, Hash>::const_iterator& lhs, const typename graph_matrix<T, Hash>::const_iterator& rhs) {}

template<class T,
		 class Hash>
class graph_matrix<T, Hash>::iterator:
	public graph_matrix<T, Hash>::const_iterator
{
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef std::ptrdiff_t difference_type;

public:
	iterator(typename graph_matrix<T, Hash>::Node* _ref):
		ref(_ref) {}
	iterator(const typename graph_matrix<T, Hash>::iterator& other):
		ref(other.ref) {}

	template<class E, class Hash_E>
	friend bool operator==(const typename graph_matrix<E, Hash_E>::iterator&, const typename graph_matrix<E, Hash_E>::iterator&);
	template<class E, class Hash_E>
	friend bool operator!=(const typename graph_matrix<E, Hash_E>::iterator&, const typename graph_matrix<E, Hash_E>::iterator&);

	typename graph_matrix<T, Hash>::iterator& operator=(const typename graph_matrix<T, Hash>::iterator& other) {}

	typename graph_matrix<T, Hash>::iterator& operator++() {}
	typename graph_matrix<T, Hash>::iterator operator++(int) {}

	typename graph_matrix<T, Hash>::iterator& operator--() {}
	typename graph_matrix<T, Hash>::iterator operator--(int) {}

	typename graph_matrix<T, Hash>::iterator::reference operator*() const {}
	std::pair<typename graph_matrix<T, Hash>::Node*, typename graph_matrix<T, Hash>::Node**> * operator->() const {}

	typename graph_matrix<T, Hash>::iterator& swap(typename graph_matrix<T, Hash>::iterator& other) {}

private:
	typename graph_matrix<T, Hash>::Node* ref;
};

template<class T, class Hash = std::hash<T>>
bool operator==(const typename graph_matrix<T, Hash>::iterator& lhs, const typename graph_matrix<T, Hash>::iterator& rhs) {}
template<class T, class Hash = std::hash<T>>
bool operator!=(const typename graph_matrix<T, Hash>::iterator& lhs, const typename graph_matrix<T, Hash>::iterator& rhs) {}

template<class T,
		 class Hash>
class graph_matrix<T, Hash>::Node
{
public:
	Node(const T& _data, Node** _ref = nullptr):
		data(_data), ref(_ref) {}

	T data;
	Node** ref;
};

// graph matrix public method declaration

#endif