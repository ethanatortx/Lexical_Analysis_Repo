#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>
#include <sstream>

template<class T>
class stack 
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

public:
	stack();
	stack(const stack<T>&);

	stack<T>& operator=(const stack<T>&);

	value_type pull();

	void push(const T& data);
	void push(T&& data);

	bool empty() const;

	void clear();

	std::string to_string(const char = ' ');
	std::string to_string(const char = ' ') const;

	template<class E>
	friend std::ostream& operator<<(std::ostream&, const stack<E>&);
	template<class E>
	friend std::istream& operator>>(std::istream&, stack<E>&);
	template<class E>
	friend void swap(stack<T>&, stack<T>&);

private:
	Node* head;
};

template<class T>
stack<T>::stack():
	head(new Node(T())) {}

template<class T>
stack<T>::stack(const stack<T>& other):
	head(new Node(T()))
{
	this->operator=(other);
}

//TODO : fix this so that it isn't reversed on copy

template<class T>
stack<T>& stack<T>::operator=(const stack<T>& rhs)
{
	clear();

	stack<T>::Node* n = rhs.head;
	stack<T> inverse;

	while(n->next != nullptr)
	{
		inverse.push(n->next->data);
		n = n->next;
	}

	n = inverse.head;
	while(n->next != nullptr)
	{
		push(n->next->data);
		n = n->next;
	}

	return (*this);
}

template<class T>
std::string stack<T>::to_string(const char delim)
{
	if(empty()) return "";
	std::stringstream ss;

	stack<T>::Node* test = head;

	while(test->next != nullptr)
	{
		ss << (test->next->data) << delim;
		test = test->next;
	}

	return (ss.str());
}

template<class T>
std::string stack<T>::to_string(const char delim) const
{
	if(empty()) return "";
	std::stringstream ss;

	stack<T>::Node* test = head;

	while(test->next != nullptr)
	{
		ss << (test->next->data) << delim;
		test = test->next;
	}

	return (ss.str());
}

template<class T>
inline std::ostream& operator<<(std::ostream& os, const stack<T>& rhs)
{
	os << (rhs.to_string());
	return os;
}

template<class T>
inline std::istream& operator>>(std::istream& is, stack<T>& rhs)
{
	T x;
	is >> x;
	rhs.push(x);
	return is;
}

template<class T>
inline void swap(stack<T>& lhs, stack<T>& rhs)
{
	stack<T> old(lhs);
	lhs.operator=(rhs);
	rhs.operator=(old);
}

template<class T>
typename stack<T>::value_type stack<T>::pull()
{
	if(empty()) return 0;

	stack<T>::Node* n = head->next;
	head->next = head->next->next;

	T x = n->data;
	delete n;
	return x;
}

template<class T>
void stack<T>::push(const T& data)
{
	stack<T>::Node* n = new stack<T>::Node(data);
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
void stack<T>::push(T&& data)
{
	stack<T>::Node* n = new stack<T>::Node(data);
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
inline void stack<T>::clear()
{
	while(!empty()) pull();
}

template<class T>
inline bool stack<T>::empty() const
{
	return (head->next == nullptr);
}

#endif