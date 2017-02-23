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

	queue<T>::Node* n = rhs.head;

	while(n->next != nullptr)
	{
		push(n->next->data);
		n = n->next;
	}

	return (*this);
}

template<class T>
std::string queue<T>::to_string(const char delim)
{
	if(empty()) return "";
	std::stringstream ss;

	queue<T>::Node* test = head;

	while(test->next != nullptr)
	{
		ss << (test->next->data) << delim;
		test = test->next;
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
		ss << (test->next->data) << delim;
		test = test->next;
	}

	return (ss.str());
}

template<class T>
inline std::ostream& operator<<(std::ostream& os, const queue<T>& rhs)
{
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