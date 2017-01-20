#ifndef __LINKED_LIST_H_INCLUDED__
#define __LINKED_LIST_H_INCLUDED__

#include <iostream>
#include <utility>
#include <iterator>

template <class T>
class Node {

	T Data;
	Node* Next;

public:

	Node(const T& x, Node* y = 0): Data(x), Next(y) {}

	inline void set_date(const T& x) { Data = x; }
	inline void set_next(Node* x) { Next = x; }

	inline T data() { return Data; }
	inline Node* next() { return Next; }
};

// singly linked lists
template <class T>
class linked_list {
protected:
	typedef T value_type;
	typedef T& reference;
	typedef T* pointer;
	typedef std::ptrdiff_t difference_type;

private:
	Node<T>* head;

public:
	linked_list();
	linked_list(const linked_list<T>&);

	// iterator pre-declaration
	class iterator;
	class const_iterator;

	bool empty() const;

	void clear();

	void operator=(const linked_list<T>&);
	void operator=(linked_list<T>&&);

	inline bool operator==(const linked_list<T>& rhs) const { return this->head == rhs.head; }
	inline bool operator!=(const linked_list<T>& rhs) const { return this->head != rhs.head; }

	// push element to front
	void push_back(const T&);
	void push_back(T&&);

	// erase element at front and pull list forwards
	void pop();

	// erase element at position
	void erase(int);

	// erase a range of elements from [lhs, rhs)
	void erase_range(int, int);

	iterator begin();
	const_iterator begin() const;
	const_iterator cbegin() const;

	iterator end();
	const_iterator end() const;
	const_iterator cend() const;
};

template <class T>
bool linked_list<T>::empty() const
{
	return this->head == NULL;
}

template <class T>
void linked_list<T>::clear() {

	Node<T>* p = head;

	
}

// iterator definition
template <class T>
class linked_list<T>::iterator:
	virtual public std::iterator<std::forward_iterator_tag, T> 
{	
	Node<T>* n_ref;

protected:
	typedef T value_type;
	typedef T& reference;
	typedef T* pointer;
	typedef int difference_type;
	typedef std::forward_iterator_tag iterator_category;

public:
	friend class linked_list;
	friend class const_iterator;

	iterator(Node<T>* x = nullptr): n_ref(x) {}
	iterator(const iterator& x): n_ref(x.n_ref) {}

	inline iterator& operator=(const iterator& x) 
	{
		this->n_ref = x.n_ref;
		return *this;
	}

	inline iterator& operator++() 
	{
		this->n_ref = this->n_ref->next;
		return *this;
	}

	inline iterator operator++(int)
	{
		iterator tmp(*this);
		this->n_ref = this->n_ref->next;
		return tmp;
	}

	inline bool operator==(const iterator& x) const 
	{
		return this->n_ref == x.n_ref;
	}

	inline bool operator!=(const iterator& x) const 
	{
		return this->n_ref != x.n_ref;
	}

	inline typename linked_list<T>::iterator::reference operator*() const 
	{
		return this->n_ref->data();
	}

	inline typename linked_list<T>::iterator::pointer operator->() const 
	{
		return this->n_ref;
	}

	inline iterator& swap(iterator& x) 
	{
		Node<T>* tmp(this->n_ref);
		this->n_ref = x.n_ref;
		x.n_ref = tmp;
		return *this;
	}
};

// constant iterator definition
template <class T>
class linked_list<T>::const_iterator:
	virtual public std::iterator<std::forward_iterator_tag, T>
{

	const Node<T>* n_ref;

protected:
	typedef T value_type;
	typedef T& reference;
	typedef T* pointer;
	typedef int difference_type;
	typedef std::forward_iterator_tag iterator_category;

public:
	friend class linked_list;
	friend class iterator;

	const_iterator(const Node<T>* x): n_ref(x) {}
	const_iterator(const iterator& x): n_ref(x.n_ref) {}
	const_iterator(const const_iterator& x): n_ref(x.n_ref) {}

	inline const_iterator& operator=(const iterator& x)
	{
		n_ref = x.n_ref;
		return *this;
	}

	inline const_iterator& operator=(const const_iterator& x)
	{
		n_ref = x.n_ref;
		return *this;
	}

	inline const_iterator& operator++()
	{
		this->n_ref = this->n_ref->next;
		return *this;
	}

	inline const_iterator operator++(int)
	{
		const_iterator tmp(*this);
		this->n_ref = this->n_ref->next;
		return tmp;
	}

	inline bool operator==(const const_iterator& x) const
	{
		return this->n_ref == x.n_ref;
	}

	inline bool operator!=(const const_iterator& x) const
	{
		return this->n_ref != x.n_ref;
	}

	inline typename linked_list<T>::const_iterator::reference operator*() const
	{
		return this->n_ref->data;
	}

	inline typename linked_list<T>::const_iterator::pointer operator->() const
	{
		return this->n_ref;
	}

	inline const_iterator& swap(const_iterator& x)
	{
		Node<T>* tmp(this->n_ref);
		this->n_ref = x.n_ref;
		x.n_ref = tmp;
		return *this;
	}
};

#endif