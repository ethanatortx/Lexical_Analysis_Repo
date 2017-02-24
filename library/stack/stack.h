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

	typedef T value_type;
	typedef T& reference;

public:
	stack();
	stack(const stack<T>&);

	stack<T>& operator=(const stack<T>&);

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
stack<T>::stack():
	head(new Node(T())), tail(nullptr)
{
	head->next = tail;
}

template<class T>
stack<T>::stack(const stack<T>& other):
	head(new Node(T())), tail(nullptr)
{
	head->next = tail;
	this->operator=(other);
}

template<class T>
stack<T>& stack<T>::operator=(const stack<T>& rhs)
{
	clear();

	stack<T>::Node* n = rhs.head;

	while(n->next != nullptr)
	{
		push(n->next->data);
		n = n->next;
	}

	return *this;
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
inline std::string stack<T>::to_string(const char delim)
{
	if(empty()) return "";
	std::stringstream ss;

	stack<T>::Node* n = head;

	while(n->next != nullptr)
	{
		ss << n->next->data << delim;
		n = n->next;
	}

	return (ss.str());
}

template<class T>
inline std::string stack<T>::to_string(const char delim) const
{
	if(empty()) return "";
	std::stringstream ss;

	stack<T>::Node* n = head;

	while(n->next != nullptr)
	{
		ss << n->next->data << delim;
		n = n->next;
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
inline void swap(stack<T>& lhs, stack<T>& rhs)
{
	stack<T> old(lhs);
	lhs.operator=(rhs);
	rhs.operator=(old);
}

template<class T>
stack<T>::~stack()
{
	clear();
	delete head;
}

#endif