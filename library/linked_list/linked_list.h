#ifndef __LINKED_LIST_H_INCLUDED__
#define __LINKED_LIST_H_INCLUDED__

#include <iostream>
#include <utility>
#include <iterator>

// linked list class; circular
template <class T>
class linked_list {
private:
	// element structure; data and pointer to next element
	struct Node {
		Node(const T& x, Node* y = 0): data(x), next(y) {}
		T data;
		Node* next;
	};

	Node* tail;

protected:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef std::ptrdiff_t difference_type;

public:

	// pre-declare iterators
	class iterator;
	class const_iterator;

	linked_list(): tail(new Node(T())) { tail->next = tail; }
	linked_list(const linked_list& L): tail(new Node(T())) 
	{
		tail->next = tail;
	}

	// clear contents of this list; erase all elements
	void clear();

	inline bool operator==(const linked_list<T>& other) const { return this->tail == other.tail; }
	inline bool operator!=(const linked_list<T>& other) const { return this->tail != other.tail; }

	linked_list<T>& operator=(const linked_list<T>&);
	linked_list<T>& operator=(linked_list<T>&&);

	// get iterator to element at position
	iterator operator[](int);
	iterator at(int);

	// return if list is empty
	inline bool empty() const { return this->tail == this->tail->next; }

	// get value of element at front
	inline T& front() { return *begin(); }
	inline const T& front() const { return *begin(); }

	// get iterator at front of list
	inline iterator begin() { return iterator(tail->next); }
	inline const_iterator begin() const { return const_iterator(tail->next); }
	inline const_iterator cbegin() const { return const_iterator(tail->next); }

	// get value of element at end
	inline T& back() { return *end(); }
	inline const T& back() { return *end(); }

	// get iterator at end of list
	inline iterator end() { return iterator(tail); }
	inline const_iterator end() const { return const_iterator(tail); }
	inline const_iterator cend() const { return const_iterator(tail); }

	// construct and insert element at position
	void emplace(const T&, int);
	void emplace(const T&, iterator);

	void emplace(T&&, int);
	void emplace(T&&, iterator);

	// append value to front
	void push_back(const T&);
	void push_back(T&&);

	// erase element at position
	void erase(int);
	void erase(iterator);

	// erase elements from [lhs, rhs)
	void erase_range(int, int);
	void erase_range(iterator, iterator);

	// print list to console
	void print();

	// rotate list so pos becomes new head
	void rotate(int);
	void rotate(iterator);

	// reverse the list
	void reverse();

	// swap list contents with other list
	inline void swap(linked_list<T>& other)
	{
		linked_list<T>::Node* n = tail;
		this->tail = other.tail;
		other.tail = n;
	}
};

template <class T>
void linked_list<T>::clear()
{
	while(!empty()) { pop(); }
}

template <class T>
typename linked_list<T>& linked_list<T>::operator=(const linked_list<T>& other)
{
	linked_list<T>::iterator it(other.head);
	
	clear();
	
	while(it->next != other.tail) {
		push_back(*it);
	}

	reverse();
}

template <class T>
typename linked_list<T>& linked_list<T>::operator=(linked_list<T>&& other)
{
	linked_list<T>::iterator it(other.head);

	clear();

	while(it->next != other.tail) {
		push_back(*it);
	}

	reverse();
}

template <class T>
typename linked_list<T>::iterator operator[](int)
{
	linked_list<T>::iterator it = this->begin();
	while(it->next) {

	};
}

template <class T>
typename linked_list<T>::iterator at(int pos)
{
	linked_list<T>::iterator it = this->begin();
	while (pos){
		it++;
		pos--;
	}
	return it;
}

template <class T>
void linked_list<T>::emplace(const T& data, int pos)
{

}

template <class T>
void linked_list<T>::emplace(const T& data, typename linked_list<T>::iterator pos)
{

}

template <class T>
void linked_list<T>::emplace(T&& data, int pos)
{

}

template <class T>
void linked_list<T>::emplace(T&& data, typename linked_list<T>::iterator pos)
{

}

template <class T>
void linked_list<T>::push_back(const T& data)
{
	linked_list<T>::Node* n = new Node(data);
	n->next = this->head;
	this->head = n;
}

template <class T>
void linked_list<T>::push_back(T&& data)
{
	linked_list<T>::Node* n = new Node(data);
	n->next = this->head;
	this->head = n;
}

template <class T>
void linked_list<T>::erase(int pos)
{
	linked_list<T>::iterator it = this->at(pos);
}

