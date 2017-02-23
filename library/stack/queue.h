#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>
#include <sstream>

template<class T>
class queue 
{
	typedef T value_type;
	typedef T& reference;

	struct Node
	{
		Node(const T& x, Node* y = nullptr):
			data(x), next(y) {}
		T data;
		Node* next;
	};

	class iterator;
	class const_iterator;

	iterator begin();
	const_iterator begin() const;
	const_iterator cbegin() const;

	iterator end();
	const_iterator end() const;
	const_iterator cend() const;

public:
	queue();
	queue(const queue<T>&);

	queue<T>& operator=(const queue<T>&);

	value_type pull();

	void push(const T& data);
	void push(T&& data);

	bool empty() const;

	void clear();

	std::string to_string(const char = ' ');
	std::string to_string(const char = ' ') const;

	template<class E>
	friend std::ostream& operator<<(std::ostream&, const queue<E>&);
	template<class E>
	friend std::istream& operator>>(std::istream&, queue<E>&);

private:
	Node* head;
};

template<class T>
class queue<T>::const_iterator
{
	friend class queue;
	friend class queue<T>::iterator;

	typedef T value_type;
	typedef typename queue<T>::Node const* pointer;
	typedef T const& reference;
	typedef std::forward_iterator_tag iterator_category;

public:
	const_iterator(typename queue<T>::Node const* _ref):
		ref(_ref) {}
	const_iterator(const typename queue<T>::iterator& other):
		ref(other.ref) {}
	const_iterator(const typename queue<T>::const_iterator& other):
		ref(other.ref) {}

	inline bool operator==(const typename queue<T>::const_iterator& rhs)
		{ return this->ref == rhs.ref; }
	inline bool operator!=(const typename queue<T>::const_iterator& rhs)
		{ return this->ref == rhs.ref; }
	inline typename queue<T>::const_iterator& swap(typename queue<T>::const_iterator& rhs)
	{
		typename queue<T>::Node* tmp(ref);
		this->ref = rhs.ref;
		rhs.ref = tmp;
		return *this;
	}

	inline typename queue<T>::const_iterator& operator=(const typename queue<T>::iterator& rhs)
	{
		this->ref = rhs.ref;
		return *this;
	}
	inline typename queue<T>::const_iterator& operator=(const typename queue<T>::const_iterator& rhs)
	{
		this->ref = rhs.ref;
		return *this;
	}

	inline typename queue<T>::const_iterator& operator++()
	{
		ref = ref->next;
		return *this;
	}
	inline typename queue<T>::const_iterator operator++(int)
	{
		typename queue<T>::const_iterator tmp(*this);
		ref = ref->next;
		return tmp;
	}

	inline typename queue<T>::const_iterator::pointer operator->() const
		{ return ref->next; }
	inline typename queue<T>::const_iterator::reference operator*() const
		{ return ref->next->data; }

private:
	typename queue<T>::Node const* ref;
};

template<class T>
class queue<T>::iterator
{
	friend class queue;
	friend class queue<T>::const_iterator;

	typedef T value_type;
	typedef typename queue<T>::Node* pointer;
	typedef T& reference;
	typedef std::forward_iterator_tag iterator_category;

public:
	iterator(typename queue<T>::Node* _ref):
		ref(_ref) {}
	iterator(const typename queue<T>::iterator& other):
		ref(other.ref) {}

	inline bool operator==(const typename queue<T>::iterator& rhs)
		{ return this->ref == rhs.ref; }
	inline bool operator!=(const typename queue<T>::iterator& rhs)
		{ return this->ref != rhs.ref; }
	inline typename queue<T>::iterator& swap(typename queue<T>::iterator& rhs)
	{
		typename queue<T>::Node* tmp(this->ref);
		this->ref = rhs.ref;
		rhs.ref = tmp;
		return *this;
	}

	inline typename queue<T>::iterator& operator=(const typename queue<T>::iterator& rhs)
	{
		this->ref = rhs.ref;
		return *this;
	}

