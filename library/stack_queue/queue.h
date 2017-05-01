#ifndef QUEUE_H
#define QUEUE_H

template<class T>
class queue
{
	typedef T value_type;
	typedef std::size_t size_type;

	class node
	{
	public:
		node(value_type d): data(d), prev(nullptr), next(nullptr) {}

		value_type data;
		node* prev;
		node* next;
	};

public:
	queue(): head(new node(T())), tail(nullptr)
	{
		head->next = head;
		head->prev = head;
		tail = head;
	}

	value_type peek() const;
	value_type pull();

	void push(const value_type&);

	void clear();
	bool empty() const;

	template<class E>
	friend std::string to_string(const queue<E>&);

private:
	node* head;
	node* tail;
};

template<class T>
typename queue<T>::value_type queue<T>::peek() const
{
	T data;
	if(!empty())
		data = tail->data;
	return data;
}

template<class T>
typename queue<T>::value_type queue<T>::pull()
{
	T data;
	if(!empty())
	{
		data = tail->data;
		node* n = tail;
		tail = tail->prev;
		delete n;
	}
	return data;
}

template<class T>
void queue<T>::push(const T& data)
{
	node* n = new node(data);
	n->prev = tail;
	tail->next = n;
	tail = n;
}

template<class T>
bool queue<T>::empty() const
{
	return head == tail;
}

template<class T>
void queue<T>::clear()
{
	while(!empty())
		pull();
	delete head;
}

template<class T>
std::string to_string(const queue<T>& q)
{
	
}

#endif