template <class T>
void linked_list<T>::erase(typename linked_list<T>::iterator pos)
{

}

template <class T>
void linked_list<T>::erase_range(int lhs, int rhs)
{

}

template <class T>
void linked_list<T>::erase_range(typename linked_list<T>::iterator lhs, typename linked_list<T>::iterator rhs)
{

}

template <class T>
void linked_list<T>::rotate(int pos)
{

}

template <class T>
void linked_list<T>::rotate(typename linked_list<T>::iterator it)
{

}

template <class T>
void linked_list<T>::reverse()
{

}

/*
	Note on iterators:

	ALL forward access iterators MUST contain a:
		postfix operator++		(iterator++)
		prefix operator++		(++iterator)
		assignment operator		(iterator = other)
		dereference operator	(*iterator)
		pointer operator 		(iterator->)
		swap function			(iterator.swap(iterator))
	AND standard type definitions for:
		value_type				(T)
		pointer					(T*)
		reference				(T&)
		difference_type			(int)
		iterator_category		(forward_access_tag)
	In order to be valid inputs into STL
	sorting and processing functions and
	algorithms.
*/
template <class T>
class linked_list<T>::iterator:
	virtual public std::iterator<std::forward_iterator_tag, T> 
{
protected:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef int difference_type;
	typedef std::forward_iterator_tag iterator_category;

	friend class linked_list;
	friend class linked_list<T>::const_iterator;

private:
	Node* nref;

public:
	iterator(linked_list<T>::Node* x = 0): nref(x) {}

	iterator(const linked_list<T>::iterator& it): nref(it.nref) {}

	inline typename linked_list<T>::iterator& operator=(const linked_list<T>::iterator other)
	{
		this->nref = other.nref;
		return *this;
	}

	inline typename linked_list<T>::iterator& operator++()
	{
		this->nref = this->nref->next;
		return *this;
	}

	inline typename linked_list<T>::iterator operator++(int)
	{
		linked_list<T>::iterator tmp(*this);
		this->nref = this->nref->next;
		return tmp;
	}

	inline typename linked_list<T>::iterator::reference operator*() const 
	{
		return this->nref->next->data;
	}

	inline typename linked_list<T>::iterator::pointer operator->() const 
	{
		return this->nref->next;
	}

	inline bool operator==(const iterator& other) const 
	{
		return this->nref == other.nref;
	}

	inline bool operator!=(const iterator& other) const 
	{
		return this->nref != other.nref;
	}

	inline typename linked_list<T>::iterator swap(typename linked_list<T>::iterator other)
	{
		typename linked_list<T>::Node* n = this->nref;
		this->nref = other.nref;
		other.nref = n;
		return *this;
	}
};

template <class T>
class linked_list<T>::const_iterator:
	virtual public std::iterator<std::forward_iterator_tag, T>
{
protected:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef int difference_type;
	typedef std::forward_iterator_tag iterator_category;

	friend class linked_list;
	friend class linked_list<T>::iterator;

private:
	const Node* nref;

public:
	const_iterator(const Node* n = 0): nref(n) {}
	const_iterator(typename linked_list<T>::iterator& other): nref(other.nref) {}
	const_iterator(typename linked_list<T>::const_iterator& other): nref(other.nref) {}

	inline typename linked_list<T>::const_iterator& operator=(const typename linked_list<T>::iterator& other)
	{
		this->nref = other.nref;
	}

	inline typename linked_list<T>::const_iterator& operator=(const typename linked_list<T>::const_iterator& other)
	{
		this->nref = other.nref;
	}

	inline typename linked_list<T>::const_iterator& operator++()
	{
		this->nref = this->nref->next;
		return *this;
	}

	inline typename linked_list<T>::const_iterator operator++(int)
	{
		typename linked_list<T>::const_iterator tmp(*this);
		this->nref = this->nref->next;
		return tmp;
	}

	inline typename linked_list<T>::const_iterator::reference operator*() const
	{
		return this->nref->next->data;
	}

	inline typename linked_list<T>::const_iterator::pointer operator->() const
	{
		return this->nref->next;
	}

	inline bool operator==(const typename linked_list<T>::const_iterator& other) const
	{
		return this->nref == other.nref;
	}

	inline bool operator!=(const typename linked_list<T>::const_iterator& other) const
	{
		return this->nref != other.nref;
	}

	inline typename linked_list<T>::const_iterator& swap(typename linked_list<T>::const_iterator& other)
	{
		typename linked_list<T>::Node* n = this->nref;
		this->nref = other.nref;
		other.nref = n;
	}
};

#endif