#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>
#include <sstream>

template<class T>
class queue
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
	queue();
	queue(const queue<T>&);

	queue<T>& operator=(const queue<T>&);

	T pull();

	void push(const T& data);
	void push(T&& data);

	void clear();

	bool empty() const;

	std::string to_string(const char = ' ');
	std::string to_string(const char = ' ') const;
	template<class E>
	friend std::ostream& operator<<(std::ostream&, const queue<E>&);
	template<class E>
	friend std::istream& operator>>(std::istream&, queue<E>&);

	~queue();

private:
	Node* head;
	Node* tail;
};

template<class T>
queue<T>::queue():
	head(new Node(T())), tail(nullptr)
{
	head->next = tail;
}

template<class T>
queue<T>::queue(const queue<T>& other):
	head(new Node(T())), tail(nullptr)
{
	head->next = tail;
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

	return *this;
}

template<class T>
T queue<T>::pull()
{
	if(empty()) return 0;
	T x = head->next->data;
	queue<T>::Node* n = head->next;
	head->next = head->next->next;
	delete n;
	return x;
}

template<class T>
void queue<T>::push(const T& data)
{
	queue<T>::Node* n = new queue<T>::Node(data);
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
void queue<T>::push(T&& data)
{
	queue<T>::Node* n = new queue<T>::Node(data);
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
inline void queue<T>::clear()
{
	while(!empty()) pull();
}

template<class T>
inline bool queue<T>::empty() const
{
	return (head->next == nullptr);
}

template<class T>
inline std::string queue<T>::to_string(const char delim)
{
	if(empty()) return "";
	std::stringstream ss;

	queue<T>::Node* n = head;

	while(n->next != nullptr)
	{
		ss << n->next->data << delim;
		n = n->next;
	}

	return (ss.str());
}

template<class T>
inline std::string queue<T>::to_string(const char delim) const
{
	if(empty()) return "";
	std::stringstream ss;

	queue<T>::Node* n = head;

	while(n->next != nullptr)
	{
		ss << n->next->data << delim;
		n = n->next;
	}

	return (ss.str());
}

template<class T>
inline std::ostream& operator<<(std::ostream& os, const queue<T>& _queue)
{
	os << (_queue.to_string());
	return os;
}

template<class T>
inline std::istream& operator>>(std::istream& is, queue<T>& _queue)
{
	T _data;
	is >> _data;

	_queue.push(_data);

	return is;
}

template<class T>
inline void swap(queue<T>& lhs, queue<T>& rhs)
{
	queue<T> old(lhs);
	lhs.operator=(rhs);
	rhs.operator=(old);
}

template<class T>
queue<T>::~queue()
{
	clear();
	delete head;
}

#endif