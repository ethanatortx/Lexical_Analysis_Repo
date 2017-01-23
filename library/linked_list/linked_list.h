#ifndef __LINKED_LIST_H_INCLUDED__
#define __LINKED_LIST_H_INCLUDED__

#include <iostream>
#include <utility>
#include <iterator>
#include <string>

template <class T>
class Node {

	T Data;
	Node* Next;

public:

	Node(const T& x, Node* y = 0): Data(x), Next(y) {}

	inline void set_data(const T& x) { Data = x; }
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
	linked_list(): head(0) {}
	linked_list(const linked_list<T>&);

	// iterator pre-declaration
	class iterator;
	class const_iterator;

	bool empty() const;

	void clear();

	linked_list<T>& operator=(const linked_list<T>&);
	linked_list<T>& operator=(linked_list<T>&&);

	iterator operator[](int);

	inline bool operator==(const linked_list<T>& rhs) const { return this->head == rhs.head; }
	inline bool operator!=(const linked_list<T>& rhs) const { return this->head != rhs.head; }

	// push element to front
	void push_back(const T&);
	void push_back(T&&);

	// create and insert node at index
	void emplace_after(const T&, int);
	void emplace_after(const T&, iterator);

	void emplace_after(T&&, int);
	void emplace_after(T&&, iterator);

	// erase_after element at front and pull list forwards
	void pop();

	// erase_after element at position
	void erase_after(int);
	void erase_after(iterator);

	// erase_after a range of elements from [lhs, rhs)
	void erase_range(int, int);
	void erase_range(iterator, iterator);

	iterator begin();
	const_iterator begin() const;
	const_iterator cbegin() const;

	iterator end();
	const_iterator end() const;
	const_iterator cend() const;

	void print();
};

template <class T>
linked_list<T>::linked_list(const linked_list<T>& list)
{

	linked_list<T>::iterator other = list.begin();
	while(other)
	{
		this->insert((*other).data(), this->end());
		other++;
	}
}

template <class T>
bool linked_list<T>::empty() const
{
	return this->head == NULL;
}

template <class T>
void linked_list<T>::clear() 
{
	while (head->next()) {
		this->pop();
	}
}

template <class T>
linked_list<T>& linked_list<T>::operator=(const linked_list<T>& L) 
{

	linked_list<T>::const_iterator it = L.cbegin();

	while(it->next()) {
		Node<T>* n = new Node<T>(*it);
		this->insert(n, this->cend());
		it++;
	}

	return *this;
}

template <class T>
linked_list<T>& linked_list<T>::operator=(linked_list<T>&& L) 
{

	linked_list<T>::const_iterator it = L.begin();

	while(it->next()) {
		Node<T>* n = new Node<T>(*it);
		this->insert(n, this->cend());
		it++;
	}

	return *this;
}

template <class T>
typename linked_list<T>::iterator linked_list<T>::operator[](int pos)
{
	linked_list<T>::iterator* it = new linked_list<T>::iterator(this->begin());

	if(!pos) return *it;

	while(pos)
	{
		pos--;
		it++;
	}

	return *it;
}

template <class T>
void linked_list<T>::push_back(const T& data) 
{
	Node<T>* n = new Node<T>(data);
	n->set_next(head);
	head = n;
}

template <class T>
void linked_list<T>::push_back(T&& data) 
{
	Node<T>* n = new Node<T>(data);
	n->set_next(head);
	head = n;
}

template <class T>
void linked_list<T>::emplace_after(const T& data, int pos) 
{

	if(!pos) this->push_back(data); return;

	Node<T>* n = new Node<T>(data);

	linked_list<T>::iterator it;

	while(pos > 0)
	{

		pos--;
		it++;
	}

	n->set_next(it->next());
	it->set_next(n);
}

template <class T>
void linked_list<T>::emplace_after(const T& data, iterator it) 
{

	if(it == this->begin()) this->push_back(data); return;

	Node<T>* n = new Node<T>(data);

	n->set_next(it->next());
	it->set_next(n);
}