	inline typename queue<T>::iterator& operator++()
	{
		ref = ref->next;
		return *this;
	}
	inline typename queue<T>::iterator operator++(int)
	{
		typename queue<T>::Node* tmp(ref);
		ref = ref->next;
		return tmp;
	}

	inline typename queue<T>::iterator::pointer operator->() const
		{ return ref->next; }
	inline typename queue<T>::iterator::reference operator*() const
		{ return ref->next->data; }

private:
	typename queue<T>::Node* ref;
};

template<class T>
inline typename queue<T>::iterator queue<T>::begin()
	{ return typename queue<T>::iterator(head); }
template<class T>
inline typename queue<T>::const_iterator queue<T>::begin() const
	{ return typename queue<T>::const_iterator(head); }
template<class T>
inline typename queue<T>::const_iterator queue<T>::cbegin() const
	{ return typename queue<T>::const_iterator(head); }

template<class T>
inline typename queue<T>::iterator queue<T>::end()
	{ return typename queue<T>::iterator(tail); }
template<class T>
inline typename queue<T>::const_iterator queue<T>::end() const
	{ return typename queue<T>::const_iterator(tail); }
template<class T>
inline typename queue<T>::const_iterator queue<T>::cend() const
	{ return typename queue<T>::const_iterator(tail); }

template<class T>
queue<T>::queue():
	head(new Node(T())) {}

template<class T>
queue<T>::queue(const queue<T>& other):
	head(new Node(T()))
{
	this->operator=(other);
}

template<class T>
queue<T>& queue<T>::operator=(const queue<T>& rhs)
{
	clear();
 
	for(typename queue<T>::const_iterator it = rhs.begin();
		it != rhs.end();
		++it)
	{
		std::cout << "test";
		this->push(*it);
	}

	return (*this);
}

template<class T>
std::string queue<T>::to_string(const char delim)
{
	if(empty()) return "";
	std::stringstream ss;

	for(queue<T>::const_iterator it = begin();
		it != end();
		++it)
	{
		ss << (*it) << delim;
	}

	return (ss.str());
}

template<class T>
std::string queue<T>::to_string(const char delim) const
{
	if(empty()) return "";
	std::stringstream ss;

	queue<T>::Node* test = head;

	while(test->next != nullptr)
	{
		std::cout << test->next->data;
	}

	return (ss.str());
}

template<class T>
inline std::ostream& operator<<(std::ostream& os, const queue<T>& rhs)
{
	std::cout << "test";
	os << (rhs.to_string());
	return os;
}

template<class T>
inline std::istream& operator>>(std::istream& is, queue<T>& rhs)
{
	T x;
	is >> x;
	rhs.push(x);
	return is;
}

template<class T>
inline void swap(queue<T>& lhs, queue<T>& rhs)
{
	queue<T> old(*lhs);
	lhs.operator=(*rhs);
	rhs.operator=(old);
}

template<class T>
typename queue<T>::value_type queue<T>::pull()
{
	if(empty()) return 0;

	queue<T>::Node* n = head->next;
	head->next = head->next->next;

	T x = n->data;
	delete n;
	return x;
}

template<class T>
void queue<T>::push(const T& data)
{
	queue<T>::Node* n = new queue<T>::Node(data);
	if(!empty())
	{
		n->next = head->next;
		head->next = n;
	}
	else if(empty())
	{
		head->next = n;
	}
}

template<class T>
void queue<T>::push(T&& data)
{
	queue<T>::Node* n = new queue<T>::Node(data);
	if(!empty())
	{
		n->next = head->next;
		head->next = n;
	}
	else if(empty())
	{
		head->next = n;
	}
}

template<class T>
inline void queue<T>::clear()
{
	while(!empty()) pull();
}

template<class T>
inline bool queue<T>::empty() const
{
	return (head->next == nullptr);
}

#endif