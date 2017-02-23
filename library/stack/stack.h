#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>
#include <sstream>

template<class T>
class stack
{
	struct Node
	{
		Node(const T& x, Node* y = nullptr):
			data(x), next(y) {}
		T data;
		Node* next;
	};

	class const_iterator;
	class iterator;

	iterator begin();
	const_iterator begin() const;
	const_iterator cbegin() const;

	iterator end();
	const_iterator end() const;
	const_iterator cend() const;

public:
	stack();

	T pull();

	void push(const T& data);
	void push(T&& data);

	void clear();

	bool empty() const;

	std::string to_string(const char = ' ');
	std::string to_string(const char = ' ') const;
	template<class E>
	friend std::ostream& operator<<(std::ostream&, const stack<E>&);
	template<class E>
	friend std::istream& operator>>(std::istream&, stack<E>&);

	~stack();

private:
	Node* head;
	Node* tail;
};

template<class T>
class stack<T>::const_iterator
{
	friend class stack;
	friend class stack<T>::iterator;

	typedef T value_type;
	typedef T& reference;

public:
	const_iterator(typename stack<T>::Node const* _ref):
		ref(_ref) {}
	const_iterator(const typename stack<T>::iterator& other):
		ref(other.ref) {}
	const_iterator(const typename stack<T>::const_iterator& other):
		ref(other.ref) {}

	inline typename stack<T>::const_iterator& operator=(const typename stack<T>::iterator& other)
	{
		ref = other.ref;
		return *this;
	}
	inline typename stack<T>::const_iterator& operator=(const typename stack<T>::const_iterator& other)
	{
		ref = other.ref;
		return *this;
	}

	inline bool operator==(const typename stack<T>::const_iterator& rhs)
		{ return (this->ref == rhs.ref); }
	inline bool operator!=(const typename stack<T>::const_iterator& rhs)
		{ return (this->ref != rhs.ref); }

	inline void swap(typename stack<T>::const_iterator& rhs)
	{
		const typename stack<T>::Node* old_lhs_ref = this->ref;
		this->ref = rhs.ref;
		rhs.ref = old_lhs_ref;
	}

	inline typename stack<T>::const_iterator& operator++()
	{
		ref = ref->next;
		return *this;
	}
	inline typename stack<T>::const_iterator operator++(int)
	{
		typename stack<T>::const_iterator tmp(*this);
		ref = ref->next;
		return tmp;
	}

	inline typename stack<T>::Node* operator->() const
		{ return ref->next; }
	inline typename stack<T>::const_iterator::reference operator*() const
		{ return ref->next->data; }

private:
	typename stack<T>::Node const* ref;
};

template<class T>
class stack<T>::iterator:
	public stack<T>::const_iterator
{
	friend class stack;
	friend class stack<T>::const_iterator;

	typedef T value_type;
	typedef T& reference;

public:
	iterator(typename stack<T>::Node* _ref):
		ref(_ref) {}
	iterator(const typename stack<T>::iterator& other):
		ref(other.ref) {}

	inline typename stack<T>::iterator& operator=(const typename stack<T>::iterator& other)
	{
		ref = other.ref;
		return *this;
	}

	inline bool operator==(const typename stack<T>::iterator& rhs)
		{ return (this->ref == rhs.ref); }
	inline bool operator!=(const typename stack<T>::iterator& rhs)
		{ return (this->ref != rhs.ref); }

	inline void swap(typename stack<T>::iterator& rhs)
	{
		typename stack<T>::Node* old_lhs_ref = this->ref;
		this->ref = rhs.ref;
		rhs.ref = old_lhs_ref;
	}

	inline typename stack<T>::iterator& operator++()
	{
		ref = ref->next;
		return (*this);
	}
	inline typename stack<T>::iterator operator++(int)
	{
		typename stack<T>::iterator tmp(*this);
		ref = ref->next;
		return tmp;
	}

	inline typename stack<T>::Node* operator->() const
		{ return ref->next; }
	inline typename stack<T>::iterator::reference operator*() const
		{ return ref->next->data; }

private:
	typename stack<T>::Node* ref;
};

template<class T>
stack<T>::stack():
	head(new Node(T())), tail(nullptr)
{
	head->next = tail;
}

template<class T>
T stack<T>::pull()
{
	if(empty()) return 0;
	T x = head->next->data;
	stack<T>::Node* n = head->next;
	head->next = head->next->next;
	delete n;
	return x;
}

template<class T>
void stack<T>::push(const T& data)
{
	stack<T>::Node* n = new stack<T>::Node(data);
	if(!empty())
	{
		tail->next = n;
		tail = n;
	}
	else if(empty())
	{
		tail = n;
		tail->next = nullptr;
		head->next = tail;
	}
}

template<class T>
void stack<T>::push(T&& data)
{
	stack<T>::Node* n = new stack<T>::Node(data);
	if(!empty())
	{
		tail->next = n;
		tail = n;
	}
	else if(empty())
	{
		tail = n;
		tail->next = nullptr;
		head->next = tail;
	}
}

template<class T>
inline void stack<T>::clear()
{
	while(!empty()) pull();
}

template<class T>
inline bool stack<T>::empty() const
{
	return (head->next == nullptr);
}

template<class T>
typename stack<T>::iterator stack<T>::begin()
	{ return stack<T>::iterator(head); }
template<class T>
typename stack<T>::const_iterator stack<T>::begin() const
	{ return stack<T>::const_iterator(head); }
template<class T>
typename stack<T>::const_iterator stack<T>::cbegin() const
	{ return stack<T>::const_iterator(head); }

template<class T>
typename stack<T>::iterator stack<T>::end()
	{ return stack<T>::iterator(tail); }
template<class T>
typename stack<T>::const_iterator stack<T>::end() const
	{ return stack<T>::const_iterator(tail); }
template<class T>
typename stack<T>::const_iterator stack<T>::cend() const
	{ return stack<T>::const_iterator(tail); }

template<class T>
inline std::string stack<T>::to_string(const char delim)
{
	std::stringstream ss;

	for(stack<T>::const_iterator it = begin();
		it != end();
		++it)
	{
		ss << (*it) << delim;
	}

	return (ss.str());
}

template<class T>
inline std::string stack<T>::to_string(const char delim) const
{
	std::stringstream ss;

	for(stack<T>::const_iterator it = begin();
		it != end();
		++it)
	{
		ss << (*it) << delim;
	}

	return (ss.str());
}

template<class T>
inline std::ostream& operator<<(std::ostream& os, const stack<T>& _stack)
{
	os << (_stack.to_string());
	return os;
}

template<class T>
inline std::istream& operator>>(std::istream& is, stack<T>& _stack)
{
	T _data;
	is >> _data;

	_stack.push(_data);

	return is;
}

template<class T>
stack<T>::~stack()
{
	clear();
	delete head;
}

#endif