template <class T>
void linked_list<T>::emplace_after(T&& data, int pos) 
{


	if(!pos) { this->push_back(data); return; }

	Node<T>* n = new Node<T>(data);

	linked_list<T>::iterator it = this->begin();

	while(pos)
	{
		pos--;
		it++;
	}

	n->set_next(it->next());
	it->set_next(n);
}

template <class T>
void linked_list<T>::emplace_after(T&& data, iterator it) 
{

	if(it == this->begin()) this->push_back(data);

	Node<T>* n = new Node<T>(data);

	n->set_next(it->next());
	it->set_next(n);
}

template <class T>
void linked_list<T>::pop() 
{

	Node<T>* n = head;
	head = head->next();
	delete n;
}

template <class T>
void linked_list<T>::erase_after(int pos)
{

	if(!pos) this->pop(); return;

	Node<T>* n;

	linked_list<T>::iterator it = (*this)[pos];

	n = it->next();
	it->set_next(it->next()->next());
	delete n;
}

template <class T>
void linked_list<T>::erase_after(iterator it)
{

	if(it == this->begin()) this->pop(); return;

	Node<T>* n;

	n = it->next();
	it->set_next(it->next()->next());
	delete n;
}

template <class T>
void linked_list<T>::erase_range(int lhs, int rhs)
{

	linked_list<T>::iterator begin = (*this)[lhs];
	linked_list<T>::iterator end = (*this)[rhs];

	while(begin->next() != end)
	{
		Node<T>* n = *begin;
		begin++;
		delete n;
	}
}

template <class T>
void linked_list<T>::erase_range(iterator lhs, iterator rhs)
{

	while(lhs->next() != rhs)
	{
		Node<T>* n = *lhs;
		lhs++;
		delete n;
	}
}

template <class T>
typename linked_list<T>::iterator linked_list<T>::begin()
{

	linked_list<T>::iterator* it = new linked_list<T>::iterator(head);
	return *it;
}

template <class T>
typename linked_list<T>::const_iterator linked_list<T>::begin() const
{

	const linked_list<T>::const_iterator* it = new linked_list<T>::const_iterator(head);
	return *it;
}

template <class T>
typename linked_list<T>::const_iterator linked_list<T>::cbegin() const
{

	const linked_list<T>::const_iterator* it = new linked_list<T>::const_iterator(head);
	return *it;
}

template <class T>
typename linked_list<T>::iterator linked_list<T>::end()
{

	linked_list<T>::iterator it = this->begin();
	while(it->next())
	{
		it++;
	}
	return it;
}

template <class T>
typename linked_list<T>::const_iterator linked_list<T>::end() const
{

	const linked_list<T>::const_iterator it = this->cbegin();
	while(it->next())
	{
		it++;
	}
	return it;
}

template <class T>
typename linked_list<T>::const_iterator linked_list<T>::cend() const
{

	const linked_list<T>::const_iterator it = this->cbegin();
	while(it->next())
	{
		it++;
	}
	return it;
}

template <class T>
void linked_list<T>::print() 
{

	linked_list<T>::iterator it = this->begin();
	while(it->next()) 
	{
		std::cout<< *it <<std::endl;
		it++;
	}
	std::cout<< *it <<std::endl;
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
	typedef Node<T>* pointer;
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
		this->n_ref = this->n_ref->next();
		return *this;
	}

	inline iterator operator++(int)
	{
		iterator tmp(*this);
		this->n_ref = this->n_ref->next();
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

	inline typename linked_list<T>::iterator::value_type operator*() const 
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
	const typedef T value_type;
	const typedef T& reference;
	const typedef Node<T>* pointer;
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
		this->n_ref = this->n_ref->next();
		return *this;
	}

	inline const_iterator operator++(int)
	{
		const_iterator tmp(*this);
		this->n_ref = this->n_ref->next();
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

	inline typename linked_list<T>::const_iterator::value_type operator*() const
	{
		return this->n_ref->data();
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