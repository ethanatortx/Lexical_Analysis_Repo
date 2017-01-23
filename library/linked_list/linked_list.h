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
	linked_list();
	linked_list(const linked_list<T>&);

	// iterator pre-declaration
	class iterator;
	class const_iterator;

	bool empty() const;

	void clear();

	linked_list<T>& operator=(const linked_list<T>&);
	linked_list<T>& operator=(linked_list<T>&&);

	inline bool operator==(const linked_list<T>& rhs) const { return this->head == rhs.head; }
	inline bool operator!=(const linked_list<T>& rhs) const { return this->head != rhs.head; }

	// push element to front
	void push_back(const T&);
	void push_back(T&&);

	// create and insert node at index
	void emplace(const T&, int);
	void emplace(const T&, const_iterator&);

	void emplace(T&&, int);
	void emplace(T&&, const_iterator&);

	// erase element at front and pull list forwards
	void pop();

	// erase element at position
	void erase(int);
	void erase(iterator&);

	// erase a range of elements from [lhs, rhs)
	void erase_range(int, int);
	void erase_range(iterator&, iterator&);

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
void linked_list<T>::push_back(const T& data) 
{
	Node<T>* n = new Node<T>(data);
	n->next = head;
	head = n;
}

template <class T>
void linked_list<T>::push_back(T&& data) 
{
	Node<T>* n = new Node<T>(data);
	n->next = head;
	head = n;
}

template <class T>
void linked_list<T>::emplace(const T& data, int pos) 
{

	if(!pos) this->push_back(data); return;

	Node<T>* n = new Node<T>(data);

	linked_list<T>::iterator it = this->begin();

	while(pos) {
		pos--;
		it++;
	}

	n->next = it->next;
	it->next = n;
}

template <class T>
void linked_list<T>::emplace(const T& data, iterator& it) 
{

	if(it == this->begin()) this->push_back(data);

	Node<T>* n = new Node<T>(data);

	n->next = it->next;
	it->next = n;
}

template <class T>
void linked_list<T>::emplace(T&& data, int pos) 
{

	if(this->empty()) return;

	Node<T>* n = new Node<T>(data);

	if(!pos) n->next = this->head; this->head = n; return;

	linked_list<T>::iterator it = this->begin();

	while(pos) {
		pos--;
		it++;
	}

	n->next = it->next;
	it->next = n;
}

template <class T>
void linked_list<T>::emplace(T&& data, iterator& it) 
{

	if(it == this->begin()) this->push_back(data);

	Node<T>* n = new Node<T>(data);

	n->next = it->next;
	it->next = n;
}

template <class T>
void linked_list<T>::pop() 
{

	Node<T>* n = head;
	head = head->next;
	delete n;
}

template <class T>
void linked_list<T>::erase(int pos)
{


}

template <class T>
void linked_list<T>::erase(iterator& it)
{


}

template <class T>
void linked_list<T>::erase_range(int lhs, int rhs)
{


}

template <class T>
void linked_list<T>::erase_range(iterator& lhs, iterator& rhs)
{


}

template <class T>
linked_list<T>::iterator linked_list<T>::begin()
{

}

template <class T>
linked_list<T>::const_iterator linked_list<T>::begin() const
{

}

template <class T>
linked_list<T>::const_iterator linked_list<T>::cbegin() const
{

}

template <class T>
linked_list<T>::iterator linked_list<T>::end()
{

}

template <class T>
linked_list<T>::const_iterator linked_list<T>::end() const
{

}

template <class T>
linked_list<T>::const_iterator linked_list<T>::cend() const
{
	
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